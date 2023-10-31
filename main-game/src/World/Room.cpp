#include "Room.h"
#include <algorithm>

Room::Room(
  std::string id,
  std::string roomInfo,
  std::vector<Tile*> roomTiles,
  std::vector<TransitionTile*> roomTransitions,
  Texture2D roomBackground
) {
  roomId = id;
  this->roomInfo = roomInfo;
  tiles = roomTiles;
  transitionTiles = roomTransitions;
  background = roomBackground;
}

void Room::removeTile(const std::string& tileId) {
  auto found = [tileId](Tile* tile) {
    return (tile->id == tileId);
  };
  auto foundTile = std::find_if(tiles.begin(), tiles.end(), found);
  tiles.erase(foundTile);
}