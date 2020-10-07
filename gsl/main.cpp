
#include <gsl/gsl_vector.h>
#include <gsl/gsl_multimin.h>

#include <thread>
#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

void my_f2( const gsl_vector *v, void *params, double& ret)
{

    cout << "\t\t f2\n";
    double x,y;
    double *p = (double *)params;

    x = gsl_vector_get(v,0);
    y = gsl_vector_get(v,1);

    this_thread::sleep_for( chrono::milliseconds(10) );
    ret = p[2] * (x - p[0]) * (x - p[0]) +
            p[3] * (y - p[1]) * (y - p[1]) + p[4];
    
}
double my_f( const gsl_vector *v, void *params)
{

    cout << "\t\t f\n";
    double x,y;
    double *p = (double *)params;

    x = gsl_vector_get(v,0);
    y = gsl_vector_get(v,1);
    this_thread::sleep_for( chrono::milliseconds(10) );
    return p[2] * (x - p[0]) * (x - p[0]) +
            p[3] * (y - p[1]) * (y - p[1]) + p[4];
    
}

void my_df( const gsl_vector *v, void *params, gsl_vector *df)
{
    cout << "\t\t df\n";
    double x,y;
    double *p = (double *) params;

    x = gsl_vector_get(v,0);
    y = gsl_vector_get(v,1);

    this_thread::sleep_for( chrono::milliseconds(10) );
    gsl_vector_set(df, 0, 2.0 * p[2] * (x - p[0]));
    gsl_vector_set(df, 1, 2.0 * p[3] * (y - p[1]));
}
    
    
void my_fdf( const gsl_vector *x, void *params,
             double *f, gsl_vector *df)
{

    cout << "\t fdf\n";
    //thread t1( my_f2, x, params, ref(*f));
    //thread t2( my_df, x, params, df);
    //t1.join();
    //t2.join();
    *f = my_f(x, params);
    my_df(x, params, df);
}

int main()
{

    size_t  iter = 0;
    int status;

    const gsl_multimin_fdfminimizer_type *T;
    gsl_multimin_fdfminimizer *s;

    double p[5] = { -1.0, 20.0, 100.0, 2.0, 1.0 };

    gsl_vector *x;
    gsl_multimin_function_fdf my_func;


    my_func.n = 2;
    my_func.f = &my_f;
    my_func.df = &my_df;
    my_func.fdf = &my_fdf;
    my_func.params = (void *) p;


    x = gsl_vector_alloc(2);
    gsl_vector_set(x, 0, 5.0);
    gsl_vector_set(x, 1, 7.0);

    //T = gsl_multimin_fdfminimizer_conjugate_fr;
    //T = gsl_multimin_fdfminimizer_conjugate_pr;
    T = gsl_multimin_fdfminimizer_vector_bfgs2; 
    //T = gsl_multimin_fdfminimizer_vector_bfgs; 
    //T = gsl_multimin_fdfminimizer_steepest_descent; 
    s = gsl_multimin_fdfminimizer_alloc(T, 2);

    gsl_multimin_fdfminimizer_set(s, &my_func, x, 0.0001, 1.e-1);

    do {
        iter++;
        status = gsl_multimin_fdfminimizer_iterate(s);
    
        if(status) break;

        status = gsl_multimin_test_gradient(s->gradient, 1e-3);

        if(status == GSL_SUCCESS ) cout << "min found at: \n";


        cout << gsl_vector_get(s->x, 0) << "\t";
        cout << gsl_vector_get(s->x, 1) << "\t";
        cout << s->f << "\n";




    } while( status == GSL_CONTINUE && iter < 100 );


    gsl_multimin_fdfminimizer_free(s);
    gsl_vector_free(x);

    return 0;
}
