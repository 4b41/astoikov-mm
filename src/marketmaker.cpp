#include "../include/marketmaker.h"
#include <string>
#include <vector>
#include <iostream>

MarketMaker::MarketMaker(const ModelParams& params, std::string symbol){
  this->_params = params;
  this->_symbol = symbol;
  this-> _pnl = 0;
  this-> _upnl = 0;
  this->assetFstream = fstream("../res/symbol.txt",ios::in);
}

std::vector<std::string> MarketMaker::parseAssetStream(std::string line){
  // assume format: SYMBOL TIME PRICE QUANTITY
  std::vector<std::string> tick;

  char delimiter[2] = " ";
  char *token = strtok(line.data(), delimiter);
uuuu
  while (token != NULL){
    tick.push_back(token);
    token = strtok(NULL, delimiter);
  }
  return tick;
}

Price MarketMaker::calculateReservationPrice(Price p, Quantity q, double t) const {
  // r(s,q,t) = s - q*GAMMA*SIGMA^2(T-t)
  return p - q * this->params.GAMMA * std::pow(this->params.SIGMA,2) * (this->params.T-t);
}

double MarketMaker::calculateSpread(double t) const {
  // delta_a + delta_b = GAMMA*SIGMA^2(T-t) + (2/gamma)ln(1+(gamma/k))
  return this->params.GAMMA * std::pow(this->params.SIGMA,2) * (this->params.T-t) + (2/this->params.gamma) * log(1+this->params.gamma/this->params.k);
}

Price MarketMaker::calculateBid(Price r, double s) const {
  return r - s/2;
}

Price MarketMaker::calculateAsk(Price r, double s) const {
  return r + s/2;
}

Quantity MarketMaker::calculateOrderSize() const {
  double size = this->params.A * (targetInventory - _quantity);
  return static_cast<Quantity>(std::round(q));
}

void MarketMaker::updateFromTick(std::string line){
  std::vector<std::string> tick = parseAssetStream(line);
  this->_price = tick[2];
}


void MarketMaker::createOrders(double t){
  Price r = calculateReservationPrice(_price, _quantity, t);
  double s = calculateSpread(s);
  Price b = calculateBid(r,s);
  Price a = calculateAsk(r,s);

  Quantity q = calculateOrderSize() / 2;

  Quote bid(this->_symbol, Side::Buy, b, q);
  Quote ask(this->_symbol, Side::Sell, a, q);
  
  auto IT1 = this->_bidQuotes.find(b);
  auto IT2 = this->_askQuotes.find(a);

  if (IT1 != this->_bidQuotes.end()){
    IT1->second.updateQuantity(10);
  } else {
    this->_bidQuotes[b] = bid;
  }
  if (IT2 != this->_askQuotes.end()){
    IT2->second.updateQuantity(10);
  } else {
    this->_askQuotes[a] = ask;
  }
  
  this->_quantity += 2*q;
  // log orders
}
