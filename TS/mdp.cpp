#include "mdp.h"

using namespace std;

#define TABUS 0.75

bool is_included(vector<int> *v, int e)
{
    if (find(v->begin(), v->end(), e) != v->end())
        return true;
    return false;
}

int random_element(Solution *s, vector<int> *t, int n, char c)
{
    int r;

    while (true)
    {
        r = rand() % n;
        if ((s->bit_set[r] == c) && (!is_included(t, r)))
            return r;
    }
}

void tabu_add(vector<int> *t, int e, int n)
{
    t->push_back(e);
    if (t->size() > (TABUS*n))
        t->erase(t->begin());
}

void ls_pmv_ts(Solution *sol, double distance, int n, int m, double (*cost)[MSIZE][MSIZE])
{
    int intentos           = 0,
        aleatorio_vecindad = 0;

    int max_ocur = int((double(n)/(double(n-m)))*2.0) + (double(MAXIT)*0.015);

    double dist_ant  = 0.0,
           dist_temp = 0.0;

    vector<int> ocurrencias (n, 0);
    vector<int> tabu_list;

    while (intentos < (MAXIT*n/m))
    {
        dist_ant = 0.0;
        while (distance != dist_ant) {
            // Calculo del aleatorio para la vencindad
            aleatorio_vecindad = random_element(sol, &tabu_list, n, '0');
            dist_ant = distance;

            ocurrencias[aleatorio_vecindad]++;
            if (ocurrencias[aleatorio_vecindad] == max_ocur)
            {
                tabu_add(&tabu_list, aleatorio_vecindad, n);
                ocurrencias[aleatorio_vecindad] = 0;
            }

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
        temp_b = 0;

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
    Solution solucion = Solution(0, aux, v);
    // Generacion de la solucion inicial aleatoria
    random_solution(&solucion, n, m);
    // Calculo de la sumatoria de la solucion Inicial
    solucion.distance = distance(&solucion, &costos);
    // Imprimo solucion Inicial
    cout << ", " << solucion.distance;

    ls_pmv_ts(&solucion, solucion.distance, n, m, &costos);
    // Imprimo la solucion obtenida
    cout << ", " << solucion.distance;
}