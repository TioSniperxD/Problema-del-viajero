#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n = 4;                       // ciudades: A B C D
    char nombre[] = {'A','B','C','D'};
    int d[4][4] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    // 1. fuerza bruta: se fija A y se prueban las (n-1)! permutaciones
    vector<int> ruta = {1, 2, 3};
    int mejor = 1e9;
    vector<int> mejorRuta;
    long long revisadas = 0;
    do {
        revisadas++;
        int costo = d[0][ruta[0]];
        for (int i = 0; i + 1 < n - 1; i++) costo += d[ruta[i]][ruta[i + 1]];
        costo += d[ruta[n - 2]][0];  // regreso al origen
        if (costo < mejor) { mejor = costo; mejorRuta = ruta; }
    } while (next_permutation(ruta.begin(), ruta.end()));

    cout << "FUERZA BRUTA" << endl;
    cout << "Rutas revisadas: " << revisadas << endl;
    cout << "Mejor ruta: A ";
    for (int c : mejorRuta) cout << "-> " << nombre[c] << " ";
    cout << "-> A   costo = " << mejor << endl;

    // 2. Held-Karp: dp[mascara][j] = costo minimo de salir de A,
    //    visitar las ciudades de la mascara y terminar en j
    const int INF = 1e9;
    vector<vector<int>> dp(1 << n, vector<int>(n, INF));
    dp[1][0] = 0;                    // solo A visitada
    for (int mascara = 1; mascara < (1 << n); mascara++)
        for (int j = 0; j < n; j++) {
            if (dp[mascara][j] == INF) continue;
            for (int k = 0; k < n; k++) {
                if ((mascara >> k) & 1) continue;
                int nueva = mascara | (1 << k);
                dp[nueva][k] = min(dp[nueva][k], dp[mascara][j] + d[j][k]);
            }
        }

    int todas = (1 << n) - 1, optimo = INF, ultima = 0;
    for (int j = 1; j < n; j++)
        if (dp[todas][j] + d[j][0] < optimo) { optimo = dp[todas][j] + d[j][0]; ultima = j; }

    vector<int> camino;              // reconstruir la ruta hacia atras
    int mascara = todas, j = ultima;
    while (j != 0) {
        camino.push_back(j);
        int previa = mascara ^ (1 << j);
        for (int i = 0; i < n; i++)
            if (((previa >> i) & 1) && dp[previa][i] + d[i][j] == dp[mascara][j]) {
                mascara = previa; j = i; break;
            }
    }

    cout << endl << "HELD-KARP" << endl;
    cout << "Tamano de la tabla dp: " << (1 << n) * n << endl;
    cout << "Mejor ruta: A ";
    for (int i = camino.size() - 1; i >= 0; i--) cout << "-> " << nombre[camino[i]] << " ";
    cout << "-> A   costo = " << optimo << endl;
    return 0;
}
