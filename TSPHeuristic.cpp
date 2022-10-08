#include <bits/stdc++.h>
#include <iostream>
#include <climits>
#include "Grafo.cpp"
#include <vector>

using namespace std;

// Variables globales

int n;                     // Numero de lugares(vertices) que se tiene que visitar.
vector<char> caminoOptimo; // Lista de vertices que forman el camino optimo a recorrer.
vector<vector<char>> vecinos;
int distanciasMinima;
Grafo G;
int MAX_NUM_INTENTOS = 1000;

void mostrarVecino(int i)
{
    cout << "[";
    for (int j = 0; j < n; j++)
    {
        cout << vecinos[i][j] << "->";
    }
    cout << vecinos[i][n] << "]";
}

void crearVecinos()
{
    int sizeSub = 0;
    int inicio;

    int index = 0;

    while (sizeSub <= n + 1 - 2)
    {
        inicio = 1;
        while (inicio + sizeSub < n - 1)
        {

            vecinos.push_back(vector<char>(n + 1));
            for (int i = 0; i < caminoOptimo.size(); i++)
            {
                vecinos[index][i] = (caminoOptimo[i]);
            }

            reverse(vecinos[index].begin() + inicio, vecinos[index].begin() + inicio + sizeSub + 2);

            inicio++;
            index++;
        }
        sizeSub++;
    }
}

DatoTypeWeightEdge calcularDistanciaDelCaminoOPtimo()
{
    DatoTypeWeightEdge distancia = 0;
    cout << "Camino inicial:" << endl;

    cout << "[";
    for (int j = 0; j < n; j++)
    {
        cout << caminoOptimo[j] << "->";
    }
    cout << caminoOptimo[n] << "]\n";

    for (int i = 0; i < n; i++)
    {
        cout << "Para" << caminoOptimo[i] << "->" << caminoOptimo[i + 1] << endl;
        if (G.existeArista(caminoOptimo[i], caminoOptimo[i + 1]))
        {
            distancia = distancia + G.getPesoArista(caminoOptimo[i], caminoOptimo[i + 1]);
        }
        else
        {
            distancia = 10000000; // inficnito
            break;
        }
    }
    return distancia;
}

DatoTypeWeightEdge calcularDistanciaDelCamino(int index) // Funcion objetivo
{
    DatoTypeWeightEdge distancia = 0;
    for (int i = 0; i < n; i++)
    {

        if (G.existeArista(vecinos[index][i], vecinos[index][i + 1]))
        {
            cout << "Para " << vecinos[index][i] << "->" << vecinos[index][i + 1] << " " << G.getPesoArista(vecinos[index][i], vecinos[index][i + 1]) << endl;
            distancia = distancia + G.getPesoArista(vecinos[index][i], vecinos[index][i + 1]);
        }
        else
        {
            distancia = 10000000; // infinito
            break;
        }
    }
    return distancia;
}

void TSPHeuristic()
{
    // Creo la vecindad
    crearVecinos();
    DatoTypeWeightEdge distTemporal;
    distanciasMinima = calcularDistanciaDelCaminoOPtimo();
    cout << "Distancia:" << distanciasMinima << endl;
    cout << "\nCalculando para los vecinos:" << distanciasMinima << endl;
    // Calculando para cada vecino
    for (int i = 0; i < vecinos.size() && i < MAX_NUM_INTENTOS; i++)
    {
        // calculando la funcion objetivo
        cout
            << "\n"
            << i << ")" << endl;
        distTemporal = calcularDistanciaDelCamino(i);
        mostrarVecino(i);
        cout << " Distancia:" << distTemporal;
        if (distanciasMinima > distTemporal)
        {
            distanciasMinima = distTemporal;
            cout << " mejora";
            for (int k = 0; k < caminoOptimo.size(); k++)
            {
                caminoOptimo[k] = vecinos[i][k];
            }
        }
        cout << endl;
    }

    // Mostarndo resultados para esta heuritica
    cout << "\nSol:\nDistancia optima:" << distanciasMinima << endl;
    cout << "[";
    for (int j = 0; j < caminoOptimo.size() - 1; j++)
    {
        cout << caminoOptimo[j] << "->";
    }
    cout << caminoOptimo[caminoOptimo.size() - 1] << "]" << endl;
}

int main()
{

    G.insertarVertice('0');
    G.insertarVertice('1');
    G.insertarVertice('2');
    G.insertarVertice('3');
    G.insertarVertice('4');
    G.insertarVertice('5');
    G.insertarVertice('6');

    G.insertarArista('0', '1', 12);
    G.insertarArista('1', '0', 12);
    G.insertarArista('1', '2', 8);
    G.insertarArista('2', '1', 8);
    G.insertarArista('1', '3', 12);
    G.insertarArista('3', '1', 12);
    G.insertarArista('0', '2', 10);
    G.insertarArista('2', '0', 10);
    G.insertarArista('0', '6', 12);
    G.insertarArista('6', '0', 12);
    G.insertarArista('2', '6', 9);
    G.insertarArista('6', '2', 9);
    G.insertarArista('2', '3', 11);
    G.insertarArista('3', '2', 11);
    G.insertarArista('2', '4', 3);
    G.insertarArista('4', '2', 3);
    G.insertarArista('3', '4', 11);
    G.insertarArista('4', '3', 11);
    G.insertarArista('3', '5', 10);
    G.insertarArista('5', '3', 10);
    G.insertarArista('4', '5', 6);
    G.insertarArista('5', '4', 6);
    G.insertarArista('4', '6', 7);
    G.insertarArista('6', '4', 7);
    G.insertarArista('5', '6', 9);
    G.insertarArista('6', '5', 9);

    G.mostrarGrafo();

    n = G.numeroDeVertices;
    // Inicio de recorrido
    caminoOptimo = {'0', '1', '2', '3', '4', '5', '6', '0'};
    // Mostrando

    TSPHeuristic();

    return 0;
}