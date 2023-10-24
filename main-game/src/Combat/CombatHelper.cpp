#include "Action/DoNothing.h"
#include "Action/Actions.h"
#include "Combat.h"

bool Combat::isHero(Unit* unit) {
  Hero* hero = dynamic_cast<Hero*>(unit);
  return hero != nullptr;
}
bool Combat::isFoe(Unit* unit) {
  Foe* foe = dynamic_cast<Foe*>(unit);
  return foe != nullptr;
}

Foe* Combat::createFoe(const std::string& foeId) {
  // add more here
  if (foeId == "FoxFoe") return new FoxFoe();
  return nullptr;
}

Action* Combat::createAction(const std::string& actionId) {
  // add more here
  if (actionId == "DoNothing") return new DoNothing();
  if (actionId == "Strike") return new Strike();
  return nullptr;
}

bool Combat::foesVanquished(std::vector<Unit*> foes) {
  for (Unit* foe : foes) {
    if(foe->hp > 0) return false;
  }
  return true;
}
bool Combat::heroesVanquished(std::vector<Unit*> heroes) {
  for (Unit* hero : heroes) {
    if(hero->hp > 0) return false;
  }
  return true;
}