#pragma once
#include "../Unit.h"

class Game;

class Foe : public Unit {
  public:
    Foe() {};
    ~Foe() {};
    std::string actionAI = "simple";

    virtual Action* decideAction() = 0;
};
