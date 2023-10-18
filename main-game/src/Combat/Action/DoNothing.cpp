#include "DoNothing.h"

DoNothing::DoNothing() {
}

DoNothing::~DoNothing() {
}

int DoNothing::perform(Unit* user, Unit* target, Game& game) {
  user->energy -= energyCost;
  fprintf(stderr, "%s performed [Do Nothing]!!!\n", user->id.c_str());
  return animationDuration;
};
