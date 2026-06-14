# Comentarios y reflexiones sobre la implementación

## Autor
Aileen Parra

## Fecha
Junio 2026

---

## 1. Sobre la condición de parada

### ¿Dónde está implementada?
En el archivo `KMeans.cpp`, función `verificarConvergencia()`

### ¿Qué hace?
Compara los centroides de la iteración anterior con los de la iteración actual. Si todos se movieron menos de 1e-6 (tolerancia), el algoritmo converge.

### ¿Por qué es una buena condición de parada?

| Razón | Explicación |
|-------|-------------|
| 1 | Es la condición estándar en k-means, usada en libros y cursos |
| 2 | Evita iteraciones infinitas porque siempre termina |
| 3 | La tolerancia permite ajustar precisión vs velocidad |
| 4 | Es fácil de entender y explicar |
| 5 | Solo necesita comparar k centroides (rápido) |

### Parámetros de la función
- `centroidesViejos`: Centroides de la iteración anterior
- `centroidesNuevos`: Centroides que acabamos de calcular
- `tolerancia`: Si la distancia recorrida es menor a esto, convergió
- `k`: Número de clusters

---

## 2. Sobre la medida de dispersión

### ¿Cuál usé?
Suma de distancias euclidianas AL CUADRADO desde cada punto a su centroide.

### Fórmula
Dispersion = Σ ( (x_i - cx)² + (y_i - cy)² + (z_i - cz)² )


### ¿Por qué esta medida?
1. Es la medida estándar en k-means (WCSS)
2. Penaliza puntos lejanos (por el cuadrado)
3. Es fácil de calcular y comparar entre clusters
4. Funciona perfecto con el método del codo

### ¿Qué otras medidas consideré?
- **Desviación estándar**: No la usé porque es menos sensible a outliers
- **Radio del cluster**: No la usé porque un solo punto lejano la distorsiona
- **Varianza**: Similar pero promediada, prefiero la suma total

---

## 3. Sobre cómo evité el overfitting

### El problema
El Dr. Szilard advierte: "Una clasificación con más clusters de los necesarios va a darles la ilusión que tienen un mejor resultado, pero es un engaño"

### Mi solución: Método del codo (Elbow method)

**Implementación en `main.cpp` - función `encontrarMejorK()`**

### ¿Cómo funciona?
1. Pruebo k = 1, 2, 3, 4, 5, 6
2. Para cada k, calculo la dispersión TOTAL
3. Mido la MEJORA al aumentar k
4. Cuando la mejora es menor al 10% de la mejora inicial, ese es el "codo"

### Ejemplo visual

Dispersion
    |
    |  \
    |   \
    |    \
    |     \
    |      \____
    |           \___
    |              \___  ← CODO (k optimo)
    |                 \___
    |                    \___
    +------------------------→ k
     1   2   3   4   5   6

### ¿Por qué funciona?
Si agregar un cluster más apenas mejora la dispersión, ese cluster extra es "overfitting" (ruido, no estructura real).

### ¿Por qué funciona?
Si agregar un cluster más apenas mejora la dispersión, ese cluster extra es "overfitting" (ruido, no estructura real).

---

## 4. Sobre la arquitectura modular

### Estructura que usé
main.cpp ← Programa principal

↓
DataLoader.cpp ← Carga datos desde CSV
↓

KMeans.cpp ← Algoritmo k-means
↓

Archivos de salida ← clasificados.csv y summary.txt


### ¿Por qué modularicé así?

| Módulo | Responsabilidad | ¿Por qué separado? |
|--------|----------------|-------------------|
| DataLoader | Leer el CSV | Si cambia el formato, solo toco esto |
| KMeans | Algoritmo de clustering | Puedo probarlo sin cargar datos |
| main | Orquestar todo | Conecta los módulos y genera salida |

### ¿Cumple con lo que pide el Dr. Szilard?
✅ Entrada y salida en módulos separados  
✅ Uso de interfaces (.h) y referencias  
✅ Algoritmo encapsulado  
✅ Condición de parada en función separada  

---

## 5. Sobre la elección de k

### ¿Qué dice el Dr. Szilard?
> "No van a necesitar más de seis clusters"

### ¿Qué hace mi programa?

| Si el usuario pide... | El programa hace... |
|----------------------|---------------------|
| k = 1, 2, 3, 4, 5, 6 | Usa ese k (respeto su decisión) |
| k > 6 | Ignora al usuario, evalúa k=1..6 y elige el mejor |

### ¿Qué k elegí para el summary.txt?
Ejecuté el programa y el método del codo me dio **k = 3** como óptimo.

---

## 6. Dificultades que encontré

| Problema | Cómo lo resolví |
|----------|-----------------|
| Leer el CSV | Usé `getline()` y `stringstream` para separar por comas |
| Elegir centroides iniciales | Tomo puntos ALEATORIOS distintos del dataset |
| El algoritmo no convergía | Aumenté iteraciones máximas a 100 |
| Formato exacto de salida | Usé `std::fixed` y `std::setprecision(6)` |
| Letras A, B, C... | `static_cast<char>('A' + i)` |

---

## 7. Lo que aprendí haciendo esta práctica

1. **K-means es simple pero poderoso** - En menos de 200 líneas de código funciona muy bien
2. **La condición de parada es crítica** - Sin ella el algoritmo nunca termina
3. **El método del codo es útil** - Me da un criterio objetivo para elegir k
4. **Modularizar no es opcional** - En empresas serias como NagySoft es un REQUERIMIENTO
5. **Seguir especificaciones al pie de la letra** - El Dr. Szilard no perdona errores de formato

---

## 8. Declaración de originalidad

Declaro que:
- ✅ No recibí ayuda de otras personas
- ✅ Usé IA y fuentes web (como está permitido)
- ✅ Todo el código lo escribí YO adaptándolo a los requerimientos
- ✅ El programa cumple con TODAS las reglas del Dr. Szilard

**Firma:** Aileen

**Fecha:** Junio 2026
