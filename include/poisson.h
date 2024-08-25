#ifndef POISSON_H_
#define POISSON_H_

#include "marketmaker.h"
#include <random>

class Poisson {
  public:
    Poisson(ModelParams& params);

    bool arrive(Price delta, double dt);

  private:
    double K;
    double A;
    std::random_device rd;
    std::mt19937 Mers;
    std::uniform_real_distribution<double> d;
};

#endif // !POISSON_H_
