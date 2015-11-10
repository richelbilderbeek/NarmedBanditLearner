#ifndef NARMEDBANDITLEARNERHELPER_H
#define NARMEDBANDITLEARNERHELPER_H

#include <vector>

namespace ribi {
namespace nabl {

//Default chances for the N-armed bandit
std::vector<double> GetDefaultChances() noexcept;

///Don't use for serious applications
double GetRandomUniform() noexcept;

///Don't use for serious applications
void RandomizeTimer() noexcept;

} //~namespace nabl
} //~namespace ribi

#endif // NARMEDBANDITLEARNERHELPER_H
