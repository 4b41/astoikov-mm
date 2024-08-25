#ifndef MARKET_MAKER_H_
#define MARKET_MAKER_H_

#include "usings.h"
#include "asset.h"

#include <fstream>
#include <map>
#include <cmath>

struct ModelParams {
  // include maximum quantity or risk params?
  double K; 
  double SIGMA;
  double GAMMA;

  double A;
  double T;

  double Q0; // initial inventory state
  double S0; // initial asset midprice

  double dt; // size of time step
  double N; // number of time steps (dt)

  Quantity targetInventory;
}

class MarketMaker {
  public:

    MarketMaker(const ModelParams& params, std::string symbol);

    Price getPnl() const { return _pnl; }
    Price getUPnl() const { return _upnl; }
    int getTradeCount() const { return _trade_count; }

    void update(double t);

  private:
    Price calculateReservationPrice(Price p, Quantity q, double t) const;
    double calculateSpread(double t) const;

    Price calculateBid(Price r, double s) const;
    Price calculateAsk(Price r, double s) const;
    
    Quantity calculateOrderSize() const;

    void updatePnl(Price lowestAsk, Price highestBid);
    
    ModelParams _params;

    std::string _symbol;
    
    Price _price; 
    Price _best_bid;
    Price _best_ask;
    Quantity _quantity;

    Price _pnl;
    Price _upnl;
    std::uint32_t _trade_count;

    std::fstream assetFstream;

    std::map<Price,Quote> _bidQuotes;
    std::map<Price,Quote> _askQuotes;
}
#endif // !MARKET_MAKER_H_

