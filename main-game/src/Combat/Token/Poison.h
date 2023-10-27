#pragma once
#include "Token.h"

class Poison : public Token {
  public:
    int stack;

    int onTurnStart(Unit& unit) override {
      // TODO: How does this play a sound?
      // SOL1: pass Game to unit on... function then to this
      unit.hp -= stack;
      return 6;
    };
    // void onTurnEnd(Unit& unit);
    // void onRoundStart(Unit& unit);
    // void onRoundEnd(Unit& unit);
};
