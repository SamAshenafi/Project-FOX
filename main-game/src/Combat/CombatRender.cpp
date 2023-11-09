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

void rTokenSprite (Texture2D sprite, int pos, int screenWidth, int screenHeight)
{
  int spriteWidth = 10 * 2;
  int spriteHeight = 10 * 3;
  Rectangle src = {
      0,
      0,
      static_cast<float>(spriteWidth),
      static_cast<float>(spriteHeight)
    };

  Rectangle dest = {
      static_cast<float>(pos),
      static_cast<float>(0.18 * screenHeight),
      static_cast<float>(screenWidth/8), //sizes are planned to change
      static_cast<float>(screenHeight/4), //sizes are planned to change
    };
  
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
    //Stat box bellow units
  DrawRectangle(
    screenWidth - screenWidth*0.98,
    screenHeight - screenHeight*0.40,
    screenWidth*0.96,
    screenHeight*0.30,
    GRAY
  );
    //Box Showing Available Actions
  DrawRectangle(
    screenWidth - screenWidth*0.96,
    screenHeight - screenHeight*0.38,
    screenWidth*0.30,
    screenHeight*0.26,
    ORANGE
  );
    //Box containing actions descriptions
  DrawRectangle(
    screenWidth - screenWidth*0.65,
    screenHeight - screenHeight*0.38,
    screenWidth*0.62,
    screenHeight*0.26,
    ORANGE
  );

  //renders the actions
  if(currentUnit != nullptr && isHero(currentUnit)) {
    std::vector<std::string> actionBox = {};
    actionBox = currentUnit->actionList;

    if (selected > 3) {
      for (int i = selected - 3 ; i>0 ; i--) {
        actionBox.erase(actionBox.begin());
      }
    }

    while (actionBox.size() > 4) actionBox.pop_back();

    int pos = 0;
    for(std::string actions : actionBox) {
      DrawText(
      actions.c_str(),
      screenWidth - (screenWidth*0.96 - 20),  // X position of the text
      screenHeight - (screenHeight*0.20 + (25*pos)),  // Y position of the text
      28,  // Font size
      WHITE
      );
      pos++;
    }
    //renders the action descriptions
    
    //renders the pointer (use selected)
    Action* action = currentUnit->getAction();
    if (action == nullptr) {
      int pos = selected;
      if (selected > 3) pos = 3;
      DrawRectangle(
        screenWidth - (screenWidth*0.96),
        screenHeight - (screenHeight*0.20 + (25*pos)),
        10,
        10,
        BLUE
      );
    }
    else {
      DrawRectangle(
        screenWidth/2 + (96*(selected) + 32*(selected+1)),
        screenHeight*0.10,
        10,
        10,
        RED
      );
    }
  }  

  

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
  int pos = 0;
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
      hero->tokens,
      isHero(hero),
      isFoe(hero)
    );
    pos++;
  }
  pos = 0;
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
      foe->tokens,
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
  std::vector<Token*> tokens,
  bool isHero,
  bool isFoe
)
{
  if(isHero)
  {
    pos = screenWidth/2 - (96*(pos+1) + (32*pos+1));
    rUnitSprite(sprite, pos, screenWidth, screenHeight);
    DrawRectangle(
    pos ,
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
      0.25 * screenHeight,  // Y position of the text
      20,  // Font size
      WHITE
      );
    //energy
    //TODO: add energy render

    //renders tokens if available
    int i = 0;
    for(Token* token : tokens) {
      int tokenPos = pos + (tokens.size() * 15);
      DrawRectangle(
        tokenPos,
        screenHeight*0.18,
        10,
        10,
        PURPLE
      );

      // Uncomment this and delete above when token sprites are made
    //   rTokenSprite(
    //     token->sprite,
    //     tokenPos,
    //     screenWidth,
    //     screenHeight
    //     );
    // }
      i++;
    }
  }
  else if (isFoe) 
  {
    pos = screenWidth/2 + (96*(pos) + 32*(pos+1));
    rUnitSprite(sprite, pos, screenWidth, screenHeight);
    DrawRectangle(
    pos,
    0.30 * screenHeight,
    10,
    10,
    BLUE
    );

    DrawRectangle(
    screenWidth/2,
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
        0.25 * screenHeight,  // Y position of the text
        20,  // Font size
        WHITE
        );
    //energy
    //TODO: add energy render
    //renders tokens if available
    int i = 0;
    for(Token* token : tokens) {
      int tokenPos = pos + (i * 15);
      DrawRectangle(
        tokenPos,
        screenHeight*0.18,
        10,
        10,
        PURPLE
      );

      // Uncomment this and delete above when token sprites are made
    //   rTokenSprite(
    //     token->sprite,
    //     tokenPos,
    //     screenWidth,
    //     screenHeight
    //     );
    // }
    i++;
    }
    return;
  }
}