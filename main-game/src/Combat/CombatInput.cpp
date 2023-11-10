#include "Combat.h"
#include <raylib.h>

void Combat::processInput(Game& game) {
  if (animationDuration != 0) return;
  // TODO:
  int keyPressed = GetKeyPressed();
  switch (keyPressed) {
    case KEY_C:
      fprintf(stderr, "%s\n", "c was pressed");
      // game.changeState("world");
      game.changeState(game.world);
      break;
    // delete this section?
    // case KEY_N:
    //   fprintf(stderr, "%s\n", "n was pressed");
    //   // if (currentUnit != nullptr) {
    //   //   if (isHero(currentUnit)) {
    //   //     if (highlightedAction != nullptr) {
    //   //       fprintf(stderr, "%s\n", "do nothing action is executed");
    //   //       currentUnit->selectedAction = highlightedAction;
    //   //       highlightedAction = nullptr;
    //   //     }
    //   //     else {
    //   //       fprintf(stderr, "%s\n", "no action is selected. Please select one by pressing p for now.");
    //   //     }
    //   //   }
    //   // }
    //   break;
    case KEY_P:
      fprintf(stderr, "%s\n", "p was pressed");
      if(!game.dialogQueue.empty()) game.dialogQueue.pop();
      if(isHero(currentUnit) && !(availableTargets.empty())) {
        selected = (selected + 1) % (availableTargets.size());
        fprintf(stderr, "%s is currently highlighted\n", availableTargets[selected]->id.c_str());
        highlightedTarget = availableTargets[selected];
      }
      else if (isHero(currentUnit) && availableTargets.empty()) {
        selected = (selected + 1) % (currentUnit->actions.size());
        fprintf(stderr, "%s%i\n", "selection size: ",currentUnit->actions.size());
        fprintf(stderr, "%s%s\n", "action highlighted: ",currentUnit->actionList[selected].first.c_str());
        highlightedAction = currentUnit->actions[selected];
      }
      else {
        fprintf(stderr, "Unit w/ id: %s is not a hero\n", currentUnit->id.c_str());
      }
      break;
    case KEY_O:
      fprintf(stderr, "%s\n", "O was pressed");
      if (!(availableTargets.empty()) && highlightedTarget != nullptr) {
        numberOfTargets--;
        if (numberOfTargets <= 0) {
          currentUnit->selectedTargets.push_back(highlightedTarget);
          targets = {};
          targets = currentUnit->selectedTargets;
          fprintf(stderr, "%s action is executed on %i enemy(ies)\n", currentUnit->id.c_str(), targets.size()); 
          selected = 0;  
        }
        else {
          currentUnit->selectedTargets.push_back(highlightedTarget);
          fprintf(stderr, "%s was selected. Selections left: %d\n", foes[selected]->id.c_str(), numberOfTargets);
          previousAvailable = availableTargets;
          availableTargets.erase(availableTargets.begin()+(selected-1));
        }
      }
      else if (highlightedAction != nullptr) {
        if (highlightedAction->targetType == "enemy") {
          fprintf(stderr, "Action selected: %s\n", currentUnit->actionList[selected].first.c_str());
          currentUnit->selectedAction = highlightedAction;
          availableTargets = foes;
          numberOfTargets = 1;
          selected = 0;
        }

        if (highlightedAction->targetType == "enemies") {
          fprintf(stderr, "Action selected: %s\n", currentUnit->actionList[selected].first.c_str());
          currentUnit->selectedAction = highlightedAction;
          availableTargets = foes;
          numberOfTargets = highlightedAction->multiSelect;
          selected = 0;
        }

        if (highlightedAction->targetType == "all") {
          fprintf(stderr, "Action selected: %s\n", currentUnit->actionList[selected].first.c_str());
          currentUnit->selectedAction = highlightedAction;
          targets = foes;
          selected = 0;
        }

        if(highlightedAction->targetType == "self") {
          fprintf(stderr, "Action selected: %s\n", currentUnit->actionList[selected].first.c_str());
          currentUnit->selectedAction = highlightedAction;
          targets.push_back(currentUnit);
          selected = 0;
        }

      }
      else {
        fprintf(
            stderr,
            "%s\n",
            "no action/target is selected. Select by pressing p."
            );
        game.dialogQueue.push("no action/target is selected. Select by pressing p");
      }
      break;
    case KEY_L:
      if (!(availableTargets.empty()) && highlightedTarget != nullptr) {
        if (availableTargets.size() != foes.size()) {
          numberOfTargets++;
          availableTargets = previousAvailable;
          currentUnit->selectedTargets.pop_back();

          fprintf(stderr, "Deselected Enemy Selection\n");
        }
        else if (!(availableTargets.empty()) && highlightedTarget != nullptr) {
          numberOfTargets = NULL;
          availableTargets = {};
          currentUnit->selectedAction = nullptr;
          currentUnit->selectedTargets = {};
          previousAvailable = {};
          fprintf(stderr, "Deselected To Action Selection\n");
          }
      }
      break;
    case KEY_SPACE:
      fprintf(stderr, "%s\n", "space was pressed");
      if (!game.dialogQueue.empty()) {
        game.dialogQueue.pop();
        break;
      }
      break;
  }
  return;
}
