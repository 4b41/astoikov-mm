// rename file to quote.h
#pragma once
#ifndef QUOTE_H_
#define QUOTE_H_

#include "usings.h"
#include <string>

enum class Side {
  Buy,
  Sell
}

class Quote {
  public:
    Quote(std::string symbol, Side side, Price price, Quantity quantity){
      this->_symbol = symbol;
      this->_side = side;
      this->_limit_price = price;
      this->_quantity = quantity;
    }

    Quantity getQuantity() const { return _quantity; }
    void updateQuantity(Quantity q) { _quantity += q; }

  private:
    std::string _symbol;
    Side _side;
    Price _limit_price;
    Quantity _quantity;
}

#endif // !QUOTE_H_
