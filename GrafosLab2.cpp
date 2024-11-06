/*****************************************************************************************************************************
Fecha: 6 noviembre 2024
Autor: Daniel Rosas
Tema: Taller Dijkstra
Estructuras de datos
******************************************************************************************************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();

void printPath(const vector<int>& prev, int j, vector<int>& path) {
    if (j == -1) return;
    printPath(prev, prev[j], path);
    path.push_back(j + 1);  // Sumamos 1 para mostrar el nodo en formato 1-based
}

void dijkstra(int inicio, const vector<vector<pair<int, int>>>& grafo) {
    int n = grafo.size();
    vector<int> distancias(n, INF);
    vector<int> prev(n, -1);
    distancias[inicio] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, inicio});

    while (!pq.empty()) {
        int distancia_actual = pq.top().first;
        int nodo_actual = pq.top().second;
        pq.pop();

        if (distancia_actual > distancias[nodo_actual]) continue;

        for (auto vecino : grafo[nodo_actual]) {
            int siguiente = vecino.first;
            int peso = vecino.second;

            if (distancias[nodo_actual] + peso < distancias[siguiente]) {
                distancias[siguiente] = distancias[nodo_actual] + peso;
                prev[siguiente] = nodo_actual;
                pq.push({distancias[siguiente], siguiente});
            }
        }
    }

    // Imprimir el resultado en formato de tabla
    cout << "Vértice\tDistancia\tCamino\n";
    for (int i = 0; i < n; ++i) {
        if (i != inicio) {  // Evita imprimir el camino desde el nodo a sí mismo
            cout << inicio + 1 << "->" << i + 1 << "\t";
            if (distancias[i] == INF) {
                cout << "Infinito\tNo alcanzable\n";
            } else {
                cout << distancias[i] << "\t\t";
                vector<int> path;
                printPath(prev, i, path);
                for (int j = 0; j < path.size(); ++j) {
                    cout << path[j];
                    if (j < path.size() - 1) cout << " ";
                }
                cout << "\n";
            }
        }
    }
}

int main() {
    int n = 7;  // Número de nodos en el grafo
    vector<vector<pair<int, int>>> grafo(n);

    // Definir las aristas del grafo con pares (nodo, peso)
    grafo[0].push_back({1, 1});
    grafo[0].push_back({2, 7});
    grafo[0].push_back({3, 6});
    grafo[1].push_back({4, 8});
    grafo[0].push_back({5, 4});
    grafo[1].push_back({6, 7});
    grafo[2].push_back({3, 6});
    grafo[3].push_back({4, 8});
    grafo[5].push_back({6, 4});

    int inicio = 0;  // Nodo de inicio
    dijkstra(inicio, grafo);

    return 0;
}
