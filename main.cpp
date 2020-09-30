
#include "gd.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;


int main()
{
    double T = 10;
    int N = 2;
    vector<vector<double> > A(N,vector<double>(N));
    vector<double> b(N);
    A[0][0] = 10000;
    A[1][1] = 1;
    A[1][0] = 0;
    A[0][1] = 0;
    b[0] = 5;
    b[1] = -6;
   
    GD gd(2,A,b); 

    vector<double> x(N);
    x[0] = 10;
    x[1] = -9; 
   
    gd.solve(x);
    gd.get_x(x);
    cout << x[0] << '\t' << x[1] << '\n';
    cout << gd.get_n() << endl;
    return 0;

    gd.first_step(x);
    cout << x[0] << '\t' << x[1] << '\n';
    for(int i=0;i<T;++i) {
        gd.step();
        gd.get_x(x);
        cout << x[0] << '\t' << x[1] << '\n';
    }


    return 0;

}
