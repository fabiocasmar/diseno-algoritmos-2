#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#define MSIZE 3000
#define MAXIT 50

struct Solution
{
    double distance;
    string bit_set;
    vector<int> sub_set;

    Solution(double d, string s, vector<int> v) : distance(d), bit_set(s), sub_set(v) {}

    bool operator < (const Solution& str) const
    {
        return (distance < str.distance);
    }
};

struct greater_than_distance
{
    inline bool operator() (const Solution& struct1, const Solution& struct2)
    {
        return (struct1.distance > struct2.distance);
    }
};

int random_element(Solution *s, int n, char c);

void random_solution(Solution *s, int n, int m);

double distance(Solution *s, double (*cost)[MSIZE][MSIZE]);

double distance_efficient(Solution *s, double actual_dist, int p, int e, double (*cost)[MSIZE][MSIZE]);

void repeated(Solution *s);