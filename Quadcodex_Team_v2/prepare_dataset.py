import pandas as pd
import numpy as np

# === 1. Cargar los datasets ===
df_users = pd.read_csv("data/usuarios_ejercicios_valoraciones.csv")
df_exercises = pd.read_csv("data/megaGymDataset.csv")

# === 2. Preprocesar df_exercises ===
# Opción 1: Rellenar NaN con 1 (como tenías)
df_exercises = df_exercises.fillna(1)

# Opción alternativa: Rellenar NaN de manera más específica
# df_exercises['Rating'] = df_exercises['Rating'].fillna(df_exercises['Rating'].median())
# df_exercises['Level'] = df_exercises['Level'].fillna('Intermediate')
# df_exercises['Equipment'] = df_exercises['Equipment'].fillna('None')

# Guardar versión preprocesada
df_exercises.to_csv("data/megaGymDataset_filled.csv", index=False)
print("Dataset de ejercicios preprocesado guardado")

# === 3. Renombrar columnas para merge ===
df_exercises.rename(columns={"ID": "id_ejercicio"}, inplace=True)

# === 4. Convertir tipos de datos ===
df_users["id_ejercicio"] = df_users["id_ejercicio"].astype(int)
df_exercises["id_ejercicio"] = df_exercises["id_ejercicio"].astype(int)

# Convertir otras columnas si es necesario
df_users['edad'] = df_users['edad'].astype(int)
df_users['peso'] = df_users['peso'].astype(float)
df_users['altura'] = df_users['altura'].astype(float)

# === 5. Crear características adicionales útiles ===
# Calcular BMI de usuarios
df_users['bmi'] = df_users['peso'] / ((df_users['altura'] / 100) ** 2)

# Categorizar por edad
def categorizar_edad(edad):
    if edad < 18:
        return 'adolescente'
    elif edad < 30:
        return 'joven'
    elif edad < 50:
        return 'adulto'
    else:
        return 'mayor'

df_users['categoria_edad'] = df_users['edad'].apply(categorizar_edad)

# Categorizar por BMI
def categorizar_bmi(bmi):
    if bmi < 18.5:
        return 'bajo_peso'
    elif bmi < 25:
        return 'normal'
    elif bmi < 30:
        return 'sobrepeso'
    else:
        return 'obesidad'

df_users['categoria_bmi'] = df_users['bmi'].apply(categorizar_bmi)

# === 6. Merge de datasets ===
df_joint = df_users.merge(df_exercises, on="id_ejercicio", how="inner")

# === 7. Crear características combinadas para recomendación ===
# Crear una columna de tags combinados
df_joint['tags_combinados'] = df_joint['Type'] + ' ' + df_joint['BodyPart'] + ' ' + df_joint['Level']

# === 8. Analizar información del dataset ===
print("\n=== INFORMACIÓN DEL DATASET CONJUNTO ===")
print(f"Número de registros: {len(df_joint)}")
print(f"Número de usuarios únicos: {df_joint['genero'].nunique()}")
print(f"Número de ejercicios únicos: {df_joint['id_ejercicio'].nunique()}")
print(f"\nRango de edades: {df_joint['edad'].min()} - {df_joint['edad'].max()}")
print(f"Valoración promedio: {df_joint['valoracion'].mean():.2f}")
print(f"\nDistribución de género:")
print(df_joint['genero'].value_counts())

# === 9. Guardar dataset conjunto ===
output_path = "data/dataset_conjunto.csv"
df_joint.to_csv(output_path, index=False)

print(f"\n✔ Dataset conjunto creado correctamente con {len(df_joint)} registros")
print(f"Guardado en: {output_path}")

# === 10. Crear dataset enriquecido para análisis ===
# Opcional: Guardar versión con características adicionales
df_enriched = df_joint.copy()

# Agregar características de popularidad
popularity = df_joint.groupby('id_ejercicio').agg({
    'valoracion': ['mean', 'count'],
    'Title': 'first'
}).reset_index()

popularity.columns = ['id_ejercicio', 'valoracion_promedio', 'num_valoraciones', 'Title']
popularity['popularidad'] = popularity['valoracion_promedio'] * np.log1p(popularity['num_valoraciones'])

# Merge con dataset original
df_enriched = df_enriched.merge(popularity[['id_ejercicio', 'popularidad']], on='id_ejercicio', how='left')

# Guardar dataset enriquecido
df_enriched.to_csv("data/dataset_enriquecido.csv", index=False)
print("\n✔ Dataset enriquecido creado para análisis avanzado")

# === 11. Mostrar algunas muestras ===
print("\n=== MUESTRAS DEL DATASET ===")
print(df_joint[['genero', 'edad', 'Title', 'Type', 'BodyPart', 'Level', 'valoracion']].head(10))

# === 12. Información estadística ===
print("\n=== ESTADÍSTICAS IMPORTANTES ===")
print("Valoraciones por grupo de edad:")
print(df_joint.groupby('categoria_edad')['valoracion'].mean())

print("\nValoraciones por parte del cuerpo:")
print(df_joint.groupby('BodyPart')['valoracion'].mean().sort_values(ascending=False).head(10))