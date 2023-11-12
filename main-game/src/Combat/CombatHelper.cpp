#include "Action/Actions.h"
#include "Combat.h"
#include "Token/Tokens.h"

std::vector<Texture2D> tokenTextures = {};

// loads token textures
void Combat::loadTokenTextures() 
{
  tokenTextures.push_back(loadTexture("Poison"));
  tokenTextures.push_back(loadTexture("AtkBoost"));
  tokenTextures.push_back(loadTexture("DefBoost"));
  tokenTextures.push_back(loadTexture("Warning"));
}

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
  if (foeId == "RazzBerry") return new RazzBerry();
  if (foeId == "BlueBerry") return new BlueBerry();
  return nullptr;
}

Action* Combat::createAction(const std::string& actionId, int amount) {
  // add more here
  if (actionId == "DoNothing") return new DoNothing();
  if (actionId == "Strike") return new Strike();
  if (actionId == "InflictPoison") return new InflictPoison(amount);
  if (actionId == "BoostAtk") return new BoostAtk(amount);
  if (actionId == "BoostDef") return new BoostDef(amount);
  if (actionId == "Heal") return new Heal(amount);
  return nullptr;
}

Token* Unit::createToken(const std::string& tokenId, int stack) {
  if (tokenId == "Poison") return new Poison(stack, tokenTextures[0]);
  if (tokenId == "AtkBoost") return new AtkBoost(stack, tokenTextures[1]);
  if (tokenId == "DefBoost") return new DefBoost(stack, tokenTextures[2]);
}


std::vector<Unit*> Combat::unitsVanquished(std::vector<Unit*> units) {
  for (Unit* unit : units) {
    if(unit->hp <= 0){
      units.erase(units.begin());
      // if(isFoe(unit)) {
      //   // add code for the loot/exp the foe holds
      // }
    }
  }
  return units;
}