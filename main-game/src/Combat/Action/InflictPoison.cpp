#include "InflictPoison.h"

InflictPoison::InflictPoison() {
    targetType = "enemy";
}

InflictPoison::~InflictPoison() {
}

int InflictPoison::perform(Unit* user, std::vector<Unit*> targets, Game& game) {
  for (Unit* target : targets) {

    // perform algorithm for the action
    Token* new_token = target->createToken("Poison", 1);
    if (target->tokens.size() == 0 || target->tokens.size() == 10) target->tokens.push_back(new_token);
    else {
      for (Token* pending : target->tokens) {
        if (pending->tokenID == new_token->tokenID) {
          new_token->tokenID++;
          pending = target->tokens[0];
        }
      }
      target->tokens.push_back(new_token);
    }

    //will need to modigy for actions containing multiple
    fprintf(
      stderr,
      "%s performed [InflictPoison] on %s!!!\n",
      user->id.c_str(),
      target->id.c_str()
    );
    // fprintf(
    //   stderr,
    //   "the strike delt %i damage to target\n",
    //   user->baseAtk
    // );
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