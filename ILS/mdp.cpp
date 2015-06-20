#include <string>
#include <vector>
#include <time.h>
#include <fstream>
#include <stdio.h>     
#include <stdlib.h>
#include <iostream>
#include <algorithm>

using namespace std;

#define SEED  67219
#define MSIZE 4000
#define MAXIT 150
#define DETER 0.40

struct Node
{
    int index;
    double media;

    Node(int k, double m) : index(k), media(m) {}

    bool operator < (const Node& str) const
    {
        return (media < str.media);
    }
};

void printVector(vector<int> *v)
{
    cout << "[";
    for(vector<int>::iterator it = v->begin(); it != v->end(); ++it) {
        cout << *it << ", ";
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

void deterSol(vector<int> *v, vector<Node> *avg, int n, int m, int t1, int t2, double (*cost)[MSIZE][MSIZE])
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

        if (!isInclude(actual, v))
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
    double tmp = 0.0;

    for(int i = 0; i < n; i++)
    {
        tmp = 0.0;
        for(int j = 0; j < n;j++)
        {
            if (i != j)
            {
                tmp += (*cost)[i][j];
            }
        }
        v->push_back(Node(i, tmp/double(n)));
    }
}

double ls(vector<int> *v, double distance, int n, double (*cost)[MSIZE][MSIZE])
{
    int m = v->size(),
        aleatorio_vecindad = 0,
        intentos = 0;

    double dist_ant  = 0.0,
           dist_temp = 0.0;

    while (intentos < (MAXIT*n/m))
    {
        dist_ant = 0.0;
        while (distance != dist_ant) {
            // Calculo del aleatorio para la vencindad
            aleatorio_vecindad = randomElem(v, n);
            dist_ant = distance;

            for(int k = 0; k < v->size();k++)
            {
                dist_temp = distanceE(v, distance, k, aleatorio_vecindad, cost);

                if (dist_temp > distance)
                {
                    distance = dist_temp;
                    (*v)[k] = aleatorio_vecindad;
                    break;
                }
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
        iteraciones = 0;

    double dist_ant  = 0.0,
           dist_temp = 0.0,
           dist_sol  = 0.0;

    vector<int> solucion_temp;
    vector<int> solucion_pert;
    vector<Node> avgs;

    // Inicio de la semilla para el aleatorio
    time_t seconds;
    time(&seconds);
    srand((unsigned int) seconds);
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
        if (dist_temp > dist_ant)
        {
            dist_ant = dist_temp;
            temp1 = temp_a;
            temp2 = temp_b;
        }
    }

    average(&avgs, n, &costos);
    sort(avgs.begin(), avgs.end());
    reverse(avgs.begin(), avgs.end());

    addDElements(&solucion_temp, &avgs, int(m*0.25 + 1));

    deterSol(&solucion_temp, &avgs, n, m, temp1, temp2, &costos);
    // Generacion de la solucion inicial aleatoria
    randomSol(&solucion_temp, n, m);
    reverse(solucion_temp.begin(), solucion_temp.end());
    // Calculo de la sumatoria de la solucion Inicial
    dist_sol = distance(&solucion_temp, &costos);
    // Imprimo solucion Inicial
    cout << "," << dist_sol;

    dist_sol = ls(&solucion_temp, dist_sol, n, &costos);
    
    while (iteraciones < 10)
    {
        solucion_pert = solucion_temp;

        for (int l = 0; l < int(1+m*0.1); l++)
        {
            temp1 = (rand()%m);
            temp2 = randomElem(&solucion_pert, n);
            solucion_pert[temp1] = temp2;
        }

        dist_temp = distance(&solucion_pert, &costos);

        dist_temp = ls(&solucion_pert, dist_temp, n, &costos);

        if (dist_temp > dist_sol)
        {
            dist_sol = dist_temp;
            solucion_temp = solucion_pert;
        }

        iteraciones++;
    }
    repeated(&solucion_temp);
    dist_sol = distance(&solucion_temp, &costos);
    // Imprimo la solucion obtenida
    cout << "," << dist_sol;
}