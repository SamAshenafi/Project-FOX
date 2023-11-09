#pragma once
#include "Token.h"

class Poison : public Token {
  public:
    Poison(int stack) {
    stack = stack;
    tokenID = GetRandomValue(8,255);
  }
    int stack;

    int onTurnStart(Unit& unit) override {
      // TODO: How does this play a sound?
      // SOL1: pass Game to unit on... function then to this
      unit.hp -= 5;
      fprintf(
        stderr,
        "%s is being drained by the poison. Losing %i health!!!\n",
        unit.id.c_str(),
        5
      );
      return 6;
    };
    virtual int onTurnEnd(Unit& unit) override {
      // TODO: How does this play a sound?
      // SOL1: pass Game to unit on... function then to this
      stack--;
      if (stack == 0) {
        int i = 0;
        for(Token* pending : unit.tokens) {
          if (pending->tokenID == this->tokenID) {
            unit.tokens.erase(unit.tokens.begin()+i);
          }
          i++;
        }
      }
      return 0;
    };
    virtual int onRoundStart(Unit& unit) override {
      // TODO: How does this play a sound?
      // SOL1: pass Game to unit on... function then to this

      return 0;
    };
    virtual int onRoundEnd(Unit& unit) override {
      // TODO: How does this play a sound?
      // SOL1: pass Game to unit on... function then to this
      
      return 0;
    };
};
