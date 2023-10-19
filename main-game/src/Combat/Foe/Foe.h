#pragma once
#include "../Unit.h"

class Game;

class Foe : public Unit {
  public:
    Foe() {};
    ~Foe() {};
    std::string actionAI = "simple";

    // virtual Action* decideAction() = 0;
    virtual void decideAction() = 0;
    virtual std::vector<Unit*> decideTarget(std::vector<Unit*> targets) = 0;
};
