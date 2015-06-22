#include "../lib/solution.h"

using namespace std;

#define SEED 67219

bool is_included(vector<int> *v, int e);

int random_element(Solution *s, vector<int> *t, int n, char c);

void tabu_add(vector<int> *t, int e, int n);

void ls_pmv_ts(Solution *sol, double distance, int n, int m, double (*cost)[MSIZE][MSIZE]);