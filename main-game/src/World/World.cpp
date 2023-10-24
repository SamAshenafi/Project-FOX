#include "World.h"
#include <cstdio>
#include <raylib.h>
#include "../../external-libs/nlohmann/json.hpp"

World::World(
    std::string roomId
    ) {
  resetGrid();

  loadRoom(roomId);

  std::string roomFilePath = "./assets/room/" + roomId + "-bg.png";
  if (std::ifstream(roomFilePath)) {
    background = LoadTexture(roomFilePath.c_str());
  }
  else {
    fprintf(stderr, "not found bg image file %s\n", roomFilePath.c_str());
  }

  player = new Player(
      "player-01",
      playerX,
      playerY,
      playerFacing
      );
  entities.push_back(player);
  players.push_back(player);
}

World::~World() {
  return;
}

void World::loadRoom(const std::string& roomId) {
  const std::string saveFilePath = "./json/room/";
  const std::string jsonFileType = ".json";
  const std::string fullFilePath = saveFilePath + roomId + jsonFileType;
  nlohmann::json root;
  std::ifstream jsonFile(fullFilePath);

  if (jsonFile.is_open()) {
    try {
      jsonFile >> root;

      // TODO: rename this
      std::string roomFilePath = "./assets/room/" + roomId;
      background = LoadTexture((roomFilePath + "-bg.png").c_str());

      // Reinitialize Entities
      entities.clear();

      // Parse Tiles
      for (const auto& tileData : root["tiles"]) {
        std::string tileID = tileData["id"].get<std::string>();
        int tileX = tileData["x"].get<int>();
        int tileY = tileData["y"].get<int>();
        bool blocked = tileData["blocked"].get<bool>();
        Tile* tile = new Tile(tileID.c_str(), tileX, tileY, blocked);
        if (blocked) grid[tileX][tileY] = 1;
        entities.push_back(tile);
      }

      // Add players back to entities vector

      for (Player* pc : players) {
        entities.push_back(pc);
      }

      // Reinitialize Transition Tiles
      transitionTiles.clear();

      // Parse transition tiles
      for (const auto& transitionData : root["transitionTiles"]) {
        int tileX = transitionData["x"].get<int>();
        int tileY = transitionData["y"].get<int>();
        int enterX = transitionData["enterX"].get<int>();
        int enterY = transitionData["enterY"].get<int>();
        std::string destinationRoomId = transitionData["destinationRoomId"].get<std::string>();
        // TODO: create new TransitionTile & push into the transitionTiles vector
        TransitionTile* transitionTile = new TransitionTile(tileX, tileY, enterX, enterY, destinationRoomId.c_str());
        transitionTiles.push_back(transitionTile);
      }
    }
    catch (const std::exception& e) {
      fprintf(stderr, "JSON parsing failed: %s\n", e.what());
    }
  }
}


void World::update(Game& game) {
  player->update();
}



void World::enterCombat(Game& game, const std::string& battleId) {
  GameState* combat = new Combat(battleId);
  game.changeState(combat);
}
