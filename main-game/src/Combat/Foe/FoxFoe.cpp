#include "FoxFoe.h"
#include "../Action/Actions.h"
#include <raylib.h>
#include <vector>

void FoxFoe::decideAction() {
  if (actions.empty()) {
    fprintf(stderr, "no actions for enemy AI\n");
    // return nullptr;
  }
  int randomActionIndex = GetRandomValue(0, actions.size());
  fprintf(stderr, "randomActionIndex rolled: %d\n", randomActionIndex);
  selectedAction = actions[randomActionIndex];
  // if (selectedAction == nullptr) {
  // return nullptr;
  // game.dialogQueue.push("Foe did nothing!");
  // selectedAction->perform(this, this, game);
  // startAnimationTime = GetTime();
  // animationTimer = 2.0;
  // selectedAction = nullptr;
  // }
  // return selectedAction;
};

std::vector<Unit*> FoxFoe::decideTarget(std::vector<Unit*> targets) {
  return targets;
}
