#include "mdp.h"

using namespace std;

double distance_efficient(Solution *s, double actual_dist, double (*cost)[MSIZE][MSIZE])
{
    int size = s->sub_set.size()-1,
        e = s->sub_set.back();

    double result = 0.0;

    for (int i = 0; i < size; i++)
    {
        result += (*cost)[s->sub_set[i]][e];
    }

    return (actual_dist + result);
}

void new_generation(vector<Solution> *g, int n, int m, double (*cost)[MSIZE][MSIZE])
{
    Solution* tmp;

    string aux (n, '0');

    vector<int> aux_vec;

    for (int i = 0; i < POBLA; i++)
    {
        g->push_back(Solution(0, aux, aux_vec));
        tmp = &((*g)[i]);
        random_solution(tmp, n, m);
        tmp->distance = distance(tmp, cost);
    }
}

void croosover(Solution *child, Solution *p1, Solution *p2, int n, int m, double (*cost)[MSIZE][MSIZE])
{
    int i = 0,
        j = 0;

    double dist_act = 0.0;

    while (i < n)
    {
        if ((p1->bit_set[i] == '1') &&
            (p2->bit_set[i] == '1'))
        {
            child->bit_set[i] = '1';
            child->sub_set.push_back(i);
            dist_act = distance_efficient(child, dist_act, cost);
        }
        i++;
    }

    i = child->sub_set.size();

    while (i < m)
    {
        j = random_element(child, n, '0');
        if ((p1->bit_set[j] == '1') ||
            (p2->bit_set[j] == '1'))
        {
            child->bit_set[j] = '1';
            child->sub_set.push_back(j);
            dist_act = distance_efficient(child, dist_act, cost);
            i++;
        }
    }

    child->distance = dist_act;
}

void update_generation(vector<Solution> *g, int n, int m, double (*cost)[MSIZE][MSIZE])
{
    int i = 0,
        j = 0,
        p = POBLA*NEWPL;

    string aux (n, '0');

    vector<Solution> result;

    Solution* tmp;

    vector<int> aux_vec;

    for (i = 0; i < p; i++)
    {
        result.push_back((*g)[i]);
    }

    while (i < POBLA)
    {
        result.push_back(Solution(0, aux, aux_vec));
        tmp = &(result.back());
        croosover(tmp, &((*g)[j]), &((*g)[j+1]), n, m, cost);

        if (++i >= POBLA)
            break;

        result.push_back(Solution(0, aux, aux_vec));
        tmp = &(result.back());
        croosover(tmp, &((*g)[j]), &((*g)[j+2]), n, m, cost);
        i++; j++;
    }

    g->clear();
    g->assign(result.begin(), result.end());
}

int main()
{
    static double costos[MSIZE][MSIZE];

    int n = 0,
        m = 0,
        tmp_a = 0,
        tmp_b = 0,
        tmp_c = 0,
        tmp_d = 0; 

    double dist_sol = 0.0,
           dist_ant = 0.0,
           dist_tmp = 0.0;

    vector<Solution> generacion;

    // Inicio de la semilla para el aleatorio
    time_t seconds; time(&seconds);
    srand((unsigned int) seconds * SEED);
    cout.precision(15);
    // n cantidad de elementos del cojunto.
    // m cantidad de elementos del subconjunto.
    cin >> n >> m;

    // Lectura de la distancia entre cada punto
    while(!cin.eof()){
        cin >> tmp_a >> tmp_b >> dist_tmp;
        costos[tmp_a][tmp_b] = dist_tmp;
        costos[tmp_b][tmp_a] = dist_tmp;
    }

    new_generation(&generacion, n, m, &costos);

    cout << ", " << generacion[0].distance;

    for (int i = 0; i < MAXGN; i++)
    {
        sort(generacion.begin(), generacion.end(), greater_than_distance());
        
        update_generation(&generacion, n, m, &costos);
    }

    sort(generacion.begin(), generacion.end(), greater_than_distance());

    cout << ", " << generacion[0].distance;
}