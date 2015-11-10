#include "narmedbanditlearnerhelper.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>

std::vector<double> ribi::nabl::GetDefaultChances() noexcept
{
  std::vector<double> chances;
  chances.push_back(0.1);
  chances.push_back(0.2);
  chances.push_back(0.4);
  chances.push_back(0.6);
  chances.push_back(0.8);
  chances.push_back(0.9);
  std::random_shuffle(chances.begin(), chances.end());
  return chances;
}

//From htpp://www.richelbilderbeek.nl/CppGetRandomUniform.htm
double ribi::nabl::GetRandomUniform() noexcept
{
  return static_cast<double>(std::rand())/static_cast<double>(RAND_MAX);
}


//From http://www.richelbilderbeek.nl/CppRandomizeTimer.htm
void ribi::nabl::RandomizeTimer() noexcept
{
  std::srand(std::time(0));
}
