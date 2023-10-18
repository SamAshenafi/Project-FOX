#include "Combat.h"
#include <cstdio>

void Combat::update(Game& game) {
  if (isRoundOver) {
    // start new round
    currentRound += 1;
    fprintf(stderr, "----------------\n");
    fprintf(stderr, "New Round: %d\n", currentRound);
    for (Hero* hero : heroes) {
      hero->onRoundStart();
      fprintf(stderr, "%s speed: %d\n", hero->id.c_str(), hero->getSpeed());
    }
    for (Foe* foe : foes) {
      foe->onRoundStart();
      fprintf(stderr, "%s speed: %d\n", foe->id.c_str(), foe->getSpeed());
    }
    // sort by speed -> add to turnQueue

    // PLACEHOLDER: TO BE REPLACE. DO NOT USE //
    // turnQueue.push(heroes[0]);
    // // fprintf(stderr, "success\n");
    // turnQueue.push(foes[0]);
    // fprintf(stderr, "a\n");
    ///////////////////////////////
    // Sort characters by speed
    std::vector<Unit*> units;
    units.insert(units.end(), heroes.begin(), heroes.end());
    units.insert(units.end(), foes.begin(), foes.end());
    std::sort(units.begin(), units.end(), [](Unit* a, Unit* b) {
        return a->getSpeed() > b->getSpeed();
        });

    // Add characters to the turn queue
    for (Unit* unit : units) {
      turnQueue.push(unit);
    }


    isRoundOver = false;
  }
  else {
    if (currentUnit == nullptr) {
      if (!turnQueue.empty()) {
        fprintf(stderr, "---\n");
        currentUnit = turnQueue.front();
        turnQueue.pop();
        currentUnit->onTurnStart();
        // currentUnit->animationTimer = 0.5;
        // currentUnit->startAnimationTime = GetTime();
      }
      else {
        isRoundOver = true;
      }
    }
    else {
      // if (currentUnit->animationTimer > 0) {
      //   currentUnit->playAnimation();
      //   return;
      // }
      if (currentUnit->energy < 1) {
        currentUnit->onTurnEnd();
        currentUnit = nullptr;
        return;
      }
      if (isFoe(currentUnit)) {
        dynamic_cast<Foe*>(currentUnit)->takeTurn(game);
      }
      Action* action = currentUnit->getAction();
      if (action == nullptr) return;
      action->perform(currentUnit, currentUnit, game);
      // currentUnit->takeTurn(this);
      // currentUnit->selectedAction = currentUnit->actions[0];
    }
  }
}
