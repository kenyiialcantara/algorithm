#include <iostream>
using namespace std;

// Variables globales
int n, V;
float *arrayFracciones;

struct objetos
{
    char nameObjeto;
    float volumen;
    float beneficio;
};

// Seleccionamos al mejor candidato
int getIndexElemtoDeMayorDesidad(objetos objs[])
{
    int index = -1;
    float density = 0;
    for (int i = 0; i < n; i++)
    {
        if ((objs[i].beneficio / objs[i].volumen) > density && arrayFracciones[i] == 0)
        {
            density = objs[i].beneficio / objs[i].volumen;
            index = i;
        }
    }
    return index;
}

// Algoritmo de  la mochila
void Mochila(objetos objs[])
{

    float vol = 0;

    for (int i = 0; i < n; i++)
    {
        vol = vol + objs[i].volumen;
    }

    if (vol <= V)
    {
        cout << "La mochila tiene capacidad para llevar todos los objetos" << endl;
        return;
    }

    arrayFracciones = new float[n];

    for (int i = 0; i < n; i++)
    {
        arrayFracciones[i] = 0;
    }

    vol = 0;
    while (vol < V)
    {
        int i = getIndexElemtoDeMayorDesidad(objs); // Seleccionamos al mejor candidato
        if (vol + objs[i].volumen < V)
        {
            arrayFracciones[i] = 1;
            vol = vol + objs[i].volumen;
        }
        else
        {
            arrayFracciones[i] = (V - vol) / objs[i].volumen;
            vol = V;
        }
    }

    int beneficioMaximo = 0;

    for (int i = 0; i < n; i++)
    {
        beneficioMaximo = beneficioMaximo + objs[i].beneficio * arrayFracciones[i];
    }

    // Mostrando los objetos selecciondos
    cout << "Objetos\tfraccion xi\tbeneficio parcial" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << objs[i].nameObjeto << "\t" << arrayFracciones[i]
             << "\t\t" << objs[i].beneficio * arrayFracciones[i] << endl;
    }

    cout << "Beneficio maximo:" << beneficioMaximo << endl;
}

void ProblemaMochila(char nameObj[], float volumenes[], float beneficios[])
{

    objetos myObjs[n];

    for (int i = 0; i < n; i++)
    {
        myObjs[i].nameObjeto = nameObj[i];
        myObjs[i].beneficio = beneficios[i];
        myObjs[i].volumen = volumenes[i];
    }

    cout << "Elementos a seleecionar:" << endl;
    cout << "Objetos\tvolumen\tbeneficio" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << i << ") " << myObjs[i].nameObjeto << "\t" << myObjs[i].volumen << "\t" << myObjs[i].beneficio << endl;
    }
    cout << "\nCapacidad Maxima de la mochila:" << V << endl;
    Mochila(myObjs);
}

int main()
{

    // Ejemplo:

    char nameObj[] = {'A', 'B', 'C', 'D', 'E'};
    float volumenes[] = {10, 20, 30, 40, 50};
    float beneficios[] = {20, 30, 67, 40, 60};
    V = 100; // Volumen maximo

    // Ejecucion del algoritmo
    n = sizeof(beneficios) / sizeof(int);
    ProblemaMochila(nameObj, volumenes, beneficios);

    return 0;
}