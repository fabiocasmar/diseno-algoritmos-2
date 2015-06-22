#include "solution.h"

using namespace std;

int random_element(Solution *s, int n, char c)
{
    int t;

    while (true)
    {
        t = rand() % n;
        if (s->bit_set[t] == c)
            break;
    }
    return t;
}

void random_solution(Solution *s, int n, int m)
{
    int r;

    for (int i = 0; i < m; i++)
    {
        r = random_element(s, n, '0');
        s->bit_set[r] = '0' + 1;
        s->sub_set.push_back(r);
    }
}

double distance(Solution *s, double (*cost)[MSIZE][MSIZE])
{
    int size = s->sub_set.size();

    double dist_aux = 0.0;

    for(int i = 0; i < size-1; i++)
    {
        for(int j = i+1; j < size; j++)
        {
            dist_aux += (*cost)[s->sub_set[i]][s->sub_set[j]];
        }
    }

    return dist_aux;
}

double distance_efficient(Solution *s, double actual_dist, int p, int e, double (*cost)[MSIZE][MSIZE])
{
    double res = 0.0,
           dif = 0.0;

    int act = s->sub_set[p],
        size = s->sub_set.size();

    for(int i = 0; i < size; i++)
    {
        if (i < p)
        {
            dif += (*cost)[s->sub_set[i]][act];
            res += (*cost)[s->sub_set[i]][e];
        }
        else if (i > p)
        {
            dif += (*cost)[act][s->sub_set[i]];            
            res += (*cost)[e][s->sub_set[i]];   
        }
    }
    return (actual_dist - dif + res);
}

void repeated(Solution *s)
{
    int size = s->sub_set.size();

    for (int i = 0; i < size; i++)
    {
        for (int j = i+1; j < size; j++)
        {
            if (s->sub_set[i] == s->sub_set[j])
            {
                cout << "error: existe un elemento repetido\n";
                exit(-1);
            }
        }
    }
}