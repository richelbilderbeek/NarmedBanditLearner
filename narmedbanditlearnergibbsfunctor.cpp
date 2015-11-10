#include "narmedbanditlearnergibbsfunctor.h"

#include <cmath>

double ribi::nabl::GibbsFunctor::operator() (const double sum, const double x) const
{
  return sum + Gibbs(x);
}

double ribi::nabl::GibbsFunctor::Gibbs(const double x) const
{
  return std::exp( x / mTau );
}

double ribi::nabl::GibbsFunctor::Gibbs(const double x, const double tau)
{
  return std::exp( x / tau );
}
