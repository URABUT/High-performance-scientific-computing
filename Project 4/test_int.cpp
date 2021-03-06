/*Author: Van Tran
test_int.cpp
11/25/15*/
// Inclusions
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "fcn.hpp"

using namespace std;

// function prototypes
double composite_int(Fcn& f, const double a, const double b, const int n);

// Integrand
class fcn : public Fcn {
public:
  double c, d;
  double operator()(double x) {   // function evaluation
    return (exp(c*x) + sin(d*x));
  }
  double antiderivative(double x) { // function evaluation
    return (exp(c*x)/c - cos(d*x)/d);
  }
};


// This routine tests the Gauss-8 method on a simple integral
int main(int argc, char* argv[]) {

  // limits of integration
  double a = -3.0;
  double b = 5.0;

  // integrand
  fcn f;
  f.c = 0.5;
  f.d = 25.0;

  // true integral value
  double Itrue = f.antiderivative(b) - f.antiderivative(a);
  printf("\n True Integral = %22.16e\n", Itrue);


  // test the Gauss-4 rule
  cout << "\n Gauss-5 approximation:\n";
  cout << "     n             R(f)            relerr    conv rate\n";
  cout << "  ---------------------------------------------------\n";
  vector<int> n = {20, 40, 60, 80, 100, 120, 140, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 175, 176, 177, 178, 179};
  vector<double> errors(n.size());
  vector<double> hvals(n.size());

  // iterate over n values, computing approximations, error, convergence rate
  double Iapprox;
  for (int i=0; i<n.size(); i++) {

    printf("   %6i", n[i]);
    Iapprox = composite_int(f, a, b, n[i]);
    errors[i] = fabs(Itrue-Iapprox)/fabs(Itrue);
    hvals[i] = (b-a)/n[i];
    if (i == 0) 
      printf("  %22.16e  %7.1e     ----\n", Iapprox, errors[i]);
    else 
      printf("  %22.16e  %7.1e   %f\n", Iapprox, errors[i], 
	     (log(errors[i-1]) - log(errors[i]))/(log(hvals[i-1]) - log(hvals[i])));
    
  }
  cout << "  ---------------------------------------------------\n";

}
