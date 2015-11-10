#include "narmedbanditlearnerselection.h"

#include <cassert>
#include <numeric>
#include <cstdlib>

#include "narmedbanditlearnergibbsfunctor.h"
#include "narmedbanditlearnerhelper.h"

int ribi::nabl::SelectIndexSoftmax(const std::vector<double>& chances, const double tau)
{
  const int nChances = chances.size();
  const double sumChances = std::accumulate(chances.begin(), chances.end(),0.0,GibbsFunctor(tau));
  if (sumChances == 0.0) return std::rand() % nChances;

  double p = GetRandomUniform() * sumChances;
  int i = -1; //The index that will be chosen
  for (i=0; i<nChances; ++i)
  {
    assert(chances[i] >= 0.0);
    const double chance = GibbsFunctor::Gibbs(chances[i],tau);
    assert(chance >= 0.0);
    p-=chance;
    if (p<0.0) break;
  }
  assert(i != nChances);
  return i;
}

int ribi::nabl::SelectionEqual::SelectIndex(const std::vector<double>& chances) const
{
  const int nChances = chances.size();
  const double sumChances = std::accumulate(chances.begin(), chances.end(),0.0);
  if (sumChances == 0.0) return std::rand() % nChances;

  double p = GetRandomUniform() * sumChances;
  int i = -1; //The index that will be chosen
  for (i=0; i<nChances; ++i)
  {
    assert(chances[i] >= 0.0);
    p-=chances[i];
    if (p<0.0) break;
  }
  assert(i != nChances);
  return i;
}

int ribi::nabl::SelectionSoftmax::SelectIndex(const std::vector<double>& chances) const
{
  const int nChances = chances.size();
  const double sumChances = std::accumulate(chances.begin(), chances.end(),0.0,GibbsFunctor(mTau));
  if (sumChances == 0.0) return std::rand() % nChances;

  double p = GetRandomUniform() * sumChances;
  int i = -1; //The index that will be chosen
  for (i=0; i<nChances; ++i)
  {
    assert(chances[i] >= 0.0);
    const double chance = GibbsFunctor::Gibbs(chances[i],mTau);
    assert(chance >= 0.0);
    p-=chance;
    if (p<0.0) break;
  }
  assert(i != nChances);
  return i;
}
