#include "DoNothing.h"

DoNothing::DoNothing() {
}

DoNothing::~DoNothing() {
}

void DoNothing::perform(Unit* user, Unit* target, Game& game) {
  energyCost = 1;
  user->energy -= energyCost;
  fprintf(stderr, "%s performed Do Nothing!!!!!\n", user->unitId.c_str());
};
