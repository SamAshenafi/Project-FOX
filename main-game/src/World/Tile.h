// Tile.h
#pragma once

#include <string>
#include "raylib.h"
#include "Entity.h"
#include <iostream>
#include <fstream>
#include "../../external-libs/nlohmann/json.hpp"

class Tile : public Entity {
  public:
    // NOTE: id, x, and y are inherited from GameObject already
    bool isBlockMovement;

    Tile(
        const std::string& tileId,
        int tileX,
        int tileY,
        bool isBlockMovement
        );

    // void interact() override;
    std::pair<std::string, std::string> interact();
    // void draw(int gridSize);
    void render(int gridWidth, int gridHeight) override;
};

class CombatTile : public Tile {
  public:
    CombatTile(
        const std::string& tileId,
        int tileX,
        int tileY,
        bool isBlockMovement
        );

    std::pair<std::string, std::string> interact();
};

class ChestTile : public Tile {
  public:
    ChestTile(
        const std::string& tileId,
        int tileX,
        int tileY,
        bool isBlockMovement
        );

    std::pair<std::string, std::string> interact();
};