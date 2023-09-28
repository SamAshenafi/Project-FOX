#include "GameObject.h"
#include "enums.h"
#include <string>

// TODO: a lot lol
class Player : public GameObject {
  public:
    // NOTE: id, x, and y are inherited from GameObject already
    std::string facing;

    // NOTE: use Tile.cpp for similar constuctor in Player.cpp
    Player(
        const std::string& playerId,
        int playerX,
        int playerY,
        std::string facing
        );

    void render(int gridWidth, int gridHeight);
    void move(int newX, int newY);
};

