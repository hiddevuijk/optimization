
#include "gd.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;


int main()
{
    double T = 1000;
    int N = 3;
    vector<vector<double> > A(N,vector<double>(N));
    vector<double> b(N);
    A[0][0] = 1;
    A[1][1] = 1;
    A[2][2] = 1;
    A[1][0] = 0;
    A[2][0] = 0;
    A[2][1] = 1;
    A[0][1] = A[1][0];
    A[0][2] = A[2][0];
    A[1][2] = A[2][1];
    b[0] = 0;
    b[1] = 0;
    b[2] = 1;
   
    GD gd(N,A,b); 

    vector<double> x(N);
    x[0] = 1;
    x[1] = 0; 
    x[2] = 0;
   

    gd.first_step(x);
    //cout << x[0] << '\t' << x[1] << '\n';
    cout << x[0] << '\t' << x[1] << '\t' << x[2] << '\n';
    for(int i=0;i<T;++i) {
        if( gd.get_done() ) break;
        gd.step();
        gd.get_x(x);
        cout << x[0] << '\t' << x[1] << '\t' << x[2] << '\n';
    }


    return 0;

}
