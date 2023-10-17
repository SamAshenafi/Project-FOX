#pragma once
#include "../Unit.h"

class Unit;

class Token {
  public:
    Token(int stack) {
      stack = stack;
    };

    int stack;

    virtual void onTurnStart(Unit& unit);
    virtual void onTurnEnd(Unit& unit);
    virtual void onRoundStart(Unit& unit);
    virtual void onRoundEnd(Unit& unit);
};
