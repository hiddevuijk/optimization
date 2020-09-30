#ifndef GUARD_GD_H
#define GUARD_GD_H

#include <vector>

class GD {
public:
    GD(int N, std::vector<std::vector<double> > A, std::vector<double> b)
    : N(N), A(A), b(b), x(N,0), r(N,0), q(N,0), n_updates(0)
    { }

    void first_step(const std::vector<double>& x0);
    void step();

    void get_x( std::vector<double>& X) {
        for(int i=0;i<N;++i) X[i] = x[i];
    }

    void solve(const std::vector<double>& x0);
    int get_n() const { return n_updates; };

private:
    int N;
    std::vector<std::vector<double> > A;
    std::vector<double> b;
    std::vector<double> x;
    std::vector<double> r;

    std::vector<double> q; // temp vec

    double alpha;
    double delta;
    double delta0;
    int n_update_r = 50;
    int max_updates = 10000;
    double epsilon = 1e-21;
    int n_updates;
};

void GD::solve(const std::vector<double>& x0)
{

    first_step( x0);
    while( n_updates < max_updates and delta > epsilon*epsilon*delta0 ) step();

}

void GD::step()
{
    // q = A.r
    for(int i=0;i<N;++i) {
        q[i] = 0;
        for(int j=0;j<N;++j) {
            q[i] += A[i][j]*r[j];
        }
    }

    // alpha = delta/temp , temp = r.q
    double temp = 0;
    for(int i=0;i<N; ++i) temp += r[i]*q[i];
    alpha = delta/temp;

    // x += alpha*r 
    for(int i=0;i<N;++i) x[i] += alpha*r[i];
    

    if( n_updates %n_update_r == 0  ) {
        for(int i=0;i<N;++i) {
            r[i] = b[i];
            for(int j=0;j<N;++j) r[i] -= A[i][j]*x[j];
        }
    } else {
        for(int i=0;i<N;++i) r[i] -= alpha*q[i];
    } 
    ++n_updates;

    // delta = r.r
    delta = 0;
    for(int i=0;i<N;++i) delta += r[i]*r[i];
}


void GD::first_step(const std::vector<double>& x0)
{
    // x = x0 
    for(int i=0;i<N;++i) x[i] = x0[i];
    // r = b - A.x
    for(int i=0;i<N;++i) {
        r[i] = b[i];
        for(int j=0;j<N;++j) r[i] -= A[i][j]*x[j];
    }

    // delta = r.r
    delta = 0;
    for(int i=0;i<N; ++i) delta += r[i]*r[i];
    // delat0 = delta
    delta0 = delta;
}



#endif
