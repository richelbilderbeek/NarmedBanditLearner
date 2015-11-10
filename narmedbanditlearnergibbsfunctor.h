#ifndef NARMEDBANDITLEARNERGIBBSFUNCTOR_H
#define NARMEDBANDITLEARNERGIBBSFUNCTOR_H

#include <vector>

namespace ribi {
namespace nabl {

struct GibbsFunctor
{
  GibbsFunctor(const double& tau) : mTau(tau) {}
  double operator() (const double sum, const double x) const;
  const double mTau;
  double Gibbs(const double x) const;
  static double Gibbs(const double x, const double tau);
};


} //~namespace nabl
} //~namespace ribi


#endif // NARMEDBANDITLEARNERGIBBSFUNCTOR_H
