#include <iostream>
#include <queue>
#include <bits/stdc++.h>

// Se utliza el archivo AuxAlgoritmos
// Ahi esta el algoritmo greddy y estructura y funciones adicionales
// Que se utiliza para calcular el limite superior para el podado.
#include "AuxAlgoritmos.cpp"

using namespace std;

// Cola  para guardamos los nodos
queue<Node> Q; //(FIFO) Recorrido por anchura del arbol

int MochilaBranchAndBound(int V, objetos objs[], int n)
{
    // Hijos
    Node u, v;

    // Inicializando
    u.nivel = -1;
    u.beneficioSubarbol = u.volumen = 0;
    Q.push(u);
    float maxBeneficio = 0;

    while (!Q.empty())
    {

        // REVISANDO LOS NODOS VIVOS
        u = Q.front();
        Q.pop();

        // Nivel 0
        if (u.nivel == -1)
            v.nivel = 0;

        // Termina revisar el subarbol
        if (u.nivel == n - 1)
        {

            cout << "No factible" << endl;
            continue;
        }

        v.nivel = u.nivel + 1;
        // Sumando volumen y beneficio del nodo actual
        v.volumen = u.volumen + objs[v.nivel].volumen;
        v.beneficioSubarbol = u.beneficioSubarbol + objs[v.nivel].beneficio;

        if (v.volumen <= V && v.beneficioSubarbol > maxBeneficio)
        {
            guardarSolucionOptima(objs[v.nivel].nameObjeto);
            maxBeneficio = v.beneficioSubarbol;
        }

        // Obteniedo el limite superior para decidir
        v.limtSuperBeneficioSubarbol = MochilaGreddy(v, n, V, objs);

        //   Tomado el objeto
        if (v.limtSuperBeneficioSubarbol > maxBeneficio)
        {
            cout << "\nNivel:" << v.nivel << endl;
            imprimirElemSeleccionados(objs, n);
            cout << "Beneficion parcial:" << beneficioParcial << endl;
            Q.push(v); // PASANDO A NODOS VIVOS
        }
        // Sino, No agregamos, es decir Podamos.

        // Sin tomar el objeto
        v.volumen = u.volumen;
        v.beneficioSubarbol = u.beneficioSubarbol;
        v.limtSuperBeneficioSubarbol = MochilaGreddy(v, n, V, objs);

        if (v.limtSuperBeneficioSubarbol > maxBeneficio)
        {
            cout << "\nNivel:" << v.nivel << endl;
            imprimirElemSeleccionados(objs, n);
            cout << "Beneficion parcial:" << beneficioParcial << endl;
            Q.push(v); // PASANDO A NODOS VIVOS
        }
        // Sino, No agregamos, es decir Podamos.
    }

    return maxBeneficio;
}

int main()
{
    // //Ejemplo 1:
    float V = 1100; // Capacida maxima de la mochila
    objetos objs[] = {{'A', 800, 60}, {'B', 600, 48}, {'C', 300, 14}, {'D', 400, 31}, {'E', 200, 10}};

    int n = sizeof(objs) / sizeof(objs[0]);

    start(n);

    // Ordenamos los objetos por densidad
    sort(objs, objs + n, comparar);

    float bMax = MochilaBranchAndBound(V, objs, n);
    cout << "\nBenefico maximo:" << bMax
         << endl;
    cout << "\nObjetos selccionados:" << objetosSeleccionados
         << endl;

    return 0;
}