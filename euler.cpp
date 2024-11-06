/*****************************************************************************************************************************
Fecha: 6 noviembre 2024
Autor: Manuel Rincon
Tema: Taller Dijkstra
Estructuras de datos
******************************************************************************************************************************/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// Función para encontrar el ciclo de Euler en un grafo no dirigido
void encontrarCicloEuler(int inicio, vector<vector<int>>& grafo) {
    vector<int> ciclo;     // Para almacenar el ciclo de Euler
    stack<int> pila;       // Pila para manejar la exploración de caminos
    pila.push(inicio);     // Comenzamos desde el nodo de inicio
    
    while (!pila.empty()) {
        int nodo = pila.top();  // Obtenemos el nodo en la parte superior de la pila
        
        if (!grafo[nodo].empty()) {  // Si el nodo tiene aristas
            int vecino = grafo[nodo].back();  // Tomamos un vecino (nodo conectado)
            grafo[nodo].pop_back();           // Eliminamos la arista del nodo actual
            
            // También eliminamos la arista del lado del vecino para mantener el grafo no dirigido
            auto it = find(grafo[vecino].begin(), grafo[vecino].end(), nodo);
            if (it != grafo[vecino].end()) grafo[vecino].erase(it);
            
            pila.push(vecino);  // Continuamos con el vecino
        } else {
            // Si el nodo ya no tiene aristas, lo agregamos al ciclo
            ciclo.push_back(nodo + 1);  // +1 para mostrar nodos en formato 1-based
            pila.pop();                 // Eliminamos el nodo de la pila
        }
    }
    
    // Imprimir el ciclo de Euler encontrado
    cout << "Ciclo de Euler: ";
    for (int nodo : ciclo) {
        cout << nodo << " ";
    }
    cout << endl;
}

int main() {
    int n = 7; // Número de nodos en el grafo
    vector<vector<int>> grafo(n);

    // Definir las aristas del grafo no dirigido
    grafo[0] = {1, 3};
    grafo[1] = {0, 2};
    grafo[2] = {1, 3, 4};
    grafo[3] = {0, 2, 5};
    grafo[4] = {2, 5};
    grafo[5] = {3, 4, 6};
    grafo[6] = {5};

    int inicio = 0; // Nodo de inicio para encontrar el ciclo de Euler
    encontrarCicloEuler(inicio, grafo);

    return 0;
}
