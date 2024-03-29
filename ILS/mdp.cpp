#include "mdp.h"

using namespace std;

#define ITERS 6

void pertubar_solucion(Solution *pert, Solution *actl, int n, int m, double (*cost)[MSIZE][MSIZE])
{
    int r_in,
        r_out;

    double dist_tmp;

    pert->bit_set  = actl->bit_set;
    pert->sub_set  = actl->sub_set;
    pert->distance = actl->distance;

    for (int l = 0; l < int(m*0.1); l++)
    {
        r_in  = random_element(pert, n, '0');
        r_out = rand() % m;

        pert->distance = distance_efficient(pert, pert->distance, r_out, r_in, cost);

        pert->bit_set[pert->sub_set[r_out]] = '0';
        pert->bit_set[r_in] = '1';
        pert->sub_set[r_out] = r_in;
    }
}

void ls_pmv(Solution *sol, double distance, int n, int m, double (*cost)[MSIZE][MSIZE])
{
    int intentos           = 0,
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

            for(int k = 0; k < m; k++)
            {
                dist_temp = distance_efficient(sol, distance, k, aleatorio_vecindad, cost);

                if (dist_temp > distance)
                {
                    distance = dist_temp;
                    sol->bit_set[sol->sub_set[k]] = '0';
                    sol->bit_set[aleatorio_vecindad] = '1';
                    sol->sub_set[k] = aleatorio_vecindad;
                    break;
                }
            }
        }
        intentos++;
    }

    sol->distance = distance;
}

int main () {
    // Variables
    static double costos[MSIZE][MSIZE];

    int n = 0,
        m = 0,
        temp_a = 0,
        temp_b = 0,
        iteraciones = 0;

    double distancia  = 0.0;

    vector<int> v;
    // Inicio de la semilla para el aleatorio
    time_t seconds;
    time(&seconds);
    srand((unsigned int) seconds);
    cout.precision(15);
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
    Solution solucion_actl = Solution(0, aux, v);
    Solution solucion_pert = Solution(0, aux, v);
    // Generacion de la solucion inicial aleatoria
    random_solution(&solucion_actl, n, m);
    // Calculo de la sumatoria de la solucion Inicial
    solucion_actl.distance = distance(&solucion_actl, &costos);
    // Imprimo solucion Inicial
    cout << ", " << solucion_actl.distance;

    ls_pmv(&solucion_actl, solucion_actl.distance, n, m, &costos);
    
    while (iteraciones < ITERS)
    {
        pertubar_solucion(&solucion_pert, &solucion_actl, n, m, &costos);

        ls_pmv(&solucion_pert, solucion_pert.distance, n, m, &costos);

        if (solucion_pert.distance > solucion_actl.distance)
        {
            solucion_actl.bit_set = solucion_pert.bit_set;
            solucion_actl.sub_set = solucion_pert.sub_set;
            solucion_actl.distance = solucion_pert.distance;
        }

        iteraciones++;
    }
    // Imprimo la solucion obtenida
    cout << ", " << solucion_actl.distance;
}