#include "line_search.h"


#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

double f(double x) { return 1.- x/2 - 2*x*x/3. + 0.05*x*x*x*x ;}
double df(double x) { return -1./2 - 4*x/3. + 0.2*x*x*x ;}

int main()
{

    LS<double> ls(&f,&df);
    double x = 0.;
    for(int i=0;i<10;++i) {
        ls.set_p(x);
        //         x, alpha0 , rho, c
        ls.backtrack(x, 1, 0.5, 0.1);
        cout << ls.alpha << endl;
        x += ls.p*ls.alpha; 
        cout << x << endl;
        cout << f(x) << endl;
        cout << "-------------" << endl;
    }

    return 0;
}
