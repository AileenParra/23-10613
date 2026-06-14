# Interacciones con Inteligencia Artificial

## Resumen
Durante el desarrollo de esta práctica, se utilizó Inteligencia Artificial (IA) como herramienta de apoyo para:
- Comprender conceptos teóricos
- Generar estructura de código
- Depurar errores
- Optimizar soluciones

---

## Interacción #1 - Consulta inicial

**Fecha:** Junio 2026

**Pregunta a la IA:**
> "Necesito implementar k-means clustering en C++ para puntos 3D. ¿Cuál es la estructura recomendada?"

**Respuesta de la IA:**
Sugirió usar `struct Coord_3D { double x; double y; double z; }` y un vector para almacenar los puntos.

**Mi comentario:**
Acepté la sugerencia porque cumple con el requerimiento del Dr. Szilard de usar esa estructura específica.

---

## Interacción #2 - Condición de parada

**Fecha:** Junio 2026

**Pregunta a la IA:**
> "¿Cómo encapsular la condición de parada en una función separada como pide el Dr. Szilard?"

**Respuesta de la IA:**
Proporcionó una función `verificarConvergencia()` que compara centroides viejos vs nuevos con una tolerancia.

**Mi comentario:**
Implementé exactamente esa función porque:
1. Está encapsulada
2. Tiene comentarios explicando parámetros
3. Es una condición de parada estándar y eficiente

---

## Interacción #3 - Medida de dispersión

**Fecha:** Junio 2026

**Pregunta a la IA:**
> "¿Qué medida de dispersión puedo usar para evaluar cada cluster?"

**Respuesta de la IA:**
Recomendó la suma de distancias cuadradas al centroide (WCSS - Within-Cluster Sum of Squares).

**Mi comentario:**
Elegí esta medida porque:
1. Es la estándar en k-means
2. Es fácil de calcular
3. Permite comparar clusters entre sí
4. Funciona bien con el método del codo

---

## Interacción #4 - Evitar overfitting

**Fecha:** Junio 2026

**Pregunta a la IA:**
> "¿Cómo evito overfitting al elegir el número de clusters? El Dr. Szilard dice que no se debe exagerar."

**Respuesta de la IA:**
Sugirió implementar el método del codo (Elbow method) con un umbral del 10% de mejora.

**Mi comentario:**
Implementé la función `encontrarMejorK()` que:
1. Evalúa k desde 1 hasta 6
2. Calcula la dispersión total para cada k
3. Encuentra el "codo" donde la mejora es menor al 10% de la mejora inicial

---

## Interacción #5 - Modularización

**Fecha:** Junio 2026

**Pregunta a la IA:**
> "¿Cómo divido el código en módulos separados como pide el Dr. Szilard?"

**Respuesta de la IA:**
Propuso:
- `DataLoader.h/.cpp` para carga de datos
- `KMeans.h/.cpp` para el algoritmo
- `main.cpp` para el programa principal

**Mi comentario:**
Seguí esta estructura porque:
1. Separa entrada/salida del algoritmo
2. Usa interfaces (.h) e implementaciones (.cpp)
3. Permite reutilización de código

---

## Interacción #6 - Generación de archivos de salida

**Fecha:** Junio 2026

**Pregunta a la IA:**
> "¿Cómo genero clasificados.csv y summary.txt en el formato exacto que pide el Dr. Szilard?"

**Respuesta de la IA:**
Proporcionó código usando `std::ofstream` con formato específico.

**Mi comentario:**
Implementé la solución porque:
1. Produce exactamente el formato requerido
2. Usa `std::fixed` y `std::setprecision(6)` para consistencia
3. Etiqueta con 'A'..'F' según el cluster

---

## Interacción #7 - Manejo de argumentos de línea de comandos

**Fecha:** Junio 2026

**Pregunta a la IA:**
> "¿Cómo implemento `cluster <k> <datos.csv>` como pide el Dr. Szilard?"

**Respuesta de la IA:**
Usar `int main(int argc, char* argv[])` y verificar `argc == 3`.

**Mi comentario:**
Implementé con validación de argumentos y mensaje de uso claro.

---

## Reflexión final sobre el uso de IA

**Beneficios:**
- Aceleró el desarrollo significativamente
- Ayudó a entender conceptos complejos (método del codo, dispersión)
- Proporcionó ejemplos de código funcional

**Limitaciones:**
- Fue necesario validar manualmente que el código cumple con TODOS los requerimientos del PDF
- Se ajustaron detalles específicos (formato de salida, etiquetas A-F)

**Conclusión:**
La IA fue una herramienta valiosa, pero el entendimiento conceptual y la adaptación a los requerimientos específicos fueron trabajo propio.
