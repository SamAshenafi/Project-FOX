#include "Strike.h"

Strike::Strike() {
}

Strike::~Strike() {
}

int Strike::perform(Unit* user, std::vector<Unit*> targets, Game& game) {
  for (Unit* target : targets) {
    fprintf(
      stderr,
      "%s performed [Strike] on %s!!!\n",
      user->id.c_str(),
      target->id.c_str()
    );
  }
  user->energy -= energyCost;
  // fprintf(stderr, "%s performed [Strike]!!!\n", user->id.c_str());
  return animationDuration;
};
