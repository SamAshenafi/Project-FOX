#pragma once
#include "Entity.h"
// #include "Combat/Unit.h"
// #include "enums.h"
#include <string>
#include "World.h"
#include <queue>

class World;

class Player : public Entity {
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

    // For stopping movement during dialogue
    bool movable;

    // Animation duration
    int animationDuration = 0;

    // Animation Frame
    int animationFrame = 2;

    Player(
        const std::string& playerId,
        int playerX,
        int playerY,
        std::string facing,
        Inventory playerInventory
        );

    std::queue<std::pair<int, int>> pathQueue = {};

    void processInput(Game&);
    void move(int newX, int newY);

    //stats specific
    // int exp;
    // int level = (level * 100 * 1.25) * exp;
    // std::vector<equipment*> equipments;

    // Shared
    void render(int gridWidth, int gridHeight);
    void update();

    std::string inputHelper(std::string facing);
    void findShortestPath(World& world, int startX, int startY, int targetX, int targetY);
};


