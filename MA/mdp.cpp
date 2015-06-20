#include <set>
#include <string>
#include <vector>
#include <time.h>
#include <math.h>
#include <fstream>
#include <stdio.h>     
#include <stdlib.h>
#include <iostream>
#include <algorithm>

using namespace std;

#define SEED  67219
#define MSIZE 4000
#define MAXIT 600
#define DETER 0.25

struct Node
{
    int index;
    double media;
    double varianza;

    Node(int k, double m, double v) : index(k), media(m), varianza(v) {}

    bool operator < (const Node& str) const
    {
        return (varianza < str.varianza);
    }
};

struct greater_than_media
{
    inline bool operator() (const Node& struct1, const Node& struct2)
    {
        return (struct1.media > struct2.media);
    }
};

void printVector(vector<int> *v)
{
    cout << "[";
    for(vector<int>::iterator it = v->begin(); it != v->end(); ++it) {
        cout << *it << ",";
    }
    cout << "]\n";
}

int randomElem(vector<int> *v, int n)
{
    int t = 0;

    while (true)
    {
        t = rand() % n;
        if (std::find(v->begin(), v->end(), t) == v->end())
            break;
    }
    return t;
}

int randomElem(vector<int> *v, vector<int> *banned, int n, int m)
{
    int t = 0,
        l = int(double(31.0*m*m*m/7920000.0) - 
            double(109.0*m*m/72000.0) + 
            double(2237.0*m/19800.0) + 
            (MAXIT*0.02)) +
            1;

    while (true)
    {
        t = rand() % n;
        if ((std::find(v->begin(), v->end(), t) == v->end()) &&
            ((*banned)[t] < l))
            break;
    }
    return t;
}

int randomElem(vector<int> *v, vector<Node> *a, int n)
{
    int t = 0;

    while (true)
    {
        t = rand() % int(double(n)/1.12);
        if (std::find(v->begin(), v->end(), (*a)[t].index) == v->end())
        {
            break;
        }
    }
    return (*a)[t].index;
}

void randomSol(vector<int> *v, int n, int m)
{
    // Generacion de la solucion inicial aleatoria
    while(v->size() < m)
    {
        v->push_back(randomElem(v, n));
    }
}

bool isInclude(int e, vector<int> *v)
{
    //sort(sol.begin(),sol.end());
    if (find(v->begin(), v->end(), e) != v->end())
        return true;
    return false;
}

bool repeated(vector<int> *v)
{
    for (int i = 0; i < v->size(); i++)
    {
        for (int j = i+1; j < v->size(); j++)
        {
            if ((*v)[i] == (*v)[j])
            {
                cout << "la cagaste\n";
                exit(-1);
                return true;
            }
        }
    }
    return false;
}

void addDElements(vector<int> *v, vector<Node> *a, int l)
{
    for (int i = 0; i < l; i++)
    {
        v->push_back((*a)[i].index);
    }
}

void deterSol(vector<int> *v, vector<Node> *avg, int t1, int t2, int n, int m, double (*cost)[MSIZE][MSIZE])
{
    int actual    = 0,
        candidato = 0,
        vecino    = 0;

    double aux_dist = 0.0;

    vector<int> queue;

    queue.push_back(t1);
    queue.push_back(t2);

    while ((!queue.empty()) && (v->size() < int(m*DETER)))
    {
        actual = queue[0];
        queue.erase(queue.begin());

        aux_dist = 0.0;
        for (int i = 0; i < n; i++)
        {
            candidato = (*avg)[i].index;
            if (candidato == actual)
                break;
            if (!(isInclude(candidato, v)) && ((*cost)[actual][candidato] > aux_dist))
            {
                aux_dist = (*cost)[actual][candidato];
                vecino = candidato;
            }
        }

        if (aux_dist != 0.0)
            queue.push_back(vecino);

        if (!(isInclude(actual, v)))
            v->push_back(actual);
    }
}

double distance(vector<int> *v, double (*cost)[MSIZE][MSIZE])
{
    int sz = v->size();
    double ds = 0;

    for(int i=0; i < sz-1; i++)
    {
        for(int j = i+1; j < sz; j++)
        {
            ds += (*cost)[v->at(i)][v->at(j)];
        }
    }

    return ds;
}

double distanceE(vector<int> *v, double actual_dist, int pos, int elem, double (*cost)[MSIZE][MSIZE])
{
    double res = 0.0,
           dif = 0.0;

    int actual = (*v)[pos];

    for(int i = 0; i < v->size(); i++)
    {
        if (i < pos)
        {
            dif += (*cost)[(*v)[i]][actual];
        }
        else if (i > pos)
        {
            dif += (*cost)[actual][(*v)[i]];            
        }

    }

    for(int i = 0; i < v->size(); i++)
    {
        if (i < pos)
        {
            res += (*cost)[(*v)[i]][elem];
        }
        else if (i > pos)
        {
            res += (*cost)[elem][(*v)[i]];   
        }
    }

    return (actual_dist - dif + res);
}

void average(vector<Node> *v, int n, double (*cost)[MSIZE][MSIZE])
{
    double tmp = 0.0,
           var = 0.0;

    for(int i = 0; i < n; i++)
    {
        tmp = 0.0;
        var = 0.0;
        for(int j = 0; j < n;j++)
        {
            if (i != j)
            {
                tmp += (*cost)[i][j];
                var += ((*cost)[i][j])*((*cost)[i][j]);
            }
        }

        tmp = tmp/double(n);
        var = sqrt(var/double(n));

        v->push_back(Node(i, tmp, var));
    }
}

double ls_pmv_ts(vector<int> *v, double distance, int n, int m, double (*cost)[MSIZE][MSIZE])
{
    int aleatorio_vecindad = 0,
        intentos  = 0,
        tabu_size = int(20*m/n);

    double dist_ant  = 0.0,
           dist_temp = 0.0;

    vector<int> tabu_list;
    vector<int> banned (n,0);

    while (intentos < (MAXIT*n/m))
    {
        dist_ant = 0.0;
        while (distance != dist_ant) {
            // Calculo del aleatorio para la vencindad
            aleatorio_vecindad = randomElem(v, &banned, n, m);
            //aleatorio_vecindad = randomElem(v, n);
            dist_ant = distance;

            for(int k = 0; k < m;k++)
            {
                dist_temp = distanceE(v, distance, k, aleatorio_vecindad, cost);

                if ((dist_temp > distance) &&
                    (!isInclude(aleatorio_vecindad, &tabu_list)))
                {
                    distance = dist_temp;
                    (*v)[k] = aleatorio_vecindad;
                    tabu_list.push_back(aleatorio_vecindad);

                    if (tabu_list.size() > tabu_size)
                        tabu_list.erase(tabu_list.begin());

                    break;
                }
            }
        }
        banned[aleatorio_vecindad]++;
        intentos++;
    }

    return distance;
}

double ls_mv_ts(vector<int> *v, double distance, int n, int m, double (*cost)[MSIZE][MSIZE])
{
    int aleatorio_vecindad = 0,
        intentos = 0,
        indice,
        tabu_size = int(20*m/n);

    double dist_ant  = 0.0,
           dist_temp = 0.0;

    vector<int> tabu_list;

    while (intentos < (MAXIT*n/m))
    {
        dist_ant = 0.0;
        while (distance != dist_ant) {
            // Calculo del aleatorio para la vencindad
            aleatorio_vecindad  = randomElem(v, n);
            dist_ant = distance;
            indice = -1;

            for(int k = 0; k < m; k++)
            {
                dist_temp = distanceE(v, distance, k, aleatorio_vecindad, cost);

                if ((dist_temp > distance) &&
                    (!isInclude(aleatorio_vecindad, &tabu_list)))
                {
                    indice = k;
                }
            }

            if (indice != -1)
            {
                distance = distanceE(v, distance, indice, aleatorio_vecindad, cost);

                tabu_list.push_back((*v)[indice]);
                
                (*v)[indice] = aleatorio_vecindad;
                
                if (tabu_list.size() > tabu_size)
                    tabu_list.erase(tabu_list.begin());
            }
        }
        intentos++;
    }

    return distance;
}

double ls_pmgv_ts(vector<int> *v, double distance, int n, int m, double (*cost)[MSIZE][MSIZE])
{
    int aleatorio_vecindad = 0,
        intentos  = 0,
        tabu_size = int(15*m/n);

    double dist_ant  = 0.0,
           dist_temp = 0.0;

    vector<int> tabu_list;

    while (intentos < (MAXIT*n/m))
    {
        dist_ant = 0.0;
        while (distance != dist_ant) {
            // Calculo del aleatorio para la vencindad
            //aleatorio_vecindad = randomElem(v, n);
            aleatorio_vecindad = rand() % m;
            dist_ant = distance;

            for(int k = 0; k < n; k++)
            {
                if (!isInclude(k, v))
                {
                    dist_temp = distanceE(v, distance, aleatorio_vecindad, k, cost);
                
                    if ((dist_temp > distance) &&
                        (!isInclude(k, &tabu_list)))
                    {
                        distance = dist_temp;
                        (*v)[aleatorio_vecindad] = k;
                        intentos *= 0.95;
                        
                        tabu_list.push_back(k);
                        
                        if (tabu_list.size() > tabu_size)
                            tabu_list.erase(tabu_list.begin());
                        break;
                    }
                }
            }
        }
        intentos++;
    }

    return distance;
}

double ls_mgv_ts(vector<int> *v, double distance, int n, int m, double (*cost)[MSIZE][MSIZE])
{
    int aleatorio_vecindad = 0,
        intentos  = 0,
        actual,
        tabu_size = int(15*m/n);

    double dist_ant  = 0.0,
           dist_temp = 0.0;

    vector<int> tabu_list;

    while (intentos < (MAXIT*n/m))
    {
        dist_ant = 0.0;
        while (distance != dist_ant) {
            // Calculo del aleatorio para la vencindad
            //aleatorio_vecindad = randomElem(v, n);
            aleatorio_vecindad = rand() % m;
            dist_ant = distance;
            actual   = -1;

            for(int k = 0; k < n; k++)
            {
                if (!isInclude(k, v))
                {
                    dist_temp = distanceE(v, distance, aleatorio_vecindad, k, cost);
                
                    if ((dist_temp > distance) &&
                        (!isInclude(k, &tabu_list)))
                    {
                        actual = k;
                    }
                }
            }

            if (actual != -1)
            {
                distance  = distanceE(v, distance, aleatorio_vecindad, actual, cost);

                tabu_list.push_back((*v)[aleatorio_vecindad]);
                
                (*v)[aleatorio_vecindad] = actual;
                
                if (tabu_list.size() > tabu_size)
                    tabu_list.erase(tabu_list.begin());
            }
        }
        intentos++;
    }

    return distance;
}


int main () {
    // Variables
    static double costos[MSIZE][MSIZE];

    int n = 0,
        m = 0,
        temp1 = 0,
        temp2 = 0, 
        temp_a = 0,
        temp_b = 0,
        aleatorio_vecindad = 0,
        intentos = 0;

    double dist_ant  = 0.0,
           dist_temp = 0.0,
           dist_sol  = 0.0;

    vector<int> solucion_temp;
    vector<Node> avgs;

    // Inicio de la semilla para el aleatorio
    time_t seconds;
    time(&seconds);
    srand((unsigned int) seconds * SEED);
    cout.precision(15);
    //srand(SEED);
    
    // Lectura de la cantidad de elementos del cojunto,
    // y de elementos del subconjunto
    cin >> n >> m;

    // Lectura de la distancia entre cada punto
    while(!cin.eof()){
        cin >> temp_a >> temp_b >> dist_temp;
        costos[temp_a][temp_b]=dist_temp;
        costos[temp_b][temp_a]=dist_temp;
    }

    average(&avgs, n, &costos);

    sort(avgs.begin(), avgs.end(), greater_than_media()); //mayor media
    addDElements(&solucion_temp, &avgs, int(m*0.25));

    sort(avgs.begin(), avgs.end()); //menor varianza
    addDElements(&solucion_temp, &avgs, int(m*0.20));

    // Generacion de la solucion inicial aleatoria
    randomSol(&solucion_temp, n, m);
    reverse(solucion_temp.begin(), solucion_temp.end());
    // Calculo de la sumatoria de la solucion Inicial
    dist_sol = distance(&solucion_temp, &costos);
    // Imprimo solucion Inicial
    cout << "," << dist_sol; // << endl;

    dist_sol = ls_pmv_ts(&solucion_temp, dist_sol, n, m, &costos);
    //dist_sol = ls_mv_ts(&solucion_temp, dist_sol, n, m, &costos);

    repeated(&solucion_temp);
    //sort(solucion_temp.begin(), solucion_temp.end());
    //printVector(&solucion_temp);
    // Imprimo la solucion obtenida
    cout << "," << dist_sol;
}