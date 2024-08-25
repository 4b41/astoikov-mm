#include "../include/poisson.h"

Poisson::Poisson(ModelParams& params) 
  : K(params->K), A(params->A), mers(rd()), d(0,1) { }

bool Poisson::arrive(Price delta, double dt){
  double lam = this->A * exp(-k*delta);
  double p = lam * dt;
  double u = d(mers);

  return u < p;
}
