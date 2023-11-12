#include "World.h"
#include <cstdio>
#include <raylib.h>
#include "../../external-libs/nlohmann/json.hpp"
#include <algorithm>
#include "Inventory.h"
World::World(
    std::string roomId
    ) {
  initializeWorld(roomId);
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
  if (transitionTimer > -1) {
    if (transitionTimer == 0) transitionHelper();
    --transitionTimer;
    return;
  }
  if (!game.dialogQueue.empty()) player->movable = false;
  player->update();
}

void World::enterCombat(Game& game, const std::string& battleId) {
  GameState* combat = new Combat(battleId);
  game.changeState(combat);
}

void World::transitionRoom(TransitionTile* transition) {
  destination = transition;
  transitionTimer = 30;
  player->movable = false;
}

void World::transitionHelper() {
  player->movable = true;
  player->move(destination->enterX, destination->enterY);
  loadRoom(destination->destinationRoomId);
}