#include <iostream>
//#include "Grafo.cpp"
// La inclusion de Grafo.cpp se comentó, por que ya esta incluido en BuscaCircuito.
#include "ExisteCircuito.cpp"
using namespace std;

int extraeBeforeOrAfterCharacter(string cadena, string antesODespuesOPeso)
{

    string inicio = "";
    string llegada = "";
    string peso = "";

    int con = 0;
    for (int i = 0; i < cadena.length(); i++)
    {
        if (cadena[i] == '|')
        {
            con++;
            continue;
        }
        if (con == 0)
        {
            inicio = inicio + cadena[i];
        }
        if (con == 1)
        {
            llegada = llegada + cadena[i];
        }
        if (con == 2)
        {
            peso = peso + cadena[i];
        }
    }

    if (antesODespuesOPeso == "inicio")
    {
        return stoi(inicio);
    }
    if (antesODespuesOPeso == "peso")
    {
        return stoi(peso);
    }

    return stoi(llegada);
}

void Boruvka(Grafo G)
{

    //  MST
    Grafo T;

    // Insertando los vertices
    Vertice *iV = G.primerVertice;
    while (iV != NULL)
    {
        T.insertarVertice(iV->dato);
        iV = iV->siguienteVertice;
    }

    // Bosque inicial formado solo con vertices
    T.mostrarGrafo();

    int inicio, llegada;      // Vertices de la arista a verificar
    int peso;                 // Peso de la arista a verificar
    string aristaMinimo = ""; // Arista minima en estrin "inicio|llegada|peso"

    int i = 1;
    int n = G.numeroDeAristas;

    int pesoMinimo = 0; // Peso minimo del MTS

    // Buscando la arista de peso minimo he incertamos a T
    // Siempre y cuando no se form circuito
    //"||" Todos los vertices fueron insertados

    while (aristaMinimo != "||")

    {
        // Extrayendo la arista de menor peso permitida (No forme circuito)
        aristaMinimo = G.getAristaDeMenorPeso();

        if (aristaMinimo != "||")
        {
            inicio = extraeBeforeOrAfterCharacter(aristaMinimo, "inicio");
            llegada = extraeBeforeOrAfterCharacter(aristaMinimo, "llegada");
            peso = extraeBeforeOrAfterCharacter(aristaMinimo, "peso");

            // Insertamos Arista
            T.insertarArista(inicio, llegada, peso);
            T.insertarArista(llegada, inicio, peso);

            pesoMinimo = pesoMinimo + peso;

            // Verificamos si con la insercion anterio se formó circuito
            bool existeCircuito = existeCircutio(T);
            if (existeCircuito)
            {

                // Si hay. Eliminamos la arista insertada.
                T.eliminarArista(inicio, llegada);
                T.eliminarArista(llegada, inicio);
                pesoMinimo = pesoMinimo - peso;
            }

            if (!existeCircuito)
            {
                cout << "\n"
                     << i << ") "
                     << "Insertando arista de menor peso:" << inicio << "-" << llegada << " (" << peso << ")" << endl;
                T.mostrarGrafo();

                i++;
            }
            // Eliminamos la arista  verificada
            // Es equivalente a marcar la arista como visitada
            // Pero considero que es eficiente si se la elimina
            // Ayuda en encontra la arista de menor peso
            // en la próxima busqueda.
            G.eliminarArista(inicio, llegada);
            G.eliminarArista(llegada, inicio);
        }
    }

    cout << "\nMST por al algoritmo Boruvka" << endl;
    T.mostrarGrafo();
    cout << "Peso minimo:" << pesoMinimo << endl;
}

int main()
{
    Grafo G;

    G.insertarVertice(0);
    G.insertarVertice(1);
    G.insertarVertice(2);
    G.insertarVertice(3);
    G.insertarVertice(4);
    G.insertarVertice(5);
    G.insertarVertice(6);
    G.insertarVertice(7);

    G.insertarArista(0, 6, 53);
    G.insertarArista(6, 0, 53);
    G.insertarArista(0, 1, 32);
    G.insertarArista(1, 0, 32);
    G.insertarArista(0, 2, 29);
    G.insertarArista(2, 0, 29);
    G.insertarArista(4, 3, 34);
    G.insertarArista(3, 4, 34);
    G.insertarArista(5, 3, 18);
    G.insertarArista(3, 5, 18);
    G.insertarArista(7, 4, 46);
    G.insertarArista(4, 7, 46);
    G.insertarArista(5, 4, 40);
    G.insertarArista(4, 5, 40);
    G.insertarArista(0, 5, 60);
    G.insertarArista(5, 0, 60);
    G.insertarArista(6, 4, 51);
    G.insertarArista(4, 6, 51);
    G.insertarArista(7, 0, 31);
    G.insertarArista(0, 7, 31);
    G.insertarArista(7, 6, 25);
    G.insertarArista(6, 7, 25);
    G.insertarArista(7, 1, 21);
    G.insertarArista(1, 7, 21);

    cout << "Grafo" << endl;
    G.mostrarGrafo();

    cout << "\nMST por al algoritmo Boruvka" << endl;
    Boruvka(G);
}