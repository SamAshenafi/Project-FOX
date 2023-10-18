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

    int baseAtk;
    int bonusAtk;
    int baseDef;
    int bonusDef;

    int baseEnergy = 1;
    int energy;

    std::vector<Token*> tokens = {};
    std::vector<Action*> actions = {};

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

    int getDef() {
      return baseDef + bonusDef;
    }
    int getAtk() {
      return baseAtk + bonusDef;
    }
    int getSpeed() {
      return baseSpeed + bonusSpeed;
    }

    Action* getAction() {
      Action* action = selectedAction;
      selectedAction = nullptr;
      return action;
    };

    void takeDmg(int dmg) {
      fprintf(stderr, "Take %d damage\n", dmg);
    }

    void onTurnStart() {
      fprintf(stderr, "%s's Turn\n", id.c_str());
      bonusMaxHp = 0;
      bonusAtk = 0;
      bonusDef = 0;

      for (Token* token : tokens) {
        token->onTurnStart(*this);
      }
      // for (Equipment* equipment : equipments) {
      // }
    }
    void onTurnEnd() {
      fprintf(stderr, "%s's Turn Ended\n", id.c_str());
      bonusMaxHp = 0;
      bonusAtk = 0;
      bonusDef = 0;
      bonusSpeed = 0;

      for (Token* token : tokens) {
        token->onTurnEnd(*this);
      }
      // for (Equipment* equipment : equipments) {
      // }
    }

    void onRoundStart() {
      energy = baseEnergy;
      bonusSpeed = GetRandomValue(0, 6);
      // get speed modifier from other

      for (Token* token : tokens) {
        token->onRoundStart(*this);
      }
    }
    void onRoundEnd() {
      for (Token* token : tokens) {
        token->onRoundEnd(*this);
      }
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
};
