#pragma once
#include "../Unit.h"

class Game;

class Foe : public Unit {
  public:
    Foe() {};
    ~Foe() {};
    std::string actionAI = "simple";

    virtual void takeTurn(Game& game) = 0;
};
