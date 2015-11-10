#include "narmedbanditlearnernarmedbandit.h"

#include <cassert>

#include "narmedbanditlearnerhelper.h"

ribi::nabl::NarmedBandit::NarmedBandit(const std::vector<double>& chances)
: mChances(chances)
{

}

bool ribi::nabl::NarmedBandit::PlayAction(const int action) const
{
  //Assert action is a valid index
  assert(action >= 0 && action < static_cast<int>(mChances.size()));
  //Determine the chance to win of this arm
  const double pWin = mChances[action];
  if (GetRandomUniform() < pWin)
    return true;  //Won!
  else
    return false; //Lost
}
