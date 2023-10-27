#include "Room.h"
#include <algorithm>

Room::Room(
  std::string id,
  int roomGrid[20][12],
  std::vector<Tile*> roomTiles,
  std::vector<TransitionTile*> roomTransitions,
  Texture2D roomBackground
) {
  roomId = id;
  std::copy(&roomGrid[0][0], &roomGrid[0][0]+20*12, &grid[0][0]);
  tiles = roomTiles;
  transitionTiles = roomTransitions;
  background = roomBackground;
}

void Room::removeTile(const std::string& tileId) {
  auto found = [tileId](Tile* tile) {
    return (tile->id == tileId);
  };
  auto foundTile = std::find_if(tiles.begin(), tiles.end(), found);
  grid[(*foundTile)->x][(*foundTile)->y] = 0;
  tiles.erase(foundTile);
}