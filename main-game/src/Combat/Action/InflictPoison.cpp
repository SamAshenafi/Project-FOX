#include "InflictPoison.h"
#include "../Token/Poison.h"

// InflictPoison::InflictPoison() {
// }

// InflictPoison::~InflictPoison() {
// }

// int InflictPoison::perform(Unit* user, std::vector<Unit*> targets, Game& game) {
//   for (Unit* target : targets) {

//     // perform algorithm for the action
//     target->tokens.push_back(new Token(1));

//     //will need to modigy for actions containing multiple
//     fprintf(
//       stderr,
//       "%s performed [InflictPoison] on %s!!!\n",
//       user->id.c_str(),
//       target->id.c_str()
//     );
//     fprintf(
//       stderr,
//       "the strike delt %i damage to target\n",
//       user->baseAtk
//     );
//     fprintf(
//       stderr,
//       "%s hp is now %i!!!\n",
//       target->id.c_str(),
//       target->hp
//     );
    
//   }
//   user->energy -= energyCost;
//   // fprintf(stderr, "%s performed [Strike]!!!\n", user->id.c_str());
//   return animationDuration;
// };