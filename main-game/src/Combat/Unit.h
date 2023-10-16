#pragma once
#include <string>
#include <vector>

class Unit {

  public:
  //character stats
    std::string name;
    int HP;
    int maxHP;

    int baseDmg;
    int dmg;

    int baseDef;
    int def;

    int maxEnergy;
    int energy;

    std::vector<Token*> tokens;

    std::vector<Use*> moves;

    int speed;
    int initiative;

    //ability stats
    

    Unit(
        std::string name,
        int health,
        int damage,
        int initiative
        ) :
      name(name),
      health(health),
      damage(damage),
      hasTakenTurn(false),
      initiative(initiative) {}

    void passTurn() {
      // Implement logic to pass the turn
      hasTakenTurn = true;
      fprintf(stderr, "Character %s passed their turn\n", name.c_str());
    }
};
