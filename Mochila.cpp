#include <iostream>
#include <climits>
using namespace std;

// Variables globales
int n, M; // Numero de objetos
int **V;  // Tabla de Valor maximo de la Mochila en cada iteración
bool **E; // Tabla que guarda que objetos se estan seleccionando
int *sol; // Lista de elentos seleccionados

struct objetos
{
    char nameObjeto;
    int volumen;
    int costo;
};

// Funciones complementarios de impresion
void imprimirElemSeleccionados(objetos objs[])
{
    cout << "Elementos insertados:" << endl;
    for (int i = 0; i < n; i++)
    {
        if (sol[i] == 1)
        {
            cout << "*)";
            cout << "Nombre:" << objs[i].nameObjeto << " costo:" << objs[i].costo << " vol:" << objs[i].volumen << endl;
        }
    }
}

void imprimirTabla(objetos objs[])
{
    cout << "Tabla" << endl;

    cout << "  ";
    for (int i = 0; i <= M; i++)
    {
        cout << " " << i;
    }

    cout << "\n-----------------------" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << objs[i].nameObjeto << " ";
        for (int j = 0; j < M + 1; j++)
        {
            cout << " " << V[i][j];
        }
        cout << endl;
    }
}

void imprimirTablaBool(objetos objs[])
{
    cout << "Tabla" << endl;

    cout << "  ";
    for (int i = 0; i <= M; i++)
    {
        cout << " " << i;
    }

    cout << "\n-----------------------" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << objs[i].nameObjeto << " ";
        for (int j = 0; j < M + 1; j++)
        {
            cout << " " << E[i][j];
        }
        cout << endl;
    }
}

// Funciones importantes
int Max(int a, int b, int elem, int cap)
{
    if (a > b)
    {
        E[elem][cap] = false; // Sin agregar
        return a;
    }
    E[elem][cap] = true; // Agregamdo
    return b;
}

// Recopilando los objetos insertados
void ObjetosSeleccionados(int elem, int cap, objetos objs[]) // De atras para delante
{

    imprimirTablaBool(objs);
    sol = new int[n];
    int volMax = 0;

    for (int i = 0; i < n; i++)
    {
        sol[i] = 0;
    }
    while (elem >= 0 && cap >= 0)
    {
        if (E[elem][cap])
        {
            volMax = volMax + objs[elem].volumen;
            sol[elem] = 1;
            cap = cap - objs[elem].volumen; // De atras para delante
        }
        elem--;
    }

    imprimirElemSeleccionados(objs);
    cout << "Volumne maximo ocupado:" << volMax << endl;
}

// Algoritmo de  la mochila
int Mochila(int elem, int cap, objetos obj[])
{
    if (cap < 0)
    {
        return INT_MIN;
    }

    if (elem < 0 || cap == 0)
    {
        return 0;
    }
    else if (V[elem][cap] <= 0)
    {
        V[elem][cap] = Max(Mochila(elem - 1, cap, obj), Mochila(elem - 1, cap - obj[elem].volumen, obj) + obj[elem].costo, elem, cap);
    }

    return V[elem][cap];
}

void ProblemaMochila(char nameObj[], int volumenes[], int costos[])
{

    objetos myObjs[n];

    for (int i = 0; i < n; i++)
    {
        myObjs[i].nameObjeto = nameObj[i];
        myObjs[i].costo = costos[i];
        myObjs[i].volumen = volumenes[i];
    }

    cout << "Elementos a seleecionar:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << i << ") " << myObjs[i].nameObjeto << " " << myObjs[i].volumen << " " << myObjs[i].costo << endl;
    }

    // Tablas iniciales
    V = new int *[n];
    for (int i = 0; i < n; i++)
    {
        V[i] = new int[M];
    }

    E = new bool *[n];
    for (int i = 0; i < n; i++)
    {
        E[i] = new bool[M];
    }

    int costoMax = Mochila(n - 1, M, myObjs);
    imprimirTabla(myObjs);
    cout << "\nCosto optimo maximo:" << costoMax << endl;
    ObjetosSeleccionados(n - 1, M, myObjs);
}

int main()
{

    char nameObj[] = {'A', 'B', 'C', 'D', 'E'};
    int volumenes[] = {7, 5, 8, 9, 4};
    int costos[] = {10, 50, 20, 30, 60};
    M = 11; // Volumen maximo

    // char nameObj[] = {'A', 'B', 'C', 'D', 'E'};
    // int volumenes[] = {1, 3, 4, 5, 7};
    // int costos[] = {2, 5, 10, 14, 15};
    // M = 8; // Volumen maximo

    // char nameObj[] = {'A', 'B', 'C', 'D'};
    // int volumenes[] = {7, 5, 6, 8};
    // int costos[] = {3, 2, 1, 4};
    // M = 20; // Volumen maximo

    // Ejecucion del algoritmo
    n = sizeof(costos) / sizeof(int);
    cout << "Capacidad Maxima de la mochila:" << M << endl;
    ProblemaMochila(nameObj, volumenes, costos);

    return 0;
}