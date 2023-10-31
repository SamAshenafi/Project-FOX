// World.h
#pragma once

#include <string.h>
#include "../GameState.h"
#include "Room.h"
#include "Entity.h"
#include "Player.h"
#include "Tile.h"
#include "TransitionTile.h"
#include "../../external-libs/nlohmann/json.hpp"
#include "../Game.h"

// class Game;
class Player;

class World : public GameState {
  public:
    World(std::string roomId); // destructor
    ~World() override; // destructor

    void processInput(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

    const double moveSpeed = 0.1;
    double lastMoveTime = 0;

    int grid[20][12];
    // int rows = sizeof(grid) / sizeof(grid[0]);
    // int columns = sizeof(grid[0]) / sizeof(grid[0][0]);
    int columns = sizeof(grid) / sizeof(grid[0]);
    int rows = sizeof(grid[0]) / sizeof(grid[0][0]);

    std::vector<Room*> rooms;
    Room* currentRoom = nullptr;

    std::vector<Entity*> entities;
    std::vector<TransitionTile*> transitionTiles;
    std::vector<Player*> players;
    Player* player = nullptr;

    // these will only be used when loadSave() & saveSave() is called
    //// player data
    int playerX = 0;
    int playerY = 0;
    std::string playerFacing = "down";

    // Input


    std::queue<std::pair<int, int>> pathQueue;

    Texture2D background;

    void loadRoom(const std::string& roomId);

    // Helpers
    Room* buildRoom(const std::string& roomId, nlohmann::json source);
    void setGridFromString(std::string roomInfo);
    void setRoom(Room* roomToSet);
    Room* findRoom(const std::string& roomId);
    // std::string inputHelper(std::string facing);
    // void findShortestPath(Game& game, int startX, int startY, int targetX, int targetY);

    void enterCombat(Game& game, const std::string& battleId);

    void resetGrid(); // set all in grid to 0
    void sortGameObjects();
    void clearPathQueue();
    void removeEntity(const std::string& tileId);

  private:
    // void handleKeyPressO();

    // processMovement();

};
