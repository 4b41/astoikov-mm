#include "../include/marketmaker.h"

int main(){
  ModelParams params = {
    .K = 1.5;
    .SIGMA = 2.0;
    .GAMMA = 0.1;
    .A = 0.5;
    .T = 1.0;
    .Q0 = 0.0;
    .S0 = 100.0;
    .dt = 1.0/1000;
    .N = 1000;
  }

  MarketMaker *mm = new MarketMaker(params);
   
  return 1;
}
