// Player.cpp
#include "Player.h"
#include "../Helper.h"
#include <cstdio>
#include "Inventory.h"
Player::Player(
    const std::string& playerId,
    int playerX,
    int playerY,
    std::string facing,
    Inventory playerInventory
    ) :
  facing(facing)
{
  id = playerId;
  x = playerX;
  y = playerY;
  inventory = playerInventory;
  sprite = Helper::loadTexture("fox.png");
  movable = true;
  ItemAssets::Initialize();
  inventory.AddItem("bronze_sword");
}

void Player::render(int gridWidth, int gridHeight) {
  // TODO: Sprite render good now?
  // Need clean up, this code is bad lol
  // TODO: There's also walking animation in the spritesheet
  // if you can get that working that would be great

  if (animationFrame > 2 || animationFrame < 0) {
    fprintf(stderr, "Animation frame (%i) invalid\n", animationFrame);
    animationFrame = 0;
  }

  int animationPosition = animationFrame * gridWidth * 4;

  Rectangle src = {
    animationPosition,
    0,
    static_cast<float>(gridWidth * 4),
    static_cast<float>(gridHeight * 6)
  };


  offsetX = 0.5;
  offsetY = 2;
  Rectangle dest = {
    static_cast<float>((x - offsetX) * gridWidth),
    static_cast<float>((y - offsetY) * gridHeight - offsetY),
    static_cast<float>(2 * gridWidth),
    static_cast<float>(3 * gridHeight),
  };
  int spriteWidth = 96 * 2;
  int spriteHeight = 80 * 3;
  Rectangle down = {
    animationPosition,
    static_cast<float>(spriteHeight),
    static_cast<float>(spriteWidth),
    static_cast<float>(spriteHeight)
  };
  Rectangle up = {
    animationPosition,
    static_cast<float>(spriteHeight * 2),
    static_cast<float>(spriteWidth),
    static_cast<float>(spriteHeight)
  };
  if (facing == "down") {
    src = down;
  }
  else if (facing == "up") {
    src = up;
  }
  else if (facing == "left") {
    src.width *= -1;
  }
  DrawTexturePro(
      sprite,
      src,
      dest,
      {0, 0},
      0.0,
      WHITE
      );
  return;
}

void Player::move(int newX, int newY) {
  x = newX;
  y = newY;
}

void Player::update() {
  if (animationDuration > 0) {
    // fprintf(stderr, "[ANIMATION]: %d\n", animationDuration);
    animationDuration -= 1;
    return;
  }
  else animationDuration += 6;
  if (animationFrame > 0) animationFrame -= 1;
  else animationFrame = 2;

  // Continue moving along the path until the queue is empty
  while (!pathQueue.empty()) {
    std::pair<int, int> nextPos = pathQueue.front();
    pathQueue.pop();
    if (nextPos.first < x) {
      facing = "left";
    }
    else if (nextPos.first > x) {
      facing = "right";
    }
    else if (nextPos.second < y) {
      facing = "up";
    }
    else if (nextPos.second > y) {
      facing = "down";
    }
    move(nextPos.first, nextPos.second);
    animationDuration += 6;
    break;
  }
}

