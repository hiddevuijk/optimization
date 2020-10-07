#ifndef GUARD_LINE_SEARCH_H
#define GUARD_LINE_SEARCH_H

template<class Doub>
class LS
{
  public:
    Doub (*f)(Doub);
    Doub (*df)(Doub);

    double alpha;
    int p;

  public:
    LS(Doub (*f)(Doub),Doub (*df)(Doub) );

    void set_p(double x) { p = df(x) > 0 ? -1 : 1; }
    void backtrack(double x, double alpha0, double rho, double c); 

    
};

template<class Doub>
LS<Doub>::LS( Doub (*f)(Doub), Doub (*df)(Doub) ) 
: f(f), df(df) {}

template<class Doub>
void LS<Doub>::backtrack(double x, double alpha0, double rho, double c)
{
    alpha = alpha0;
    while( f(x+alpha*p) > f(x) + c*alpha*df(x)*p ) {
        alpha *= rho;
    }

}



#endif
