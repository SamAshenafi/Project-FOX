//CombatRender.cpp
//Helper Class
#include "Combat.h"
#include "Unit.h"
#include <cstdio>
#include <raylib.h>

void rUnitSprite(Texture2D sprite, int pos, int screenWidth, int screenHeight)
{
    int spriteWidth = 96 * 2;
    int spriteHeight = 80 * 3;
    Rectangle src = {
      0,
      0,
      static_cast<float>(spriteWidth),
      static_cast<float>(spriteHeight)
    };

    Rectangle dest = {
      static_cast<float>(pos),
      static_cast<float>(0.30 * screenHeight),
      static_cast<float>(screenWidth/8), //sizes are planned to change
      static_cast<float>(screenHeight/4), //sizes are planned to change
    };

    //render's hero's position
    DrawTexturePro(
    sprite,
    src,
    dest,
    {0, 0},
    0.0,
    WHITE
    );
}


// Combat Helpers //
//loadTexture
Texture2D Combat::loadTexture(std::string filePath) 
{
  std::string fileType = ".png";
  std::string fullFilePath = "./assets/combat/" + filePath + fileType;
  return LoadTexture(fullFilePath.c_str());
}

//RenderUI
void Combat::RenderUI(int screenWidth, int screenHeight)
{
  //first renders the boxes
  DrawRectangle(
    screenWidth - screenWidth*0.98,
    screenHeight - screenHeight*0.40,
    screenWidth*0.96,
    screenHeight*0.30,
    GRAY
  );

  //then renders the actions 
}

//Render Units
void Combat::RenderUnits
(
  std::vector<Unit*> heroes,
  std::vector<Unit*> foes,
  int screenWidth,
  int screenHeight
)
{
  int pos = 1;
  for (Unit* hero : heroes)
  {
    hero->RenderSprite(
      hero->sprite,
      hero->hp,
      hero->getMaxHp(),
      hero->energy,
      screenWidth,
      screenHeight,
      pos,
      isHero(hero),
      isFoe(hero)
    );
    pos++;
  }
  pos = 1;
  for (Unit* foe : foes)
  {
    foe->RenderSprite(
      foe->sprite,
      foe->hp,
      foe->getMaxHp(),
      foe->energy,
      screenWidth,
      screenHeight, 
      pos,
      isHero(foe),
      isFoe(foe));
    pos++;
  }
}

// Unit Helpers //
//Render Unit Sprites
void Unit::RenderSprite
( 
  Texture2D sprite,
  int hp,
  int maxHp,
  int energy,
  int screenWidth,
  int screenHeight, 
  int pos,
  bool isHero,
  bool isFoe
)
{
  if(isHero)
  {
    pos = screenWidth/2 - (96*pos+1 + (32));
    rUnitSprite(sprite, pos, screenWidth, screenHeight);
    DrawRectangle(
    pos,
    0.30 * screenHeight,
    10,
    10,
    BLUE
    );

    //render's hero's stats
    //health TODO: improve this line?
    const std::string healthText = (std::to_string(hp) + "/" + std::to_string(maxHp));
    DrawText(
      healthText.c_str(),
      pos,  // X position of the text
      0.10 * screenHeight,  // Y position of the text
      20,  // Font size
      WHITE
      );
    //energy
    //TODO: add energy render
  }
  else if (isFoe) 
  {
    pos = screenWidth/2 + (96*pos);
    if (pos > 0) pos += 32;
    rUnitSprite(sprite, pos, screenWidth, screenHeight);
    DrawRectangle(
    pos,
    0.30 * screenHeight,
    10,
    10,
    BLUE
    );

    //render's foe's stats
    //health
    //TODO: improve this line of code
    const std::string healthText = (std::to_string(hp) + "/" + std::to_string(maxHp));
    DrawText(
        healthText.c_str(),
        pos,  // X position of the text
        0.10 * screenHeight,  // Y position of the text
        20,  // Font size
        WHITE
        );
    //energy
    //TODO: add energy render
    //Tokens
    //TODO: and Token render
    }
    return;
}