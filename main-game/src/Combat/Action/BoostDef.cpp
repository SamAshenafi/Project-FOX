#include "BoostDef.h"

BoostDef::BoostDef(int stack) {
    targetType = "self";
    amount = stack;
}

BoostDef::~BoostDef() {
}

int BoostDef::perform(Unit* user, std::vector<Unit*> targets, Game& game) {
  for (Unit* target : targets) {

    // perform algorithm for the action
    Token* new_token = target->createToken("DefBoost", amount);
    if (target->tokens.size() == 0) {
      target->bonusDef += target->baseDef * 0.50;
      target->tokens.push_back(new_token);
    } 
    else if (target->tokens.size() <= 10) {
      for (Token* pending : target->tokens) {
        if (pending->tokenID == new_token->tokenID) {
          new_token->tokenID++;
          pending = target->tokens[0];
        }
      }
      target->bonusDef += target->baseDef * 0.50;
      target->tokens.push_back(new_token);
    }

    //will need to modigy for actions containing multiple
    fprintf(
      stderr,
      "%s performed [Boost Defence] on %s!!!\n",
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
      "%s defnece is now %i!!!\n",
      target->id.c_str(),
      target->getDef()
    );
    
  }
  user->energy -= energyCost;
  // fprintf(stderr, "%s performed [Strike]!!!\n", user->id.c_str());
  return animationDuration;
};