#include "mdp_mv.h"

using namespace std;

void ls_mv(Solution *sol, double distance, int n, int m, double (*cost)[MSIZE][MSIZE])
{
    int intentos  = 0,
        seleccion = 0,
        aleatorio_vecindad = 0;

    double dist_ant  = 0.0,
           dist_temp = 0.0;

    while (intentos < (MAXIT*n/m))
    {
        dist_ant = 0.0;
        while (distance != dist_ant) {
            // Calculo del aleatorio para la vencindad
            aleatorio_vecindad = random_element(sol, n, '0');
            dist_ant = distance;
            seleccion = -1;

            for(int k = 0; k < m; k++)
            {
                dist_temp = distance_efficient(sol, distance, k, aleatorio_vecindad, cost);

                if (dist_temp > distance)
                {
                    dist_ant  = dist_temp;
                    seleccion = k;
                }
            }

            if (seleccion != -1)
            {
                sol->bit_set[sol->sub_set[seleccion]] = '0';
                sol->bit_set[aleatorio_vecindad] = '1';
                sol->sub_set[seleccion] = aleatorio_vecindad;
                sol->distance = dist_ant;
                distance = dist_ant;
                dist_ant = 0.0;
            }
        }
        intentos++;
    }
}

int main () {
    // Variables
    static double costos[MSIZE][MSIZE];

    int n = 0,
        m = 0,
        temp_a = 0,
        temp_b = 0;

    double distancia  = 0.0;

    vector<int> v;
    // Inicio de la semilla para el aleatorio
    srand(time(NULL));
    // Lectura de la cantidad de elementos del cojunto,
    // y de elementos del subconjunto
    cin >> n >> m;
    // Lectura de la distancia entre cada punto
    while(!cin.eof()){
        cin >> temp_a >> temp_b >> distancia;
        costos[temp_a][temp_b] = distancia;
        costos[temp_b][temp_a] = distancia;
    }

    string aux (n, '0');
    Solution solucion = Solution(0, aux, v);
    // Generacion de la solucion inicial aleatoria
    random_solution(&solucion, n, m);
    // Calculo de la sumatoria de la solucion Inicial
    solucion.distance = distance(&solucion, &costos);
    // Imprimo solucion Inicial
    cout << ", " << solucion.distance;

    ls_mv(&solucion, solucion.distance, n, m, &costos);
    // Imprimo la solucion obtenida
    cout << ", " << solucion.distance;
}