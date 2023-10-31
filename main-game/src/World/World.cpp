#include "World.h"
#include <cstdio>
#include <raylib.h>
#include "../../external-libs/nlohmann/json.hpp"
#include <algorithm>

World::World(
    std::string roomId
    ) {
  //resetGrid();

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

        // variables for constructing new room
        int roomGrid[20][12];
        std::vector<Tile*> roomTiles;
        std::vector<TransitionTile*> roomTransitions;

        // TODO: rename this
        std::string roomFilePath = "./assets/room/" + roomId;
        Texture2D roomBackground = LoadTexture((roomFilePath + "-bg.png").c_str());

        // Set grid to provided
        int col = 0;
        for (const auto& row : root["blockGrid"]){
          for(size_t i = 0; i < row.size(); i++){
            roomGrid[i][col] = row[i];
          }
          col = (col < 12) ? col + 1 : col;
        }

        // Parse Tiles
        for (const auto& tileData : root["tiles"]) {
          std::string tileID = tileData["id"].get<std::string>();
          int tileX = tileData["x"].get<int>();
          int tileY = tileData["y"].get<int>();
          bool blocked = tileData["blocked"].get<bool>();
          Tile* tile = new Tile(tileID.c_str(), tileX, tileY, blocked);
          roomTiles.push_back(tile);
        }

        // Parse transition tiles
        for (const auto& transitionData : root["transitionTiles"]) {
          int tileX = transitionData["x"].get<int>();
          int tileY = transitionData["y"].get<int>();
          int enterX = transitionData["enterX"].get<int>();
          int enterY = transitionData["enterY"].get<int>();
          std::string destinationRoomId = transitionData["destinationRoomId"].get<std::string>();
          TransitionTile* transitionTile = new TransitionTile(tileX, tileY, enterX, enterY, destinationRoomId.c_str());
          roomTransitions.push_back(transitionTile);
        }
        // Construct new room and add it to the rooms vector
        roomToLoad = new Room(roomId, roomGrid, roomTiles, roomTransitions, roomBackground);
        rooms.push_back(roomToLoad);
      }
      catch (const std::exception& e) {
        fprintf(stderr, "JSON parsing failed: %s\n", e.what());
      }
    }
  }
  else fprintf(stderr, "Room already exists\n");
  // Set current room as loaded room
  currentRoom = roomToLoad;

  // --------------------- Render/build the room
  // Reinitialize display data
  entities.clear();
  transitionTiles.clear();
  // Refill display data with room data
  std::copy(&(roomToLoad->grid[0][0]), &(roomToLoad->grid)[0][0]+20*12, &grid[0][0]);
  for (Tile* tile : roomToLoad->tiles) {
    if (tile != nullptr && tile->isBlockMovement) {
      grid[tile->x][tile->y] = 1;
    }
  }
  std::copy(roomToLoad->tiles.begin(), roomToLoad->tiles.end(), std::back_inserter(entities));
  std::copy(roomToLoad->transitionTiles.begin(), roomToLoad->transitionTiles.end(), std::back_inserter(transitionTiles));
  // Add players back to entities vector
  for (Player* pc : players) {
    entities.push_back(pc);
  }
  background = roomToLoad->background;
  fprintf(stderr, "Successful loadRoom\n");
  // For testing setGridFromString
  // setGridFromString("w21e18w2e18w2e18w2e18w2e18w2e18w2e18w2e18w2e18w2e18w21");
}


void World::update(Game& game) {
  player->update();
}



void World::enterCombat(Game& game, const std::string& battleId) {
  GameState* combat = new Combat(battleId);
  game.changeState(combat);
}
