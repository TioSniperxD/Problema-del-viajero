# Problema-del-viajero
# Problema del viajero (TSP) en C++

Implementaciones en C++ del **problema del viajero** (*Traveling Salesman Problem*, TSP): encontrar la ruta de menor costo que visita cada ciudad exactamente una vez y regresa al punto de partida.

El repositorio contiene dos programas, uno por cada familia de algoritmos:

| Archivo | Familia | Algoritmos | Garantiza el óptimo |
|---|---|---|---|
| `tsp_exactos.cpp` | Exactos | Fuerza bruta, Held–Karp | Sí |
| `tsp_heuristicas.cpp` | Heurísticos | Vecino más cercano, 2-opt | No |

## Compilación y ejecución

Requiere un compilador de C++ (por ejemplo, `g++`).

```bash
g++ -O2 -o exactos tsp_exactos.cpp
./exactos

g++ -O2 -o heuristicas tsp_heuristicas.cpp
./heuristicas
```

## `tsp_exactos.cpp`

Resuelve una instancia pequeña de **4 ciudades (A, B, C, D)** definida con una matriz de distancias. Calcula la ruta óptima con dos métodos exactos y verifica que ambos coinciden.

**1. Fuerza bruta.** Fija la ciudad A como origen y prueba las (n − 1)! permutaciones de las demás ciudades con `next_permutation`. Calcula el costo de cada ruta y conserva la menor.

**2. Held–Karp (programación dinámica).** Usa una tabla `dp[máscara][j]`: el costo mínimo de salir de A, visitar el subconjunto de ciudades indicado por la máscara de bits y terminar en `j`. Reutiliza los resultados de subconjuntos más pequeños para construir los más grandes, y al final reconstruye la ruta hacia atrás.

| Método | Complejidad en tiempo | Memoria |
|---|---|---|
| Fuerza bruta | O(n!) | O(n) |
| Held–Karp | O(n²2ⁿ) | O(n2ⁿ) |

**Salida de ejemplo**

```
FUERZA BRUTA
Rutas revisadas: 6
Mejor ruta: A -> B -> D -> C -> A   costo = 80

HELD-KARP
Tamano de la tabla dp: 64
Mejor ruta: A -> C -> D -> B -> A   costo = 80
```

Ambos métodos encuentran el costo óptimo (80). Las dos rutas son la misma, recorrida en sentidos opuestos, porque la matriz es simétrica y existen dos recorridos con el mismo costo.

## `tsp_heuristicas.cpp`

Trabaja con **7 ciudades (A a G)** ubicadas en el plano. El costo entre dos ciudades es la distancia euclidiana. Aplica dos heurísticas en secuencia y muestra cuánto mejora la ruta.

**1. Vecino más cercano.** Parte de A y, en cada paso, va a la ciudad no visitada más cercana. Es muy rápido (O(n²)), pero su decisión es voraz y puede dejar tramos largos al final.

**2. 2-opt (búsqueda local).** Toma la ruta anterior y revierte tramos de la ruta cuando eso reduce el costo. Repite hasta que ningún cambio mejora la ruta, es decir, hasta llegar a un óptimo local.

**Salida de ejemplo**

```
VECINO MAS CERCANO
A -> F -> D -> C -> G -> B -> E -> A   costo = 36.7077

DESPUES DE 2-OPT
A -> F -> B -> E -> G -> C -> D -> A   costo = 30.9148
```

El 2-opt reduce el costo de 36,71 a 30,91 (aproximadamente un 16 %). Ese resultado no está garantizado como el óptimo global: es una ruta buena obtenida rápido.

## Cómo modificar las instancias

- **Exactos:** cambia `n`, el arreglo `nombre` y la matriz `d` en `main()`. Con la fuerza bruta no conviene pasar de unas 10 a 12 ciudades, y Held–Karp está limitado por la memoria, que crece como n·2ⁿ.
- **Heurísticos:** cambia `n`, `nombre` y las coordenadas `x` e `y` en la parte superior del archivo.

## Exactos frente a heurísticos

| | Exactos | Heurísticos |
|---|---|---|
| Resultado | Ruta óptima garantizada | Ruta buena, sin garantía |
| Tiempo | Crece exponencialmente | Polinómico |
| Tamaño práctico | Pocas decenas de ciudades como máximo | Miles de ciudades |
