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
    std::pair<std::string, std::string> interact() override;
    // void draw(int gridSize);
    void render(int gridWidth, int gridHeight) override;

  protected:
    std::string tileText = "";
};

class CombatTile : public Tile {
  public:
    CombatTile(
      const std::string& tileId,
      int tileX,
      int tileY,
      bool isBlockMovement
      );

    std::pair<std::string, std::string> interact() override;
};

class NpcTile : public Tile {
  public:
    NpcTile(
      const std::string& tileId,
      int tileX,
      int tileY,
      bool isBlockMovement
      );

    std::pair<std::string, std::string> interact() override;
};

class ChestTile : public Tile {
  public:
    ChestTile(
      const std::string& tileId,
      int tileX,
      int tileY,
      bool isBlockMovement
      );

    std::pair<std::string, std::string> interact() override;

    // Inventory data below:
};

class DoorTile : public Tile {
  public:
    DoorTile(
      const std::string& tileId,
      int tileX,
      int tileY,
      bool isBlockMovement
      );

    std::pair<std::string, std::string> interact() override;
    // Depending on what we have art-wise, we can either have doors open, and change their sprite,
    // Or we can delete them, so we only need one sprite
    void open();
};