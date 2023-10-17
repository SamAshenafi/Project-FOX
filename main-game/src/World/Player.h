#pragma once
#include "Entity.h"
// #include "Combat/Unit.h"
// #include "enums.h"
#include <string>

// TODO: a lot lol
class Player : public Entity { //: public Unit {
  public:
    std::string facing;

    // Rectangle right = { 0, 0, 96 * 2, 80 * 3 };
    // Rectangle down = { 0, 80 * 3, 96 * 2, 80 * 3 * 2 };
    // Rectangle up = { 0, 80 * 3 * 2, 96 * 2, 80 * 3 * 3 };
    // Rectangle left = { 0, 0, 96 * 2, 80 * 3 };
    //
    // Rectangle right = { 0, 0, 48 * 2, 40 * 3 };
    // Rectangle down = { 0, 40 * 3, 48 * 2, 40 * 3 * 2 };
    // Rectangle up = { 0, 40 * 3 * 2, 48 * 2, 40 * 3 * 3 };
    // Rectangle left = { 0, 0, 48 * 2, 40 * 3 };

    // Texture2D flippedSprite;

    Player(
        const std::string& playerId,
        int playerX,
        int playerY,
        std::string facing
        );

    void move(int newX, int newY);

    //stats specific
    int exp;
    int level = (level * 100 * 1.25) * exp;
    // std::vector<equipment*> equipments;

    // Shared
    void render(int gridWidth, int gridHeight);
};


