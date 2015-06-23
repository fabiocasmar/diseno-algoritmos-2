#include "../lib/solution.h"

using namespace std;

#define SEED 67219
#define MAXGN 5
#define POBLA 3
#define NEWPL 0.7

bool is_included(vector<int> *v, int e);

int random_element(Solution *s, vector<int> *t, int n, char c);

void tabu_add(vector<int> *t, int e, int n);

void ls_pmv_ts(Solution *sol, double distance, int n, int m, double (*cost)[MSIZE][MSIZE]);

double distance_efficient(Solution *s, double actual_dist, double (*cost)[MSIZE][MSIZE]);

void new_generation(vector<Solution> *g, int n, int m, double (*cost)[MSIZE][MSIZE]);

void croosover(Solution *child, Solution *p1, Solution *p2, int n, int m, double (*cost)[MSIZE][MSIZE]);

void update_generation(vector<Solution> *g, int n, int m, double (*cost)[MSIZE][MSIZE]);