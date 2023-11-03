#include "Tile.h"

// ----------------------- Combat Tile
CombatTile::CombatTile(
    const std::string& tileId,
    int tileX,
    int tileY,
    bool isBlockMovement
) : Tile(tileId, tileX, tileY, isBlockMovement)
{
  // Additional constructor functionality to add to base constructor


}

std::pair<std::string, std::string> CombatTile::interact() {
  std::pair<std::string, std::string> returnValue = Tile::interact();

  return returnValue;
}

// ----------------------- Chest Tile
ChestTile::ChestTile(
    const std::string& tileId,
    int tileX,
    int tileY,
    bool isBlockMovement
) : Tile(tileId, tileX, tileY, isBlockMovement)
{
  // Additional constructor functionality to add to base constructor


}