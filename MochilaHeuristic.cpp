#include <bits/stdc++.h>
#include <iostream>
#include <climits>
#include <vector>
#include <math.h>

using namespace std;

int n;              // Numero de objetos
int indexOptimo;    // Vacontener 0 / 1s
vector<int> vecino; // Vacontener 0 / 1s .
vector<vector<int>> vecinos;
float optimoBeneficio;
int MAX_NUM_INTENTOS = 100;
float V;

struct objetos
{
    char nameObjeto;
    int beneficio;
    int volumen;
};

void mostrarVecinos()
{

    for (int i = 0; i < vecinos.size(); i++)
    {

        cout << "[";
        for (int j = 0; j < vecino.size(); j++)
        {
            cout << vecinos[i][j] << " ";
        }
        cout << "]" << endl;
    }
}

void generarVecinos()
{
    vector<int> aux;

    for (int i = 0; i < vecino.size(); i++)
    {
        aux.push_back(vecino[i]);
    }

    int k = 1;
    while (k < n)
    {
        vecinos.push_back(aux);
        for (int i = k; i < n; i++)
        {
            vector<int> aux2;

            for (int j = 0; j < vecino.size(); j++)
            {
                aux2.push_back(aux[j]);
            }
            aux2[i] = 1;
            vecinos.push_back(aux2);
        }
        aux[k] = 1;
        k++;
    }
}

float calculaBeneficio(objetos objs[], int index) // Funcion Objetivo
{
    cout << "Para: [";
    float beneficio = 0;
    for (int i = 0; i < vecino.size(); i++)
    {
        cout << vecinos[index][i] << " ";
        beneficio = beneficio + vecinos[index][i] * objs[i].beneficio;
    }
    cout << "]" << endl;
    return beneficio;
}

float calculaVolumen(objetos objs[], int index) // Funcion Objetivo
{

    float vol = 0;
    for (int i = 0; i < vecino.size(); i++)
    {

        vol = vol + vecinos[index][i] * objs[i].volumen;
    }

    return vol;
}

void MochilaHeuristic(objetos objs[])
{

    // Genrando vecinos
    generarVecinos();
    cout << "Vecinos" << endl;
    mostrarVecinos();
    int i = 0;
    float iBeneficio;
    float iVol;
    while (i < vecinos.size() && i < MAX_NUM_INTENTOS)
    {
        // Calculando en la funcion objetivo
        iBeneficio = calculaBeneficio(objs, i);
        iVol = calculaVolumen(objs, i);
        if (iBeneficio > optimoBeneficio && V > iVol)
        {

            optimoBeneficio = iBeneficio;
            indexOptimo = i;
            cout << "max beneficio:" << optimoBeneficio << " Mejora" << endl;
        }
        else
        {
            cout << "max beneficio:" << optimoBeneficio << " No mejora" << endl;
        }
        i++;
    }

    cout << "\nBeneficio Optimo:" << optimoBeneficio << endl;
    // Mostrado objetos:
    for (i = 0; i < vecino.size(); i++)
    {
        if (vecinos[indexOptimo][i] == 1)
        {
            cout << objs[i].nameObjeto << " ";
        }
    }
    cout << endl;
}

int main()
{

    // //Ejemplo 1:
    V = 1100; // Capacida maxima de la mochila
    objetos objs[] = {{'A', 10, 200}, {'B', 14, 300}, {'C', 31, 400}, {'D', 48, 600}, {'E', 60, 800}};

    n = sizeof(objs) / sizeof(objs[0]);

    // Solucion inicial
    vecino = {1, 0, 0, 0, 0};
    cout << "\nHeuritica" << endl;
    MochilaHeuristic(objs);
    return 0;
}