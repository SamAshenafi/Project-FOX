#pragma once
#include <string>
#include "../Unit.h"
#include "../../Game.h"
// #include "../Combat.h"

class Action {
  public:
    Action() {};
    virtual ~Action() = default;
    // Possile targetType
    // "self"
    // "ally"
    // "allies"
    // "team"
    // "enemy"
    // "enemies"
    // "all"
    // "ALL"
    std::string targetType = "enemy";
    int energyCost = 1;
    int animationDuration = 12;

    virtual int perform(Unit* user, std::vector<Unit*> targets, Game& game) = 0;
};

