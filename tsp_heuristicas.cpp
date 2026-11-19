#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int n = 7;                           // ciudades: A B C D E F G en el plano
char nombre[] = {'A','B','C','D','E','F','G'};
double x[] = {9, 0, 7, 8, 0, 6, 5};
double y[] = {2, 5, 9, 6, 9, 0, 7};

double dist(int a, int b) { return hypot(x[a] - x[b], y[a] - y[b]); }

double costo(const vector<int>& r) {
    double c = 0;
    for (int i = 0; i < n; i++) c += dist(r[i], r[(i + 1) % n]);
    return c;
}

void mostrar(const vector<int>& r) {
    for (int c : r) cout << nombre[c] << " -> ";
    cout << nombre[r[0]] << "   costo = " << costo(r) << endl;
}

int main() {
    // 1. vecino mas cercano: desde A, siempre a la ciudad libre mas cercana
    vector<int> ruta = {0};
    vector<bool> visitada(n, false);
    visitada[0] = true;
    while ((int)ruta.size() < n) {
        int actual = ruta.back(), siguiente = -1;
        for (int j = 0; j < n; j++)
            if (!visitada[j] && (siguiente == -1 || dist(actual, j) < dist(actual, siguiente)))
                siguiente = j;
        ruta.push_back(siguiente);
        visitada[siguiente] = true;
    }
    cout << "VECINO MAS CERCANO" << endl;
    mostrar(ruta);

    // 2. 2-opt: se invierte un tramo de la ruta si eso baja el costo
    bool mejora = true;
    while (mejora) {
        mejora = false;
        for (int i = 1; i < n - 1; i++)
            for (int j = i + 1; j < n; j++) {
                double antes = costo(ruta);
                reverse(ruta.begin() + i, ruta.begin() + j + 1);
                if (costo(ruta) < antes - 1e-9) mejora = true;
                else reverse(ruta.begin() + i, ruta.begin() + j + 1);  // deshacer
            }
    }
    cout << endl << "DESPUES DE 2-OPT" << endl;
    mostrar(ruta);
    return 0;
}
