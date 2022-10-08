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

string getAristaMinimaDeUnaFranjaDeUnSubGrafo(Grafo G, Grafo Ti)
{

    Vertice *iVG = G.primerVertice;
    Vertice *iVT = Ti.primerVertice;
    Arista *aristaFranja;

    string inicio = "";
    string llegada = "";
    int peso; // Supuesto peso minimo
    string pesoString = "";
    bool primerExisteAristaFranja = false;

    cout << "\nSiguiente Busqueda:\nFranja:" << endl;

    // Buscando la franja de menor peso
    while (iVT != NULL)
    {

        iVG = G.primerVertice;
        while (iVG != NULL)
        {

            // Condiciones para recorer y comparar toda la franja
            if (!Ti.existeVerticeDeDato(iVG->dato))
            {
                if (G.existeArista(iVT->dato, iVG->dato))
                {
                    aristaFranja = G.getArista(iVT->dato, iVG->dato);
                    cout << iVT->dato << "-" << iVG->dato << " (" << aristaFranja->peso << ")" << endl;
                    // Supuesto peso minimo(Solo ocurre una vez)
                    if (!primerExisteAristaFranja)
                    {
                        peso = aristaFranja->peso;
                        primerExisteAristaFranja = true;
                    }

                    // Encontrado la menor
                    if (aristaFranja->peso <= peso)
                    {
                        peso = aristaFranja->peso;
                        pesoString = to_string(peso);
                        inicio = to_string(iVT->dato);
                        llegada = to_string(iVG->dato);
                    }
                }
            }

            iVG = iVG->siguienteVertice;
        }
        iVT = iVT->siguienteVertice;
    }

    // Ocurre cuando ya no hay franja
    if (inicio == "" && llegada == "")
    {
        pesoString == ""; // Regresamoa a "" el peso por defecto asignado para la busqueda
    }

    return inicio + "|" + llegada + "|" + pesoString;
}

void Prim(Grafo G, DatoType v)
{

    Grafo T;

    // Insertando el primer vertice

    T.insertarVertice(v);

    cout << "\nGrafo T con el vetice inicial insertado:" << endl;
    T.mostrarGrafo();

    int inicio, llegada;
    int peso;
    string aristaMinimo = "";

    int i = 1;
    int n = G.numeroDeAristas;

    int pesoMinimo = 0;

    while (aristaMinimo != "||")

    {

        // Traemos el minimo de la franja
        aristaMinimo = getAristaMinimaDeUnaFranjaDeUnSubGrafo(G, T);

        if (aristaMinimo != "||")
        {
            inicio = extraeBeforeOrAfterCharacter(aristaMinimo, "inicio");
            llegada = extraeBeforeOrAfterCharacter(aristaMinimo, "llegada");
            peso = extraeBeforeOrAfterCharacter(aristaMinimo, "peso");

            T.insertarVertice(llegada);

            T.insertarArista(inicio, llegada, peso);
            T.insertarArista(llegada, inicio, peso);

            pesoMinimo = pesoMinimo + peso;

            cout << "\n"
                 << i << ") "
                 << "Insertando arista de menor peso:" << inicio << "-" << llegada << " (" << peso << ")" << endl;
            T.mostrarGrafo();
            i++;
        }
    }
    cout << "\nMST por al algoritmo Prim:" << endl;
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

    cout << "\nMST por al algoritmo Prim" << endl;
    Prim(G, 0);
}