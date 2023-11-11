#include "World.h"
#include <cstdio>
#include <raylib.h>
#include "../../external-libs/nlohmann/json.hpp"
#include <algorithm>
#include "Inventory.h"
World::World(
    std::string roomId
    ) {
  //resetGrid();

  loadRoom(roomId);

  player = new Player(
      "player-01",
      playerX,
      playerY,
      playerFacing,
      playerInventory
      );
  entities.push_back(player);
  players.push_back(player);
}

World::~World() {
  return;
}

void World::loadRoom(const std::string& roomId) {
  Room* roomToLoad = findRoom(roomId);
  // If the room does not exist, construct it
  if (roomToLoad == nullptr) {
    fprintf(stderr, "Creating new Room...\n");
    const std::string saveFilePath = "./json/room/";
    const std::string jsonFileType = ".json";
    const std::string fullFilePath = saveFilePath + roomId + jsonFileType;
    nlohmann::json root;
    std::ifstream jsonFile(fullFilePath);

    if (jsonFile.is_open()) {
      try {
        jsonFile >> root;

        roomToLoad = buildRoom(roomId, root["roomData"]);
        rooms.push_back(roomToLoad);
      }
      catch (const std::exception& e) {
        fprintf(stderr, "JSON parsing failed: %s\n", e.what());
      }
    }
  }
  else fprintf(stderr, "Room already exists\n");

  setRoom(roomToLoad);
  fprintf(stderr, "Successful loadRoom\n");
}


void World::update(Game& game) {
  player->update();
  if (!game.dialogQueue.empty()) player->movable = false;
}

void World::enterCombat(Game& game, const std::string& battleId) {
  GameState* combat = new Combat(battleId);
  game.changeState(combat);
}
