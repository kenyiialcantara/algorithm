#include <iostream>
using namespace std;

// Definiendo el tipo de dato
typedef int DatoType;

class Arista;

// Definiendo la clase vertice (Varinate del Nodo)
class Vertice
{
public:
    DatoType dato;             // Nombre o dato del vertice
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
    DatoType peso;
    bool visit;

    // Constructor

    Arista()
    {
        verticeDestino = NULL;
        siguienteArista = NULL;
        peso = 1;
        visit = false;
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
    void insertarVertice(DatoType);
    void insertarArista(DatoType, DatoType);           // Arista con peso 1 por defecto.
    void insertarArista(DatoType, DatoType, DatoType); // Arista con peso.

    void eliminarArista(DatoType, DatoType);

    void visualizarGrafo();
    Vertice *buscarVertice(DatoType);
    Vertice *buscarVerticeByIndex(DatoType);
    void mostrarGrafo();
    DatoType getDatoVerticeByIndex(int);

    Arista *getArista(DatoType, DatoType);
    void insertarAristaEnOrdenPeso(DatoType, DatoType, DatoType);
    int getPesoAristaByIndex(int, int);

    bool tieneVerticeDeDato(DatoType);

    string getAristaDeMenorPeso();

    void eliminarVertice(DatoType);
    void borrarAristasQueApuntaAlVerticeEliminado(DatoType);

    void actualizarIndices();

    bool existeVerticeDeDato(DatoType);
    bool existeArista(DatoType, DatoType);
};

bool Grafo::existeArista(DatoType dv, DatoType du)
{

    Vertice *iVertice = buscarVertice(dv);
    Arista *iArista = iVertice->primerAyacente;
    while (iArista != NULL)
    {
        if (iArista->verticeDestino->dato == du)
        {
            return true;
        }

        iArista = iArista->siguienteArista;
    }

    return false;
}

bool Grafo::existeVerticeDeDato(DatoType dato)
{

    Vertice *indexV = primerVertice;

    while (indexV != NULL)
    {

        if (indexV->dato == dato)
        {
            return true;
        }

        indexV = indexV->siguienteVertice;
    }

    return false;
}

void Grafo::actualizarIndices()
{

    int i = 0;
    Vertice *indexV = primerVertice;

    while (indexV != NULL)
    {
        indexV->indexVertice = i;
        indexV = indexV->siguienteVertice;
        i++;
    }
}

void Grafo::eliminarVertice(DatoType dato)
{
    Vertice *aux = primerVertice; // Apuntador o contador que recorre el directorio buscando
                                  // el nodo que se quiere borrar
    Vertice *ant = NULL;          // Apuntador que apunta al nodo que esta detras o antes del aux
    if (primerVertice == NULL)
    {
        cout << "Grafo vacio\n";
        return;
    }

    while (aux != NULL) // Recorre la lista hasta entrar el aux
    {
        if (aux->dato == dato)
        {
            borrarAristasQueApuntaAlVerticeEliminado(dato);

            if (aux->primerAyacente != NULL)
            {
                borrarAristasQueApuntaAlVerticeEliminado(dato); // Elimina los arcos del aux
            }

            if (aux == primerVertice)
            {
                primerVertice = primerVertice->siguienteVertice;
                delete (aux);
                // Actualizamos los indices
                actualizarIndices();
                // cout << "Primer vertice eliminado\n";
                return;
            }
            else
            {

                (ant->siguienteVertice) = (aux->siguienteVertice);
                // cout << "Nodo eliminado:" << aux << "(" << aux->dato << ")->" << aux->siguienteVertice << endl;
                delete (aux);
                // Actualizamos los indices
                actualizarIndices();
                return;
            }
        }
        else
        {
            ant = aux;
            aux = aux->siguienteVertice;
        }
    }
}

void Grafo::borrarAristasQueApuntaAlVerticeEliminado(DatoType datoVerticeAEli)
{
    //
    // Esta funcion recorre cada arco, si encuantra uno que esta conectando
    // al nodo que se eliminará, guarda en "ant",
    // para su posterior eliminacion en la siguiente iteracion.
    //
    //(Por que eliminamos en la siguiente iteracion y no en el instante que la encontramos?)
    // Esto debido a que si eliminamos el nodo en el instante que la encontramos
    // al finalizar esa iteracion tenemos que realizar arcoActual=arcoActual->sgte
    // para seguir recorriendo, pero en este caso hipotetico
    // no es posible, ya que el arco ya estaria eliminado, y se generaria un error.
    //
    // Si bien es cierto que lo solucionamos guardando en "ant" y eliminando en la siguiente iter.
    // Tine una exepcion pequeña (No verifica si el ultimo arco se dirige al nodo a eliminar).
    // ya que la itercion se terminaria antes de virificarlo.
    // Pero lo solucionamos con el codigo en [aa] ver abajo.
    //
    Vertice *n = primerVertice;
    Arista *na;
    Arista *ant;
    while (n != NULL)
    {
        na = n->primerAyacente;
        ant = NULL;
        while (na != NULL)
        {
            if (ant != NULL)
            {
                if (ant->verticeDestino->dato == datoVerticeAEli)
                {
                    eliminarArista(n->dato, ant->verticeDestino->dato);
                }
            }
            ant = na;
            na = na->siguienteArista;
            //[aa] Esto verifica si el ultimo arco se dirige al nodo a eliminar
            if (na == NULL)
            {
                if (ant->verticeDestino->dato == datoVerticeAEli)
                {
                    eliminarArista(n->dato, ant->verticeDestino->dato);
                }
            }
        }

        n = n->siguienteVertice;
    }
}

string Grafo::getAristaDeMenorPeso()
{
    string inicio = "";
    string llegada = "";
    string peso = "";

    Vertice *iVertice = primerVertice;

    if (primerVertice->primerAyacente == NULL)
    {
        return inicio + "|" + llegada + "|" + peso;
    }

    int pesoSupuestoMinimo = primerVertice->primerAyacente->peso;
    Arista *iArista;

    while (iVertice != NULL)
    {
        iArista = iVertice->primerAyacente;
        while (iArista != NULL)
        {

            if (iArista->peso <= pesoSupuestoMinimo)
            {

                pesoSupuestoMinimo = iArista->peso;
                inicio = to_string(iVertice->dato);
                llegada = to_string(iArista->verticeDestino->dato);
                peso = to_string(pesoSupuestoMinimo);
            }

            iArista = iArista->siguienteArista;
        }

        iVertice = iVertice->siguienteVertice;
    }

    return inicio + "|" + llegada + "|" + peso;
}

int Grafo::getPesoAristaByIndex(int iv, int iu)
{
    Vertice *v = buscarVerticeByIndex(iv);
    int peso = v->primerAyacente->peso;
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

bool Grafo::tieneVerticeDeDato(DatoType d)
{
    Vertice *iVertice = primerVertice;
    bool response = false;
    while (iVertice != NULL)
    {

        if (iVertice->dato == d)
        {
            response = true;
            break;
        }

        iVertice = iVertice->siguienteVertice;
    }

    return response;
}

Arista *Grafo::getArista(DatoType dv, DatoType du)
{
    Vertice *v = buscarVertice(dv);
    Arista *arista = v->primerAyacente;
    Arista *indexArista = v->primerAyacente;
    while (indexArista != NULL)
    {

        if (indexArista->verticeDestino->dato == du)
        {
            arista = indexArista;
        }

        indexArista = indexArista->siguienteArista;
    }
    return arista;
}

void Grafo::insertarAristaEnOrdenPeso(DatoType inicial, DatoType llegada, DatoType peso)
{

    Vertice *v = buscarVertice(inicial);
    Arista *iArista = v->primerAyacente;
    Arista *anteriorArista = NULL;

    Arista *nuevo = new Arista();
    nuevo->verticeDestino = buscarVertice(llegada);
    nuevo->peso = peso;

    if (iArista == NULL)
    {
        v->primerAyacente = nuevo;
    }
    else if (peso < iArista->peso)
    {
        nuevo->siguienteArista = iArista;
        v->primerAyacente = nuevo;
    }
    else
    {
        for (iArista; iArista != NULL; iArista = iArista->siguienteArista)
        {
            if (iArista->peso <= peso)
            {
                anteriorArista = iArista;
            }
            else
            {
                nuevo->siguienteArista = iArista;
                anteriorArista->siguienteArista = nuevo;
                break;
            }
        }
        if (iArista == NULL)
        {
            anteriorArista->siguienteArista = nuevo;
        }
    }
    numeroDeAristas++;
}

void Grafo::insertarArista(DatoType x, DatoType y, DatoType peso) // Arista de peso 1 (Por defecto)
{
    Vertice *indexVertice = primerVertice;

    while (indexVertice != NULL)
    {
        if (indexVertice->dato == x)
        {

            Arista *nuevo = new Arista();
            nuevo->peso = peso;
            Arista *indexArista = indexVertice->primerAyacente;
            nuevo->verticeDestino = buscarVertice(y);
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

void Grafo::eliminarArista(DatoType inicial, DatoType llegada)
{

    Vertice *v = buscarVertice(inicial);
    Arista *indexArista = v->primerAyacente;
    Arista *anterior = indexArista;
    Arista *aEliminar;

    if (v != NULL)
    {
        if (indexArista->verticeDestino->dato == llegada)
        {
            aEliminar = indexArista;
            v->primerAyacente = indexArista->siguienteArista;
            delete (aEliminar);
            numeroDeAristas--;
            return;
        }

        while (indexArista != NULL)
        {

            if (indexArista->verticeDestino->dato == llegada)
            {
                anterior->siguienteArista = indexArista->siguienteArista;
                delete (indexArista);
                numeroDeAristas--;
                break;
            }

            anterior = indexArista;
            indexArista = indexArista->siguienteArista;
        }
    }
}

Vertice *Grafo::buscarVerticeByIndex(DatoType i)
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

DatoType Grafo::getDatoVerticeByIndex(int index)
{
    Vertice *iVertice = primerVertice;
    while (iVertice != NULL)
    {
        if (iVertice->indexVertice == index)
            break;
        iVertice = iVertice->siguienteVertice;
    }
    return iVertice->dato;
}

Vertice *Grafo::buscarVertice(DatoType d)
{
    Vertice *n = primerVertice;

    while (n != NULL)
    {

        if (n->dato == d)
        {
            break;
        }
        n = n->siguienteVertice;
    }
    return n;
}

void Grafo::insertarVertice(DatoType d)
{
    // Asignando la direccion de memoria del nuevo vertice
    // Y este apunta al anterior primer nodo.
    // Nota: "new" retorna un puntero, en comparacion a otros leguages.
    Vertice *nuevo = new Vertice();
    nuevo->dato = d;
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

void Grafo::insertarArista(DatoType x, DatoType y) // Arista de peso 1 (Por defecto)
{
    Vertice *indexVertice = primerVertice;

    while (indexVertice != NULL)
    {
        if (indexVertice->dato == x)
        {

            Arista *nuevo = new Arista();
            Arista *indexArista = indexVertice->primerAyacente;
            nuevo->verticeDestino = buscarVertice(y);
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
        cout << "i:" << n->indexVertice << ") " << n->dato << "\t| ";
        while (na != NULL)
        {
            // cout << na << "(" << na->destino << "-" << na->destino->nombre << ")->" << na->sgte << "   ";
            cout << " " << na->verticeDestino->dato << "(" << na->peso << ")";
            na = na->siguienteArista;
        }
        cout << "\n";
        n = n->siguienteVertice;
    }
}

// int main()
// {
//     Grafo G;

//     G.insertarVertice(0);
//     G.insertarVertice(1);
//     G.insertarVertice(2);
//     G.insertarVertice(3);
//     G.insertarVertice(4);
//     G.insertarVertice(5);
//     G.insertarVertice(6);
//     G.insertarVertice(7);

//     G.insertarAristaEnOrdenPeso(0, 6, 53);
//     G.insertarAristaEnOrdenPeso(0, 1, 32);
//     G.insertarAristaEnOrdenPeso(0, 2, 29);
//     G.insertarAristaEnOrdenPeso(4, 3, 34);
//     G.insertarAristaEnOrdenPeso(5, 3, 18);
//     G.insertarAristaEnOrdenPeso(7, 4, 46);
//     G.insertarAristaEnOrdenPeso(5, 4, 40);
//     G.insertarAristaEnOrdenPeso(0, 5, 60);
//     G.insertarAristaEnOrdenPeso(6, 4, 51);
//     G.insertarAristaEnOrdenPeso(7, 0, 31);
//     G.insertarAristaEnOrdenPeso(7, 6, 25);
//     G.insertarAristaEnOrdenPeso(7, 1, 21);

//     G.mostrarGrafo();
//     G.eliminarVertice(5);
//     G.mostrarGrafo();

//     return 0;
// }