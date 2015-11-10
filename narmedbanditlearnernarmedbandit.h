#ifndef NARMEDBANDITLEARNERNARMEDBANDIT_H
#define NARMEDBANDITLEARNERNARMEDBANDIT_H

#include <vector>

namespace ribi {
namespace nabl {

///The N-armed bandit (which are the same as multiple 1-armed bandits)
struct NarmedBandit
{
  NarmedBandit(const std::vector<double>& chances);
  bool PlayAction(const int action) const;
  const std::vector<double> mChances;
};

} //~namespace nabl
} //~namespace ribi

#endif // NARMEDBANDITLEARNERNARMEDBANDIT_H
