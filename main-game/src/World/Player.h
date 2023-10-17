#pragma once
#include "Entity.h"
#include "../Combat/Unit.h"
// #include "enums.h"
#include <string>

// TODO: a lot lol
class Player : public Entity, public Unit {
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

    //stats specific
    // int exp;
    // int level = (level * 100 * 1.25) * exp;
    // std::vector<equipment*> equipments;
    std::vector<Player> team;

    Player(
        const std::string& playerId,
        int playerX,
        int playerY,
        std::string facing,
        std::vector<Player> party
        //int exp //what the current exp of the player
        //int level //current level of player
        //equipments //what equipment was the player carrying
        );

    Player( //for initialization in world.cpp
        const std::string& playerId,
        int playerX,
        int playerY,
        std::string facing
        //int exp //what the current exp of the player
        //int level //current level of player
        //equipments //what equipment was the player carrying
        );

    Player() {}; // for initializing stats for player party

    void move(int newX, int newY);



    // Shared
    // void interact();
    void render(int gridWidth, int gridHeight);
};


