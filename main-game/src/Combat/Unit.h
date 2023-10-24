#pragma once
#include <cstdio>
#include <raylib.h>
#include <string>
#include <vector>
// #include "Combat.h"
#include "Token/Token.h"
// #include "Action/Action.h"
// #include "Action/Actions.h"

class Action;
class Token;
class Combat;

class Unit {

  public:
    Unit() {};
    virtual ~Unit() {};

    //character stats
    std::string id;
    int hp;
    int maxHp;
    int bonusMaxHp;

    int baseAtk = 0;
    int bonusAtk = 0;
    int baseDef = 0;
    int bonusDef = 0;

    int baseEnergy = 1;
    int energy = 0;

    std::vector<Token*> tokens = {};
    std::vector<Action*> actions = {};
    std::vector<std::string> actionList = {};

    Action* selectedAction = nullptr;

    int baseSpeed = 0;
    int bonusSpeed = 0;
    
    //ability stats
    // Unit(
    //     std::string name,
    //     int health,
    //     int damage,
    //     int initiative
    //     );

    // double lockOut = 0;
    //
    double startAnimationTime = 0;
    double animationTimer = 0;

    int getMaxHp() {
      return maxHp + bonusMaxHp;
    }
    int getDef() {
      return baseDef + bonusAtk;
    }
    int getAtk() {
      return baseAtk + bonusDef;
    }
    int getSpeed() {
      return baseSpeed + bonusSpeed;
    }

    std::vector<std::string> getActionList(){
      return actionList;
    }

    Action* getAction() {
      Action* action = selectedAction;
      selectedAction = nullptr;
      return action;
    };

    // void takeDmg(int dmg) {
    //   fprintf(stderr, "Take %d damage\n", dmg);
    // }

    int onTurnStart() {
      int totalAnimationDuration = 6;
      fprintf(stderr, "%s's Turn\n", id.c_str());
      bonusMaxHp = 0;
      bonusAtk = 0;
      bonusDef = 0;

      for (Token* token : tokens) {
        totalAnimationDuration += token->onTurnStart(*this);
      }
      // for (Equipment* equipment : equipments) {
      // }
      return totalAnimationDuration;
    }
    int onTurnEnd() {
      int totalAnimationDuration = 2;
      fprintf(stderr, "%s's Turn Ended\n", id.c_str());
      bonusMaxHp = 0;
      bonusAtk = 0;
      bonusDef = 0;
      bonusSpeed = 0;

      for (Token* token : tokens) {
        totalAnimationDuration += token->onTurnEnd(*this);
      }

      return totalAnimationDuration;
      // for (Equipment* equipment : equipments) {
      // }
    }

      int onRoundStart() {
        int totalAnimationDuration = 0;
        energy = baseEnergy;
        bonusSpeed = GetRandomValue(0, 6);
        // get speed modifier from other

        for (Token* token : tokens) {
          totalAnimationDuration += token->onRoundStart(*this);
        }
        return totalAnimationDuration;
      }
      int onRoundEnd() {
        int totalAnimationDuration = 0;
        for (Token* token : tokens) {
          totalAnimationDuration += token->onRoundEnd(*this);
        }
      return totalAnimationDuration;
    }

    // virtual void playAnimation();

    // void playAnimation() {
    //   double currentTime = GetTime();
    //   double deltaTimeSinceLastMove = currentTime - startAnimationTime;
    //   if (deltaTimeSinceLastMove > animationTimer) {
    //     fprintf(stderr, "Animation completed: %f\n", deltaTimeSinceLastMove);
    //     animationTimer = 0;
    //     return;
    //   }
    //   fprintf(stderr, "Animation playing: %f\n", deltaTimeSinceLastMove);
    // }


    virtual void assasdasdasd() {};
    // virtual void takeTurn(Combat* combat) {};

    // void passTurn() {
    //   // Implement logic to pass the turn
    //   // hasTakenTurn = true;
    //   fprintf(stderr, "Character %s passed their turn\n", name.c_str());
    // }

    Texture2D sprite;

    //helper function for rendering
    void RenderSprite(
      Texture2D sprite,
      int hp,
      int maxHp,
      int energy,
      int screenWidth,
      int screenHeight, 
      int pos,
      bool isHero,
      bool isFoe
      );
    // void RenderActions(
    //   int screenWidth,
    //   int screenHeight,
    //   int selectedAction,
    //   std::vector<Action*> actions
    // );
};
