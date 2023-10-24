#include "Strike.h"

Strike::Strike() {
}

Strike::~Strike() {
}

int Strike::perform(Unit* user, std::vector<Unit*> targets, Game& game) {
  for (Unit* target : targets) {

    // perform algorithm
    target->hp -= user->getAtk();


    fprintf(
      stderr,
      "%s performed [Strike] on %s!!!\n",
      user->id.c_str(),
      target->id.c_str()
    );
    fprintf(
      stderr,
      "the strike delt %i damage to target\n",
      user->baseAtk
    );
    fprintf(
      stderr,
      "%s hp is now %i!!!\n",
      target->id.c_str(),
      target->hp
    );
    
  }
  user->energy -= energyCost;
  // fprintf(stderr, "%s performed [Strike]!!!\n", user->id.c_str());
  return animationDuration;
};
