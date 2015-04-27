#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>     
#include <stdlib.h>
using namespace std;

int main () {
    // Variables
    int n,m,temp_a,temp_b,num;
    double temp_dist;
    cin >> n >> m;
    double costos[3000][3000];
    vector<int> solucion_temp;
    double distancia_solucion_temp;
    // Lectura
    while(!cin.eof()){
      cin >> temp_a >> temp_a >> temp_dist;
      costos[temp_a][temp_b]=temp_dist;
    }
}