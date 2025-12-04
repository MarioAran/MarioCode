import pandas as pd
import numpy as np
import tensorflow as tf
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder, MinMaxScaler, StandardScaler
import pickle
import warnings
warnings.filterwarnings('ignore')

# ========== 1. CARGAR Y PREPARAR DATOS ==========
print("Cargando dataset...")
df = pd.read_csv("data/dataset_conjunto.csv")

print(f"Dimensión del dataset: {df.shape}")
print(f"Columnas disponibles: {df.columns.tolist()}")

# ========== 2. ANÁLISIS INICIAL ==========
print("\n=== Análisis inicial ===")
print(f"Número de registros: {len(df)}")
print(f"Número de usuarios únicos: {df['genero'].nunique()}")  # Asumiendo que genero identifica usuarios
print(f"Número de ejercicios únicos: {df['id_ejercicio'].nunique()}")
print(f"Rango de valoraciones: {df['valoracion'].min()} - {df['valoracion'].max()}")

# ========== 3. PREPROCESAMIENTO INTELIGENTE ==========
# Crear copia para no modificar el original
df_processed = df.copy()

# ===== 3.1. Manejar columnas problemáticas =====
# Columnas que no son útiles para el modelo
columns_to_drop = ['Desc', 'RatingDesc', 'Title']  # Texto largo, información redundante
df_processed = df_processed.drop(columns=[col for col in columns_to_drop if col in df_processed.columns])

# ===== 3.2. Codificar variables categóricas de manera estratégica =====
encoders = {}

# Columnas que deben ser codificadas
categorical_cols = ["genero", "Type", "BodyPart", "Equipment", "Level"]

for col in categorical_cols:
    if col in df_processed.columns:
        print(f"Codificando columna: {col}")
        print(f"  Valores únicos: {df_processed[col].unique()[:10]}...")
        
        le = LabelEncoder()
        df_processed[col] = le.fit_transform(df_processed[col].astype(str))
        encoders[col] = le
        
        print(f"  Número de categorías: {len(le.classes_)}")

# ===== 3.3. Normalizar datos numéricos =====
print("\nNormalizando datos numéricos...")

# Columnas numéricas que necesitan escalado
numeric_cols = ["edad", "peso", "altura", "Rating"]

# Separar scaler para cada tipo de dato si es necesario
scaler_numeric = MinMaxScaler()

# Aplicar escalado solo a las columnas que existen
existing_numeric = [col for col in numeric_cols if col in df_processed.columns]

if existing_numeric:
    print(f"Columnas numéricas a escalar: {existing_numeric}")
    df_processed[existing_numeric] = scaler_numeric.fit_transform(df_processed[existing_numeric])
    print("Escalado completado")
else:
    print("No hay columnas numéricas para escalar")

# ===== 3.4. Manejar la columna 'id_ejercicio' =====
# Para id_ejercicio, es mejor tratarlo como categoría o usar embedding
if 'id_ejercicio' in df_processed.columns:
    print(f"\nTratando id_ejercicio (ejercicios únicos: {df_processed['id_ejercicio'].nunique()})")
    
    # Opción 1: Normalizar como numérico (si hay muchos IDs)
    if df_processed['id_ejercicio'].nunique() > 50:
        scaler_id = MinMaxScaler()
        df_processed['id_ejercicio_scaled'] = scaler_id.fit_transform(df_processed[['id_ejercicio']])
        encoders['id_scaler'] = scaler_id
    else:
        # Opción 2: Codificar como categoría
        le_id = LabelEncoder()
        df_processed['id_ejercicio_encoded'] = le_id.fit_transform(df_processed['id_ejercicio'])
        encoders['id_ejercicio'] = le_id

# ========== 4. PREPARAR FEATURES Y TARGET ==========
print("\n=== Preparando features y target ===")

# Definir columnas de features
feature_cols = []

# Añadir columnas codificadas
feature_cols.extend([col for col in categorical_cols if col in df_processed.columns])

# Añadir columnas numéricas escaladas
feature_cols.extend(existing_numeric)

# Añadir id_ejercicio procesado
if 'id_ejercicio_scaled' in df_processed.columns:
    feature_cols.append('id_ejercicio_scaled')
elif 'id_ejercicio_encoded' in df_processed.columns:
    feature_cols.append('id_ejercicio_encoded')
elif 'id_ejercicio' in df_processed.columns:
    feature_cols.append('id_ejercicio')

print(f"Features seleccionadas: {feature_cols}")
print(f"Número de features: {len(feature_cols)}")

# Crear X e y
X = df_processed[feature_cols]
y = df_processed['valoracion']

print(f"Forma de X: {X.shape}")
print(f"Forma de y: {y.shape}")

# Verificar que no haya NaN
print(f"NaN en X: {X.isna().sum().sum()}")
print(f"NaN en y: {y.isna().sum()}")

# ========== 5. DIVISIÓN DE DATOS ==========
print("\n=== División train-test ===")
X_train, X_test, y_train, y_test = train_test_split(
    X, y, 
    test_size=0.2, 
    random_state=42,  # Para reproducibilidad
    stratify=df_processed['genero'] if 'genero' in df_processed.columns else None
)

print(f"Train size: {X_train.shape}")
print(f"Test size: {X_test.shape}")

# ========== 6. CONSTRUCCIÓN DEL MODELO MEJORADO ==========
print("\n=== Construyendo modelo ===")

input_dim = X_train.shape[1]

# Modelo más robusto
model = tf.keras.Sequential([
    # Capa de entrada con regularización
    tf.keras.layers.Dense(256, activation="relu", input_shape=(input_dim,),
                         kernel_regularizer=tf.keras.regularizers.l2(0.001)),
    tf.keras.layers.Dropout(0.3),  # Regularización
    
    tf.keras.layers.Dense(128, activation="relu",
                         kernel_regularizer=tf.keras.regularizers.l2(0.001)),
    tf.keras.layers.Dropout(0.3),
    
    tf.keras.layers.Dense(64, activation="relu"),
    tf.keras.layers.Dropout(0.2),
    
    tf.keras.layers.Dense(32, activation="relu"),
    
    # Capa de salida (regresión)
    tf.keras.layers.Dense(1, activation="linear")  # Para predicción de valoración
])

# Compilar modelo
model.compile(
    optimizer=tf.keras.optimizers.Adam(learning_rate=0.001),
    loss="mse",
    metrics=["mae", "mse"]
)

print("Resumen del modelo:")
model.summary()

# ========== 7. ENTRENAMIENTO CON CALLBACKS ==========
print("\n=== Entrenando modelo ===")

# Callbacks para mejor entrenamiento
callbacks = [
    tf.keras.callbacks.EarlyStopping(
        monitor='val_loss',
        patience=10,
        restore_best_weights=True
    ),
    tf.keras.callbacks.ReduceLROnPlateau(
        monitor='val_loss',
        factor=0.5,
        patience=5,
        min_lr=0.00001
    ),
    tf.keras.callbacks.ModelCheckpoint(
        filepath='best_model.h5',
        monitor='val_loss',
        save_best_only=True
    )
]

# Entrenar modelo
history = model.fit(
    X_train, y_train,
    validation_split=0.15,
    epochs=50,
    batch_size=32,
    callbacks=callbacks,
    verbose=1
)

# ========== 8. EVALUACIÓN ==========
print("\n=== Evaluación del modelo ===")

# Evaluar en test set
test_results = model.evaluate(X_test, y_test, verbose=0)
print(f"Test Loss (MSE): {test_results[0]:.4f}")
print(f"Test MAE: {test_results[1]:.4f}")

# Predicciones de ejemplo
print("\n=== Predicciones de ejemplo ===")
sample_indices = np.random.choice(len(X_test), 5, replace=False)
sample_X = X_test.iloc[sample_indices]
sample_y_true = y_test.iloc[sample_indices].values
sample_y_pred = model.predict(sample_X, verbose=0).flatten()

for i in range(5):
    print(f"Ejemplo {i+1}:")
    print(f"  Valoración real: {sample_y_true[i]:.2f}")
    print(f"  Valoración predicha: {sample_y_pred[i]:.2f}")
    print(f"  Error: {abs(sample_y_true[i] - sample_y_pred[i]):.2f}")
    print()

# ========== 9. GUARDAR MODELO Y ENCODERS ==========
print("\n=== Guardando modelo y recursos ===")

# Guardar modelo
model.save("h5/modelo_recomendador.h5")
print("✓ Modelo guardado como 'h5/modelo_recomendador.h5'")

# Guardar encoders y scalers
with open("pkl/encoders.pkl", "wb") as f:
    pickle.dump(encoders, f)
print("✓ Encoders guardados como 'pkl/encoders.pkl'")

# Guardar scaler numérico si existe
if 'scaler_numeric' in locals():
    with open("pkl/scaler_numeric.pkl", "wb") as f:
        pickle.dump(scaler_numeric, f)
    print("✓ Scaler numérico guardado")

# Guardar lista de features
with open("pkl/feature_cols.pkl", "wb") as f:
    pickle.dump(feature_cols, f)
print("✓ Lista de features guardada")

# ========== 10. FUNCIÓN DE PREDICCIÓN ==========
def predecir_valoracion(usuario_features, ejercicio_id):
    """
    Función para predecir la valoración que un usuario daría a un ejercicio
    
    Args:
        usuario_features: dict con características del usuario
        ejercicio_id: ID del ejercicio
    
    Returns:
        Predicción de valoración
    """
    # Cargar recursos
    with open("pkl/encoders.pkl", "rb") as f:
        encoders = pickle.load(f)
    
    with open("pkl/feature_cols.pkl", "rb") as f:
        feature_cols = pickle.load(f)
    
    # Crear dataframe con las features
    features_dict = {}
    
    # Procesar cada feature
    for col in feature_cols:
        if col in usuario_features:
            # Si es categórico, codificar
            if col in encoders:
                features_dict[col] = encoders[col].transform([str(usuario_features[col])])[0]
            else:
                features_dict[col] = usuario_features[col]
        elif col == 'id_ejercicio_scaled' and 'id_scaler' in encoders:
            # Escalar id_ejercicio
            features_dict[col] = encoders['id_scaler'].transform([[ejercicio_id]])[0][0]
        elif col == 'id_ejercicio_encoded' and 'id_ejercicio' in encoders:
            # Codificar id_ejercicio
            features_dict[col] = encoders['id_ejercicio'].transform([ejercicio_id])[0]
    
    # Crear array para predicción
    input_array = np.array([[features_dict.get(col, 0) for col in feature_cols]])
    
    # Cargar modelo y predecir
    modelo = tf.keras.models.load_model("h5/modelo_recomendador.h5")
    prediccion = modelo.predict(input_array, verbose=0)[0][0]
    
    return prediccion

print("\n=== Entrenamiento completado ===")
print("Recursos guardados:")
print("  - modelo_recomendador.h5 (modelo entrenado)")
print("  - encoders.pkl (codificadores de categorías)")
print("  - feature_cols.pkl (lista de features)")
print("\nPuedes usar la función 'predecir_valoracion()' para hacer predicciones.")