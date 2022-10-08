#include <iostream>
using namespace std;

// Backtracking
//  Variables globales:
int n;
char **Tablero;

// Variables globales complementarias
bool exito;
bool opcion;

void inicializarTablero()
{
    Tablero = new char *[n];
    for (int i = 0; i < n; i++)
    {
        Tablero[i] = new char[n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Tablero[i][j] = ' ';
        }
    }
}

void imprimirTablero()
{
    cout << "Tablero:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int i = 0; i < n; i++)
        {
            cout << "----";
        }
        printf("\n| ");
        for (int j = 0; j < n; j++)
        {
            cout << Tablero[i][j] << " | ";
        }
        printf("\n");
    }
}

// Verificamos en la casilla [fila][columna] del tablero que ninguna reina le este atacando.
bool verificaPosicion(int fila, int columna)
{
    int i, j;
    // Verificando fila hacia la izquierda
    for (i = 0; i < columna; i++)
    {
        if (Tablero[fila][i] == 'I')
        {
            return false;
        }
    }
    // Verificando la diagonal superior izquierda
    for (i = fila, j = columna; i >= 0 && j >= 0; i--, j--)
    {

        if (Tablero[i][j] == 'I')
        {
            return false;
        }
    }

    // Verificanado la diagonal inferior izquierda
    for (i = fila, j = columna; j >= 0 && i < n; i++, j--)
    {
        if (Tablero[i][j] == 'I')
        {
            return false;
        }
    }
    return true; // Si ninguna reina le esta atacando
}

bool NReinaRetroceso(int columna)
{
    cout << endl;
    imprimirTablero();
    // Caso base: Si todas las reinas ya fueforn colocados
    if (columna >= n)
    {
        return true;
    }
    // Para esta columna, tratamos de poner la reina en cada casilla
    //(Son opciones a OPCIONES probar)
    for (int iFila = 0; iFila < n; iFila++)
    {
        // Verificacion para seleccionar opcion
        opcion = verificaPosicion(iFila, columna);
        if (opcion)
        {
            // Guardando opcion
            Tablero[iFila][columna] = 'I';

            // Si aun no esta completa la solución
            if (columna < n)
            {
                exito = NReinaRetroceso(columna + 1); // Analizamos la SIGUIENTE ETAPA

                if (!exito)
                {
                    // Si no tenemos exito, RETIRAMOS OPCION
                    Tablero[iFila][columna] = ' ';
                }
                else
                {
                    return true;
                }
            }
        }
    }
    return false;
}

int main()
{
    n = 4;
    inicializarTablero();

    NReinaRetroceso(0);

    imprimirTablero();
    return 0;
}