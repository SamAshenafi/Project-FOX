// Tile.cpp
#include "Tile.h"
#include "../Helper.h"

Tile::Tile(
    const std::string& tileId,
    int tileX,
    int tileY,
    bool isBlockMovement
    ) :
  isBlockMovement(isBlockMovement)
{
  id = tileId;
  x = tileX;
  y = tileY;
}

std::pair<std::string, std::string> Tile::interact() {
  std::string tileType = Helper::parseGameObjectType(id);
  return std::make_pair(tileType, tileText);
}

void Tile::render(int gridWidth, int gridHeight) {
  // Placeholder is now set up for implementation of sprites.
  // Will be restructured once some sprites are in

  // PLACEHOLDER:
  Color color = BLUE;
  std::string tileType = Helper::parseGameObjectType(id);
  if (tileType == "chest") {
    // color = YELLOW;
    renderHelper(gridWidth, gridHeight);
    return;
  }
  else if (tileType == "npc") {
    // color = GREEN;
    renderHelper(gridWidth, gridHeight);
    return;
  }
  else if (tileType == "battle") {
    // color = RED;
    renderHelper(gridWidth, gridHeight);
    return;
  }
  DrawRectangle(
      x * gridWidth,
      y * gridHeight,
      gridWidth,
      gridHeight,
      color);
  return;
}
