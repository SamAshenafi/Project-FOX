#include "DoNothing.h"

DoNothing::DoNothing() {
}

DoNothing::~DoNothing() {
}

int DoNothing::perform(Unit* user, std::vector<Unit*> targets, Game& game) {
  for (Unit* target : targets) {
    fprintf(
      stderr,
      "%s performed [Do Nothing] on %s!!!\n",
      user->id.c_str(),
      target->id.c_str()
    );
  }
  user->energy -= energyCost;
  // fprintf(stderr, "%s performed [Do Nothing]!!!\n", user->id.c_str());
  return animationDuration;
};
