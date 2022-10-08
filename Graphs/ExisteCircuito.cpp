#include <iostream>
#include "Grafo.cpp"
using namespace std;

// Definiendo el tipo de dato
typedef int DatoType;

// Declarando variables globales
int *visit;

// Busqueda por dato
string mostrarArrayVisit(int n)
{
    string res = "[";
    for (int i = 0; i < n; i++)
    {
        res = res + " " + to_string(visit[i]);
    }
    return res + "]";
}

bool buscaCircuitoDFS(Grafo G, DatoType iv, DatoType ivpadre)
{

    visit[iv] = 1;
    Vertice *v = G.buscarVertice(iv);
    Arista *w = v->primerAyacente;

    while (w != NULL)
    {

        if (visit[w->verticeDestino->dato] == -1)
        {
            if (buscaCircuitoDFS(G, w->verticeDestino->dato, iv))
            {
                return true;
            }
        }
        else
        {
            if (ivpadre != w->verticeDestino->dato)
            {
                return true;
            }
        }

        w = w->siguienteArista;
    }
    return false;
}

bool existeCircutio(Grafo G)
{
    // Antes de comenzar, verificamos si el grafo no tiene vertices
    if (G.numeroDeVertices == 0)
    {
        cout << "El grafo no tiene vertices" << endl;
        return false;
    }

    // Declaramos Array visit que guarda si el vertice ya fue visitado
    visit = new int[G.numeroDeVertices];

    // Inicializamos todos los campos del array orden con -1.
    // Es decir, aun no fueron visitados.

    for (int i = 0; i < G.numeroDeVertices; i++)
    {
        visit[i] = -1;
    }

    for (int i = 0; i < G.numeroDeVertices; i++)
    {
        if (visit[i] == -1)
        {
            if (buscaCircuitoDFS(G, i, i))
            {
                return true;
            }
        }
    }

    return false;
}

// Busqueda por indice

bool buscaCircuitoDFSByIndex(Grafo G, DatoType indexV, DatoType indexVpadre)
{

    visit[indexV] = 1;
    Vertice *v = G.buscarVerticeByIndex(indexV);
    Arista *w = v->primerAyacente;

    while (w != NULL)
    {

        if (visit[w->verticeDestino->indexVertice] == -1)
        {
            if (buscaCircuitoDFSByIndex(G, w->verticeDestino->indexVertice, indexV))
            {
                return true;
            }
        }
        else
        {
            if (indexVpadre != w->verticeDestino->indexVertice)
            {
                return true;
            }
        }

        w = w->siguienteArista;
    }
    return false;
}

bool existeCircutioByIndex(Grafo G)
{
    // Antes de comenzar, verificamos si el grafo no tiene vertices
    if (G.numeroDeVertices == 0)
    {
        cout << "El grafo no tiene vertices" << endl;
        return false;
    }

    // Declaramos Array visit que guarda si el vertice ya fue visitado
    visit = new int[G.numeroDeVertices];

    // Inicializamos todos los campos del array orden con -1.
    // Es decir, aun no fueron visitados.

    for (int i = 0; i < G.numeroDeVertices; i++)
    {
        visit[i] = -1;
    }

    for (int i = 0; i < G.numeroDeVertices; i++)
    {
        if (visit[i] == -1)
        {
            if (buscaCircuitoDFSByIndex(G, i, i))
            {
                return true;
            }
        }
    }

    return false;
}

// int main()
// {
//     Grafo G;

//     // G.insertarVertice(0);
//     // G.insertarVertice(1);
//     // G.insertarVertice(2);
//     G.insertarVertice(3);
//     // G.insertarVertice(4);
//     G.insertarVertice(5);
//     // G.insertarVertice(6);
//     // G.insertarVertice(7);

//     G.insertarAristaEnOrdenPeso(5, 3, 23);
//     G.insertarAristaEnOrdenPeso(3, 5, 23);

//     G.mostrarGrafo();
//     cout
//         << "Existe cicuito: " << existeCircutioByIndex(G) << endl;
//     cout << mostrarArrayVisit(G.numeroDeVertices) << endl;

//     return 0;
// }