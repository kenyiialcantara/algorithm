#include <iostream>
#include <queue>
#include <bits/stdc++.h>
using namespace std;

float *arrayFracciones;
string objetosSeleccionados;
float beneficioParcial;

struct objetos
{
    char nameObjeto;
    float volumen;
    float beneficio;
};

/// Nodo del arbol
struct Node
{
    int nivel;
    float beneficioSubarbol, limtSuperBeneficioSubarbol;
    float volumen;
};

// Algoritmo greddy
int MochilaGreddy(Node node, int n, float V, objetos objs[])
{

    if (node.volumen >= V)
        return 0;

    // Comenzamos desde al nodo actual
    float iBeneficio = node.beneficioSubarbol;
    int j = node.nivel + 1;
    float iVolumen = node.volumen;

    // Si la capacida aun no se sobrepasa
    while ((j < n) && (iVolumen + objs[j].volumen <= V))
    {
        iVolumen += objs[j].volumen;
        iBeneficio += objs[j].beneficio;
        arrayFracciones[j] = 1;
        j++;
    }

    // Si no se verifico aun todos los nodos
    // Sumar el beneficio del ultimo objeto como limite superior.
    if (j < n)
    {
        iBeneficio += (V - iVolumen) * objs[j].beneficio / objs[j].volumen;
        arrayFracciones[j] = objs[j].beneficio / objs[j].volumen;
    }

    beneficioParcial = iBeneficio;
    return iBeneficio;
}

// Comarar densidades para ordenar
bool comparar(objetos a, objetos b)
{
    double r1 = (double)a.beneficio / a.volumen;
    double r2 = (double)b.beneficio / b.volumen;
    return r1 > r2;
}

// Funciones complementarios de impresion
void imprimirElemSeleccionados(objetos objs[], int n)
{
    // Mostrando los objetos selecciondos
    cout << "Objetos\tfraccion xi" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << objs[i].nameObjeto << "\t" << arrayFracciones[i]
             << endl;
    }
}

// Funciones complementarios de impresion
void imprimirElemSeleccionadosOptimos(objetos objs[], int n)
{
    // Mostrando los objetos selecciondos
    cout << "Objetos\tfraccion xi" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << objs[i].nameObjeto << "\t" << objetosSeleccionados[i]
             << endl;
    }
}

void start(int n)
{
    arrayFracciones = new float[n];

    for (int i = 0; i < n; i++)
    {
        arrayFracciones[i] = 0;
    }
}

void guardarSolucionOptima(char name)
{

    objetosSeleccionados = objetosSeleccionados + " " + name;
}