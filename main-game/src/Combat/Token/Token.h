#pragma once
#include "../Unit.h"

class Unit;

class Token {
  public:
    Token(int stack) {
      stack = stack;
    };

    int stack;

    virtual int onTurnStart(Unit& unit);
    virtual int onTurnEnd(Unit& unit);
    virtual int onRoundStart(Unit& unit);
    virtual int onRoundEnd(Unit& unit);
};
