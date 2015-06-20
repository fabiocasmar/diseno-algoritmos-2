#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#define SEED  67219
#define MSIZE 3000
#define MAXGN 45
#define POBLA 550
#define NEWPL 0.5

struct Node
{
    double distance;
    string solution;
    vector<int> sub_set;

    Node(double d, string s, vector<int> v) : distance(d), solution(s), sub_set(v) {}

    bool operator < (const Node& str) const
    {
        return (distance < str.distance);
    }
};

struct greater_than_distance
{
    inline bool operator() (const Node& struct1, const Node& struct2)
    {
        return (struct1.distance > struct2.distance);
    }
};

int count_elements(string *s)
{
    int i = 0,
        r = 0;

    while (i < s->size())
    {
        if ((*s)[i] == '1')
            r++;
        i++;
    }
    return r;
}

int random_element(string *s, int n, char c)
{
    int t;

    while (true)
    {
        t = rand() % n;
        if ((*s)[t] == c)
            break;
    }
    return t;
}

void random_solution(Node *s, int n, int m)
{
    int r;

    for (int i = 0; i < m; i++)
    {
        r = random_element(&(s->solution), n, '0');
        s->solution[r] = '0' + 1;
        s->sub_set.push_back(r);
    }
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

double distance(vector<int> *v, double (*cost)[MSIZE][MSIZE])
{
    int sz = v->size();
    double ds = 0.0;

    for(int i = 0; i < sz-1; i++)
    {
        for(int j = i+1; j < sz; j++)
        {
            ds += (*cost)[v->at(i)][v->at(j)];
        }
    }

    return ds;
}

double distanceE(vector<int> *v, double actual_dist, double (*cost)[MSIZE][MSIZE])
{
    double res = 0.0;

    int e = v->size()-1;

    for(int i = 0; i < e; i++)
    {
        res += (*cost)[v->at(i)][v->at(e)];
    }

    return (actual_dist + res);
}

void new_generation(vector<Node> *g, int n, int m, double (*cost)[MSIZE][MSIZE])
{
    Node* tmp;

    string aux (n, '0');

    vector<int> aux_vec;

    for (int i = 0; i < POBLA; i++)
    {
        g->push_back(Node(0, aux, aux_vec));
        tmp = &((*g)[i]);
        random_solution(tmp, n, m);
        tmp->distance = distance(&(tmp->sub_set), cost);
    }
}

void croosover(Node *child, Node *p1, Node *p2, int n, int m, double (*cost)[MSIZE][MSIZE])
{
    int i = 0,
        j = 0;

    double dist_act = 0.0;

    while (i < n)
    {
        if ((p1->solution[i] == '1') &&
            (p2->solution[i] == '1'))
        {
            child->solution[i] = '1';
            child->sub_set.push_back(i);
            dist_act = distanceE(&(child->sub_set), dist_act, cost);
        }
        i++;
    }

    i = child->sub_set.size();

    while (i < m)
    {
        j = random_element(&(child->solution), n, '0');
        if ((p1->solution[j] == '1') ||
            (p2->solution[j] == '1'))
        {
            child->solution[j] = '1';
            child->sub_set.push_back(j);
            dist_act = distanceE(&(child->sub_set), dist_act, cost);
            i++;
        }
    }

    child->distance = dist_act;
}

void update_generation(vector<Node> *g, int n, int m, double (*cost)[MSIZE][MSIZE])
{
    int i = 0,
        p = POBLA*NEWPL;

    string aux (n, '0');

    vector<Node> result;

    Node* tmp;

    vector<int> aux_vec;

    for (i = 0; i < p; i++)
    {
        result.push_back((*g)[i]);
    }

    i = 0;

    while (i < p)
    {
        for (int j = 0; j < 2; j++)
        {
            result.push_back(Node(0, aux, aux_vec));
            tmp = &(result.back());
            croosover(tmp, &((*g)[i]), &((*g)[i+j+1]), n, m, cost);
            i++;
        }
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

    vector<Node> generacion;

    // Inicio de la semilla para el aleatorio
    time_t seconds; time(&seconds);
    srand((unsigned int) seconds * SEED);
    //srand(SEED);
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
    sort(generacion.begin(), generacion.end(), greater_than_distance());

    cout << "," << generacion[0].distance;

    for (int i = 0; i < MAXGN; i++)
    {
        sort(generacion.begin(), generacion.end(), greater_than_distance());
        
        update_generation(&generacion, n, m, &costos);
    }

    sort(generacion.begin(), generacion.end(), greater_than_distance());

    cout << "," << generacion[0].distance;
}