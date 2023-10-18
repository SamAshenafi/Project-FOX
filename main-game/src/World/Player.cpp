// Player.cpp
#include "Player.h"
#include "../Helper.h"
#include <cstdio>

Player::Player(
    const std::string& playerId,
    int playerX,
    int playerY,
    std::string facing
    ) :
  facing(facing)
{
  id = playerId;
  x = playerX;
  y = playerY;
  // "fox.png" does not exist
  sprite = Helper::loadTexture("fox.png");
  // flippedSprite = Helper::loadTexture("fox.png");
}

void Player::render(int gridWidth, int gridHeight) {
  // TODO: Sprite render good now?
  // Need clean up, this code is bad lol
  // TODO: There's also walking animation in the spritesheet
  // if you can get that working that would be great

  // Old red rectangle, to be remove? or keep to debug?
  // DrawRectangle(
  //     x * gridWidth,
  //     y * gridHeight,
  //     gridWidth,
  //     gridHeight,
  //     RED);

  Rectangle src = {
    0,
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
    0,
    static_cast<float>(spriteHeight),
    static_cast<float>(spriteWidth),
    static_cast<float>(spriteHeight)
  };
  Rectangle up = {
    0,
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

