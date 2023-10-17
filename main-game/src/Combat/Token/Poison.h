#pragma once
#include "Token.h"

class Poison : public Token {
  public:
    int stack;

    void onTurnStart(Unit& unit) override {
      unit.takeDmg(stack);
    };
    // void onTurnEnd(Unit& unit);
    // void onRoundStart(Unit& unit);
    // void onRoundEnd(Unit& unit);
};
