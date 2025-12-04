# app_fixed.py - VERSIÓN CORREGIDA
from flask import Flask, request, jsonify
from flask_cors import CORS
import os
import sys
import pandas as pd  # ¡IMPORTANTE! Importar pandas aquí
import numpy as np

app = Flask(__name__)
CORS(app)

print("="*60)
print("INICIANDO API DE EJERCICIOS")
print("="*60)

# Variables globales
model = None
exercises_df = None

def cargar_modelo_simple():
    """Carga el modelo de forma segura"""
    global model, exercises_df
    
    try:
        print("\n1. Intentando cargar TensorFlow...")
        import tensorflow as tf
        print(f"   ✅ TensorFlow {tf.__version__}")
        
        # Verificar si el archivo del modelo existe
        if os.path.exists("modelo_recomendador.h5"):
            print("2. Cargando modelo...")
            model = tf.keras.models.load_model("modelo_recomendador.h5")
            print("   ✅ Modelo cargado exitosamente")
        else:
            print("   ⚠️  Archivo modelo_recomendador.h5 no encontrado")
            print("   ℹ️  Usando modelo simulado para pruebas")
            model = "MOCK_MODEL"
        
        print("3. Cargando dataset...")
        
        if os.path.exists("data/megaGymDataset_filled.csv"):
            exercises_df = pd.read_csv("data/megaGymDataset_filled.csv")
            print(f"   ✅ Dataset cargado: {len(exercises_df)} ejercicios")
            
            # Renombrar columna ID si existe
            if "ID" in exercises_df.columns:
                exercises_df.rename(columns={"ID": "id_ejercicio"}, inplace=True)
        else:
            print("   ⚠️  Dataset no encontrado")
            # Crear dataset de ejemplo
            exercises_df = pd.DataFrame({
                'id_ejercicio': [1, 2, 3],
                'Title': ['Push-up', 'Squat', 'Plank'],
                'Type': ['Strength', 'Strength', 'Stability'],
                'BodyPart': ['Chest', 'Legs', 'Core'],
                'Equipment': ['Bodyweight', 'Bodyweight', 'Bodyweight'],
                'Level': ['Beginner', 'Beginner', 'Beginner'],
                'Rating': [8.5, 8.2, 8.8]
            })
            print("   ℹ️  Usando dataset de ejemplo")
        
        print("\n✅ SISTEMA INICIALIZADO CORRECTAMENTE")
        
    except Exception as e:
        print(f"\n❌ ERROR durante la carga: {e}")
        import traceback
        traceback.print_exc()
        print("💡 Usando modo de emergencia...")
        model = "EMERGENCY_MODE"
        exercises_df = pd.DataFrame({
            'id_ejercicio': [1, 2, 3],
            'Title': ['Emergency Ex 1', 'Emergency Ex 2', 'Emergency Ex 3'],
            'Type': ['Strength', 'Cardio', 'Flexibility'],
            'BodyPart': ['Full Body', 'Full Body', 'Full Body']
        })

# Cargar recursos al iniciar
cargar_modelo_simple()

# ========== ENDPOINTS ==========

@app.route('/')
def home():
    return jsonify({
        'api': 'Exercise Recommendation API',
        'version': '1.0',
        'status': 'active',
        'model_loaded': model not in [None, "EMERGENCY_MODE", "MOCK_MODEL"],
        'exercises_loaded': exercises_df is not None,
        'total_exercises': len(exercises_df),
        'endpoints': {
            'GET /': 'API information',
            'GET /status': 'System status',
            'GET /test': 'Simple test',
            'GET /recommend': 'Get recommendations (URL params)',
            'POST /recommend': 'Get recommendations (JSON body)',
            'GET /exercises': 'List exercises'
        }
    })

@app.route('/status')
def status():
    return jsonify({
        'model': 'loaded' if model and model not in ["EMERGENCY_MODE", "MOCK_MODEL"] else 'simulated',
        'exercises': len(exercises_df),
        'api': 'ready'
    })

@app.route('/test')
def test():
    """Endpoint de prueba simple"""
    return jsonify({
        'success': True,
        'message': 'API is working!',
        'model_status': 'loaded' if model not in ["EMERGENCY_MODE", "MOCK_MODEL"] else 'simulated',
        'dataframe_info': {
            'shape': exercises_df.shape,
            'columns': list(exercises_df.columns)
        }
    })

@app.route('/recommend', methods=['GET', 'POST'])
def recommend():
    """Endpoint principal de recomendación"""
    try:
        print(f"\n📥 Nueva petición: {request.method}")
        
        # Obtener parámetros según el método
        if request.method == 'POST':
            data = request.get_json() or {}
            genero = data.get('genero', 'male')
            edad = data.get('edad', '30')
            peso = data.get('peso', '70')
            altura = data.get('altura', '170')
            top_n = data.get('top_n', '5')
        else:  # GET
            genero = request.args.get('genero', 'male')
            edad = request.args.get('edad', '30')
            peso = request.args.get('peso', '70')
            altura = request.args.get('altura', '170')
            top_n = request.args.get('top_n', '5')
        
        # Convertir a tipos adecuados
        try:
            edad = float(edad)
            peso = float(peso)
            altura = float(altura)
            top_n = int(top_n)
        except ValueError:
            return jsonify({
                'success': False,
                'error': 'Parámetros numéricos inválidos',
                'tip': 'Asegúrate que edad, peso, altura y top_n sean números'
            }), 400
        
        print(f"   Parámetros: {genero}, {edad}años, {peso}kg, {altura}cm, top_n={top_n}")
        
        # Validar parámetros básicos
        if genero not in ['male', 'female', 'other']:
            genero = 'male'
        
        # Limitar top_n a un rango razonable
        if top_n < 1 or top_n > 20:
            top_n = min(max(top_n, 1), 20)
        
        # Generar recomendaciones
        recommendations = []
        
        # Tomar una muestra de ejercicios
        sample_size = min(top_n * 3, len(exercises_df))
        sample_df = exercises_df.head(sample_size).copy()
        
        for idx, row in sample_df.iterrows():
            # Simular puntuación basada en parámetros del usuario
            base_score = 7.0
            
            # Ajustes según género
            if genero == 'male':
                base_score += 0.3
            elif genero == 'female':
                base_score += 0.2
            
            # Ajustes según edad
            if 20 <= edad <= 40:
                base_score += 0.4
            elif 41 <= edad <= 60:
                base_score += 0.2
            
            # Ajustes según BMI
            bmi = peso / ((altura/100) ** 2)
            if 18.5 <= bmi <= 25:
                base_score += 0.3
            
            # Variación aleatoria
            import random
            variation = random.uniform(-0.5, 0.5)
            final_score = round(base_score + variation + (idx * 0.02), 1)
            
            # Asegurar rango 0-10
            final_score = max(0.0, min(10.0, final_score))
            
            recommendations.append({
                'id': int(row.get('id_ejercicio', idx + 1)),
                'title': str(row.get('Title', f'Ejercicio {idx + 1}')),
                'type': str(row.get('Type', 'Strength')),
                'body_part': str(row.get('BodyPart', 'Full Body')),
                'equipment': str(row.get('Equipment', 'Bodyweight')),
                'level': str(row.get('Level', 'Beginner')),
                'original_rating': float(row.get('Rating', 0.0)),
                'predicted_score': final_score
            })
        
        # Ordenar por puntuación predicha (mayor a menor)
        recommendations.sort(key=lambda x: x['predicted_score'], reverse=True)
        
        # Tomar solo top_n
        final_recommendations = recommendations[:top_n]
        
        return jsonify({
            'success': True,
            'method': request.method,
            'user': {
                'gender': genero,
                'age': edad,
                'weight': peso,
                'height': altura,
                'bmi': round(bmi, 1)
            },
            'recommendations': final_recommendations,
            'total_evaluated': len(recommendations),
            'total_returned': len(final_recommendations),
            'note': 'Using simulated predictions based on user parameters'
        })
        
    except Exception as e:
        print(f"❌ Error en recommend: {e}")
        import traceback
        traceback.print_exc()
        
        return jsonify({
            'success': False,
            'error': str(e),
            'tip': 'Check the server logs for details',
            'example_url': 'http://localhost:5000/recommend?genero=male&edad=30&peso=75&altura=175&top_n=3'
        }), 500

@app.route('/exercises', methods=['GET'])
def get_exercises():
    """Lista de ejercicios disponibles"""
    try:
        limit = int(request.args.get('limit', 10))
        
        # Limitar resultados
        limited_df = exercises_df.head(limit)
        
        # Convertir a diccionario
        exercises = []
        for _, row in limited_df.iterrows():
            exercise = {}
            for col in limited_df.columns:
                value = row[col]
                if pd.notna(value):  # Solo incluir valores no nulos
                    exercise[col] = value
            exercises.append(exercise)
        
        return jsonify({
            'success': True,
            'count': len(exercises),
            'total_available': len(exercises_df),
            'exercises': exercises
        })
        
    except Exception as e:
        print(f"❌ Error en exercises: {e}")
        return jsonify({
            'success': False,
            'error': str(e)
        }), 500

# ========== ERROR HANDLERS ==========

@app.errorhandler(404)
def not_found(error):
    return jsonify({
        'success': False,
        'error': 'Endpoint not found',
        'available_endpoints': ['/', '/status', '/test', '/recommend', '/exercises']
    }), 404

@app.errorhandler(405)
def method_not_allowed(error):
    return jsonify({
        'success': False,
        'error': 'Method not allowed',
        'tip': 'This endpoint only accepts GET requests'
    }), 405

@app.errorhandler(500)
def internal_error(error):
    return jsonify({
        'success': False,
        'error': 'Internal server error',
        'tip': 'Check server logs for details'
    }), 500

# ========== EJECUCIÓN ==========

if __name__ == '__main__':
    print("\n" + "="*60)
    print("🚀 API LISTA EN http://localhost:5000")
    print("="*60)
    print(f"📊 Total ejercicios: {len(exercises_df)}")
    print(f"🤖 Modelo: {'Cargado' if model not in ['MOCK_MODEL', 'EMERGENCY_MODE'] else 'Simulado'}")
    
    print("\n📡 ENDPOINTS DISPONIBLES:")
    print("  GET  /              - Información de la API")
    print("  GET  /status        - Estado del sistema")
    print("  GET  /test          - Prueba simple")
    print("  GET  /exercises     - Lista de ejercicios")
    print("  GET  /recommend     - Recomendaciones (parámetros URL)")
    print("  POST /recommend     - Recomendaciones (cuerpo JSON)")
    
    print("\n🔧 EJEMPLOS DE USO (curl):")
    print("  # Información básica")
    print("  curl http://localhost:5000/")
    print("\n  # Prueba simple")
    print("  curl http://localhost:5000/test")
    print("\n  # Recomendación básica")
    print("  curl 'http://localhost:5000/recommend?genero=male&edad=30&peso=75&altura=175'")
    print("\n  # Con parámetros específicos")
    print("  curl 'http://localhost:5000/recommend?genero=male&edad=42&peso=87.4&altura=169&top_n=5'")
    print("\n  # Listar ejercicios")
    print("  curl 'http://localhost:5000/exercises?limit=5'")
    
    print("\n🔍 EJEMPLOS DE USO (navegador):")
    print("  http://localhost:5000/recommend?genero=male&edad=30&peso=75&altura=175&top_n=3")
    print("  http://localhost:5000/recommend?genero=female&edad=25&peso=60&altura=165&top_n=5")
    
    print("\n" + "="*60)
    print("✅ API LISTA PARA USAR")
    print("="*60 + "\n")
    
    app.run(host='0.0.0.0', port=5000, debug=True)