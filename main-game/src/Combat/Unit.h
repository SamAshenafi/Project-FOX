#pragma once
#include <raylib.h>
#include <string>
#include <vector>
#include "Token/Token.h"
// #include "Use/Use.h"

class Action;
class Token;

class Unit {

  public:
    Unit() {};

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

    int baseSpeed;
    int bonusSpeed;

    //ability stats
    // Unit(
    //     std::string name,
    //     int health,
    //     int damage,
    //     int initiative
    //     );


    int getDef() {
      return baseDef + bonusDef;
    }
    int getAtk() {
      return baseAtk + bonusDef;
    }

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


    virtual void asdasdasdasd() {};

    // void passTurn() {
    //   // Implement logic to pass the turn
    //   // hasTakenTurn = true;
    //   fprintf(stderr, "Character %s passed their turn\n", name.c_str());
    // }
};
