#include "Heal.h"

Heal::Heal(int insert) {
  targetType = "self";
  amount = insert;
  fprintf(stderr, "amount = %d\n", amount);
}

Heal::~Heal() {
}

//might need to modify for 
int Heal::perform(Unit* user, std::vector<Unit*> targets,  Game& game) {
  for (Unit* target : targets) {

    fprintf(stderr, "amount = %d\n", this->amount);
    // perform algorithm for the action
    if(target->getMaxHp() >= target->hp) target->hp = target->hp + this->amount;

    //will need to modigy for actions containing multiple
    fprintf(
      stderr,
      "%s performed [Heal] on %s!!!\n",
      user->id.c_str(),
      user->id.c_str()
    );
    // fprintf(
    //   stderr,
    //   "the strike delt %i damage to target\n",
    //   user->baseAtk
    // );
    fprintf(
      stderr,
      "%s hp is now %i!!!\n",
      user->id.c_str(),
      user->hp
    );
    
  }
  user->energy -= energyCost;
  // fprintf(stderr, "%s performed [Strike]!!!\n", user->id.c_str());
  return animationDuration;
};