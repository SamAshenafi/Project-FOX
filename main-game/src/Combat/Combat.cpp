#include "Combat.h"
#include "Action/Actions.h"
#include "Action/DoNothing.h"

Combat::Combat() {
  // abilityMap["DoNothing"] = []() { return new DoNothing(); };
  // currentRound = 0;
  // units = {};
  // units.push_back(Unit("unit1", 1, 1, 1));
  // units.push_back(Unit("unit2", 1, 1, 3));
  // units.push_back(Unit("unit3", 1, 1, 7));
  // std::sort(units.begin(), units.end(), [](const Unit& a, const Unit& b) {
  //     return a.initiative > b.initiative;
  //     });

  // PLACEHOLDER. DO NOT//
  Hero* foxHero = new FoxHero();
  foxHero->id = "Fox";
  foxHero->actions.push_back(new DoNothing());
  heroes.push_back(foxHero);
  // PLACEHOLDER. DO NOT//
}

void Combat::render(Game& game) {
  // TODO:
  BeginDrawing();
  // ClearBackground(RAYWHITE);
  ClearBackground(DARKGRAY);
  EndDrawing();
}

void Combat::processInput(Game& game) {
  // TODO:
  int keyPressed = GetKeyPressed();
  switch (keyPressed) {
    case KEY_C:
      fprintf(stderr, "%s\n", "c was pressed");
      // game.changeState("world");
      break;
    case KEY_N:
      fprintf(stderr, "%s\n", "n was pressed");
      if (currentUnit != nullptr) {
        if (isHero(currentUnit)) {
          // PLACEHOLDER //
          currentUnit->selectedAction = currentUnit->actions[0];
          // PLACEHOLDER //
        }
      }
      break;
    case KEY_P:
      fprintf(stderr, "%s\n", "p was pressed");
      // PLACEHOLDER //
      if (currentUnit != nullptr) {
        if (isHero(currentUnit)) {
          if (currentUnit->selectedAction != nullptr) {
            currentUnit->selectedAction->perform(currentUnit, currentUnit, game);
            currentUnit->selectedAction = nullptr;
          }
          else {
            fprintf(stderr, "no action is selecter. Use n to select DoNothing\n");
          }
        }
      }
      else {
        fprintf(stderr, "sigsegv\n");
      }
      // PLACEHOLDER //

      // if (currentUnitIndex < units.size()) {
      //   Unit& currentPlayer = units[currentUnitIndex];
      //   if (!currentPlayer.hasTakenTurn) {
      //     // Handle player's turn (e.g., wait for user input like Space key press)
      //     currentPlayer.passTurn();
      //     currentUnitIndex++;
      //   }
      // }
      // else {
      //   startRound();
      // }
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

// void Combat::startRound() {
//   fprintf(stderr, "round %d started\n", currentRound);
//   currentRound++;
//   // isRoundOver = false;
//   // for (Unit& unit : units) {
//   //   unit.hasTakenTurn = false;
//   }
//   // for (Unit& unit : enemies) {
//   //   unit.hasTakenTurn = false;
//   // }
//
//   // std::sort(units.begin(), units.end(), [](const Unit& a, const Unit& b) {
//   //     return a.initiative > b.initiative;
//   //     });
//   // currentUnitIndex = 0; // Start with the first player character
// }

void Combat::update(Game& game) {
  if (isRoundOver) {
    // start new round
    currentRound += 1;
    fprintf(stderr, "New Round: %d\n", currentRound);
    for (Hero* hero : heroes) {
      hero->onRoundStart();
    }
    for (Foe* foe : foes) {
      foe->onRoundStart();
    }
    // sort by speed -> add to turnQueue

    // PLACEHOLDER: TO BE REPLACE. DO NOT USE //
    turnQueue.push(heroes[0]);
    ///////////////////////////////

    isRoundOver = false;
  }
  else {
    if (currentUnit == nullptr) {
      if (!turnQueue.empty()) {
        currentUnit = turnQueue.front();
        turnQueue.pop();
        currentUnit->onTurnStart();
      }
      else {
        isRoundOver = true;
      }
    }
    else {
      if (currentUnit->energy < 1) {
        currentUnit->onTurnEnd();
        currentUnit = nullptr;
      }
    }
  }
}

Combat::~Combat() {
  return;
}


bool Combat::isHero(Unit* unit) {
  Hero* hero = dynamic_cast<Hero*>(unit);
  return hero != nullptr;
}
bool Combat::isFoe(Unit* unit) {
  Foe* foe = dynamic_cast<Foe*>(unit);
  return foe != nullptr;
}
