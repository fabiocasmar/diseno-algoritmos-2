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
#define MAXIT 900
#define DETER 0.45

struct Node
{
    int index;
    double media;
    double varianza;
    double factor;

    Node(int k, double m, double v, double f) : index(k), media(m), varianza(v), factor(f) {}

    bool operator < (const Node& str) const
    {
        return (media > str.media);
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

int randomElem(vector<int> *v, vector<Node> *a, int n)
{
    int t = 0;

    while (true)
    {
        t = rand() % int(double(n)/1.3);
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

        v->push_back(Node(i, tmp, var, (tmp/var)));
    }
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
    vector<int> tabu_list;
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
    }

    average(&avgs, n, &costos);
    sort(avgs.begin(), avgs.end());
    //reverse(avgs.begin(), avgs.end());

    addDElements(&solucion_temp, &avgs, int(m*0.20));
    //cout << solucion_temp.size() << endl;

    dist_sol = avgs[0].varianza;
    for(int i = 1; i < n; i++)
    {
        if (dist_sol > avgs[i].varianza)
        {
            dist_sol = avgs[i].varianza;
            temp1    = temp2;
            temp2    = avgs[i].index;
        }
    }

    deterSol(&solucion_temp, &avgs, temp1, temp2, n, m, &costos);
    //cout << solucion_temp.size() << endl;
    //exit(0);
    // Generacion de la solucion inicial aleatoria
    randomSol(&solucion_temp, n, m);
    reverse(solucion_temp.begin(), solucion_temp.end());
    // Calculo de la sumatoria de la solucion Inicial
    dist_sol = distance(&solucion_temp, &costos);
    // Imprimo solucion Inicial
    cout << "," << dist_sol;

    temp2 = int(20*m/n);

    while (intentos < (MAXIT*n/m))
    {
        dist_ant = 0.0;
        while (dist_sol != dist_ant) {
            // Calculo del aleatorio para la vencindad
            aleatorio_vecindad = randomElem(&solucion_temp, &avgs, n);
            dist_ant = dist_sol;

            for(int k = 0; k < solucion_temp.size();k++)
            {
                dist_temp = distanceE(&solucion_temp, dist_sol, k, aleatorio_vecindad, &costos);

                if ((dist_temp > dist_sol) &&
                    (!isInclude(aleatorio_vecindad, &tabu_list)))
                {
                    dist_sol = dist_temp;
                    solucion_temp[k] = aleatorio_vecindad;
                    tabu_list.push_back(aleatorio_vecindad);

                    if (tabu_list.size() > temp2)
                        tabu_list.erase(tabu_list.begin());

                    break;
                }
            }
        }
        intentos++;
    }
    // Imprimo la solucion obtenida
    repeated(&solucion_temp);

    cout << "," << dist_sol;
}