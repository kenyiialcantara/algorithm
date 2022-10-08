#include <iostream>
using namespace std;

// Definiendo el tipo de dato
typedef char DatoTypeVertex;
typedef float DatoTypeWeightEdge;

class Arista;

// Definiendo la clase vertice (Varinate del Nodo)
class Vertice
{
public:
    DatoTypeVertex name;       // Nombre o dato del vertice
    Vertice *siguienteVertice; // Puntero al siguiente vertice de la lista de directorios
    Arista *primerAyacente;    // Puntero al primer adyacente
    int indexVertice;

    // Contructor
    Vertice()
    {
        siguienteVertice = NULL;
        primerAyacente = NULL;
        indexVertice = 0;
    }
};

// Definiendo arista
class Arista
{
public:
    Vertice *verticeDestino; // Puntero al vertice de llegada
    Arista *siguienteArista; // Puntero al siguiente arista en la lista de adyacencia
    DatoTypeWeightEdge peso;

    // Constructor

    Arista()
    {
        verticeDestino = NULL;
        siguienteArista = NULL;
        peso = 1;
    }
};

class Grafo
{
public:
    Vertice *primerVertice; // Definien el primer nodo
    int numeroDeVertices;
    int numeroDeAristas;

    // Constructor
    Grafo()
    {
        primerVertice = NULL; // Declaramos el primer nodo nullo. Por que la lista esta vacía al principio
        numeroDeVertices = 0;
        numeroDeAristas = 0;
    }

    // Metodos
    void insertarVertice(DatoTypeVertex);
    void insertarArista(DatoTypeVertex, DatoTypeVertex);                     // Arista con peso 1 por defecto.
    void insertarArista(DatoTypeVertex, DatoTypeVertex, DatoTypeWeightEdge); // Arista con peso.
    Vertice *getVertice(DatoTypeVertex);
    int getIndexVertice(DatoTypeVertex);
    Vertice *getVerticeByIndex(int);
    DatoTypeVertex getDatoVerticeByIndex(int);
    Arista *getArista(DatoTypeVertex, DatoTypeVertex);
    DatoTypeWeightEdge getPesoArista(DatoTypeVertex, DatoTypeVertex);
    DatoTypeWeightEdge getPesoAristaByIndex(int, int);
    bool existeVerticeDeDato(DatoTypeVertex);
    bool existeArista(DatoTypeVertex, DatoTypeVertex);
    bool existeAristaByIndex(int, int);
    void mostrarGrafo();
    int getGradoVerticeByIndex(int);
};

int Grafo::getGradoVerticeByIndex(int index)
{
    Vertice *v = getVerticeByIndex(index);
    Arista *iArista = v->primerAyacente;
    int grado = 0;
    while (iArista != NULL)
    {
        grado++;
        iArista = iArista->siguienteArista;
    }
    return grado;
}

// Methods
void Grafo::insertarVertice(DatoTypeVertex d)
{
    // Asignando la direccion de memoria del nuevo vertice
    // Y este apunta al anterior primer nodo.
    // Nota: "new" retorna un puntero, en comparacion a otros leguages.
    Vertice *nuevo = new Vertice();
    nuevo->name = d;
    nuevo->indexVertice = numeroDeVertices; // Indexamos un vertice con un int (Esto para poder usarlo si el dato fuera un string)
    // O si el grafo esta dado con datos enteros consecutivos V = {0,1,..}; Esto ayudara en los algoritmos.

    if (primerVertice == NULL)
    {
        primerVertice = nuevo;
        numeroDeVertices++;
    }
    else
    {
        Vertice *index = primerVertice;
        while (index->siguienteVertice != NULL)
        {
            index = index->siguienteVertice;
        }
        index->siguienteVertice = nuevo;
        numeroDeVertices++;
    }
}

void Grafo::insertarArista(DatoTypeVertex x, DatoTypeVertex y) // Arista de peso 1 (Por defecto)
{
    Vertice *indexVertice = primerVertice;

    while (indexVertice != NULL)
    {
        if (indexVertice->name == x)
        {

            Arista *nuevo = new Arista();
            Arista *indexArista = indexVertice->primerAyacente;
            nuevo->verticeDestino = getVertice(y);
            if (indexArista == NULL)
            {
                indexVertice->primerAyacente = nuevo;
            }
            else
            {
                while (indexArista->siguienteArista != NULL)
                {
                    indexArista = indexArista->siguienteArista;
                }
                indexArista->siguienteArista = nuevo;
            }
        }
        indexVertice = indexVertice->siguienteVertice;
    }
    numeroDeAristas++;
}

void Grafo::insertarArista(DatoTypeVertex x, DatoTypeVertex y, DatoTypeWeightEdge peso) // Arista de peso 1 (Por defecto)
{
    Vertice *indexVertice = primerVertice;

    while (indexVertice != NULL)
    {
        if (indexVertice->name == x)
        {

            Arista *nuevo = new Arista();
            nuevo->peso = peso;
            Arista *indexArista = indexVertice->primerAyacente;
            nuevo->verticeDestino = getVertice(y);
            if (indexArista == NULL)
            {
                indexVertice->primerAyacente = nuevo;
            }
            else
            {
                while (indexArista->siguienteArista != NULL)
                {
                    indexArista = indexArista->siguienteArista;
                }
                indexArista->siguienteArista = nuevo;
            }
        }
        indexVertice = indexVertice->siguienteVertice;
    }
    numeroDeAristas++;
}

Vertice *Grafo::getVertice(DatoTypeVertex d)
{
    Vertice *n = primerVertice;

    while (n != NULL)
    {

        if (n->name == d)
        {
            break;
        }
        n = n->siguienteVertice;
    }
    return n;
}

int Grafo::getIndexVertice(DatoTypeVertex d)
{
    Vertice *n = primerVertice;

    while (n != NULL)
    {

        if (n->name == d)
        {
            break;
        }
        n = n->siguienteVertice;
    }
    return n->indexVertice;
}

Vertice *Grafo::getVerticeByIndex(int i)
{
    Vertice *n = primerVertice;

    while (n != NULL)
    {

        if (n->indexVertice == i)
        {
            break;
        }
        n = n->siguienteVertice;
    }
    return n;
}

DatoTypeVertex Grafo::getDatoVerticeByIndex(int index)
{
    Vertice *iVertice = primerVertice;
    while (iVertice != NULL)
    {
        if (iVertice->indexVertice == index)
            break;
        iVertice = iVertice->siguienteVertice;
    }
    return iVertice->name;
}

bool Grafo::existeVerticeDeDato(DatoTypeVertex dato)
{

    Vertice *indexV = primerVertice;

    while (indexV != NULL)
    {

        if (indexV->name == dato)
        {
            return true;
        }

        indexV = indexV->siguienteVertice;
    }

    return false;
}

Arista *Grafo::getArista(DatoTypeVertex dv, DatoTypeVertex du)
{
    Vertice *v = getVertice(dv);
    Arista *arista = v->primerAyacente;
    Arista *indexArista = v->primerAyacente;
    while (indexArista != NULL)
    {

        if (indexArista->verticeDestino->name == du)
        {
            arista = indexArista;
        }

        indexArista = indexArista->siguienteArista;
    }
    return arista;
}

DatoTypeWeightEdge Grafo::getPesoAristaByIndex(int iv, int iu)
{
    Vertice *v = getVerticeByIndex(iv);
    DatoTypeWeightEdge peso = 10000; // Infinito
    Arista *indexArista = v->primerAyacente;
    while (indexArista != NULL)
    {
        if (indexArista->verticeDestino->indexVertice == iu)
        {
            peso = indexArista->peso;
        }
        indexArista = indexArista->siguienteArista;
    }
    return peso;
}

DatoTypeWeightEdge Grafo::getPesoArista(DatoTypeVertex a, DatoTypeVertex b)
{
    Vertice *v = getVertice(a);
    DatoTypeWeightEdge peso = 10000; // Infinito
    Arista *indexArista = v->primerAyacente;
    while (indexArista != NULL)
    {
        if (indexArista->verticeDestino->name == b)
        {
            peso = indexArista->peso;
        }
        indexArista = indexArista->siguienteArista;
    }
    return peso;
}

void Grafo::mostrarGrafo()
{
    Vertice *n = primerVertice;
    Arista *na;
    // cout << "Direccion\tnombre\tsgte\tady\tcabeza" << endl;
    cout << "Vertices    | Lista de adyacencia" << endl;
    while (n != NULL)
    {
        na = n->primerAyacente;
        // cout << n << "(" << n->nombre << ")->" << n->sgte << "\t| ";
        cout << "i:" << n->indexVertice << ") " << n->name << "\t| ";
        while (na != NULL)
        {
            // cout << na << "(" << na->destino << "-" << na->destino->nombre << ")->" << na->sgte << "   ";
            cout << " " << na->verticeDestino->name << "(" << na->peso << ")";
            na = na->siguienteArista;
        }
        cout << "\n";
        n = n->siguienteVertice;
    }
}

bool Grafo::existeArista(DatoTypeVertex dv, DatoTypeVertex du)
{

    Vertice *iVertice = getVertice(dv);
    Arista *iArista = iVertice->primerAyacente;
    while (iArista != NULL)
    {
        if (iArista->verticeDestino->name == du)
        {
            return true;
        }

        iArista = iArista->siguienteArista;
    }

    return false;
}

bool Grafo::existeAristaByIndex(int i, int j)
{

    Vertice *iVertice = getVerticeByIndex(i);
    Arista *iArista = iVertice->primerAyacente;
    while (iArista != NULL)
    {
        if (iArista->verticeDestino->indexVertice == j)
        {
            return true;
        }
        iArista = iArista->siguienteArista;
    }

    return false;
}
