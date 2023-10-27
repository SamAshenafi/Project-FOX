#include "Combat.h"
#include "Action/Actions.h"
#include "../../external-libs/nlohmann/json.hpp"
#include "Action/DoNothing.h"
#include "Action/Strike.h"
#include <cstdio>
#include <raylib.h>
#include <string>

Combat::Combat(std::string combatId) {
  // currentRound = 0;
  // units = {};
  // units.push_back(Unit("unit1", 1, 1, 1));
  // units.push_back(Unit("unit2", 1, 1, 3));
  // units.push_back(Unit("unit3", 1, 1, 7));
  // std::sort(units.begin(), units.end(), [](const Unit& a, const Unit& b) {
  //     return a.initiative > b.initiative;
  //     });

  // std::string currentBattleId = "001";
  loadBattle(combatId);
}

Combat::~Combat() {
  return;
}

void Combat::render(Game& game) {
  // TODO:
  BeginDrawing();
  // ClearBackground(RAYWHITE);
  ClearBackground(DARKGRAY);

  int screenWidth = game.settings.screenWidth;
  int screenHeight = game.settings.screenHeight;

  //Renders Background for battle 
  // Could use similar algorithm for drawing the background image in World.cpp

  // Renders Menu Boxes containing selectable actions
  // Menu contains (1) actions and can scroll through them
  RenderUI(screenWidth, screenHeight);

  // Renders Heros and Foes and stat symbols
  // if theres a better way to initilize pos then replace it
  // for now the usage of pos will be considered a placeholder
  RenderUnits(
    heroes,
    foes,
    screenWidth,
    screenHeight
  );
  game.renderDialog();
  EndDrawing();
}

void Combat::loadBattle(const std::string& battleId) {
  const std::string battleFilePath = "./json/battle/";
  const std::string jsonFileType = ".json";
  const std::string fullFilePath = battleFilePath + battleId + jsonFileType;
  nlohmann::json root;
  std::ifstream jsonFile(fullFilePath);

  if (jsonFile.is_open()) {
    try {
      jsonFile >> root;

      // Empty the output vector
      unitsFromJSON.clear();

      // Parse Enemies
      for (const auto& foeData : root["enemies"]) {
        std::string foeId = foeData["id"].get<std::string>();

        Foe* newFoe = createFoe(foeId);
        if (newFoe != nullptr) {
          fprintf(stderr, "Added foe w/ id:%s to foes\n", foeId.c_str());
          for(std::string action : newFoe->getActionList()) {
            newFoe->actions.push_back(createAction(action));
          }
          newFoe->sprite = loadTexture(newFoe->id);
          foes.push_back(newFoe);
        }
        else {
          fprintf(stderr, "Invalid foeId: %s\n", foeId.c_str());
        }
      }

    }
    catch (const std::exception& e) {
      fprintf(stderr, "JSON parsing failed: %s\n", e.what());
    }
  }
  Hero* foxHero = new FoxHero();
  foxHero->sprite = loadTexture(foxHero->id);
  for(std::string action : foxHero->actionList)
  {
    foxHero->actions.push_back(createAction(action));
  }
  heroes.push_back(foxHero);
}

