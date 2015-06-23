#include "../lib/solution.h"

using namespace std;

#define SEED 67219
#define MAXGN 70
#define POBLA 500
#define NEWPL 0.40

double distance_efficient(Solution *s, double actual_dist, double (*cost)[MSIZE][MSIZE]);

void new_generation(vector<Solution> *g, int n, int m, double (*cost)[MSIZE][MSIZE]);

void croosover(Solution *child, Solution *p1, Solution *p2, int n, int m, double (*cost)[MSIZE][MSIZE]);

void update_generation(vector<Solution> *g, int n, int m, double (*cost)[MSIZE][MSIZE]);