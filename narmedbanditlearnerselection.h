#ifndef NARMEDBANDITLEARNERSELECTION_H
#define NARMEDBANDITLEARNERSELECTION_H

#include <vector>

namespace ribi {
namespace nabl {

//A State
struct SelectionBase
{
  virtual int SelectIndex(const std::vector<double>& chances) const = 0;
  virtual ~SelectionBase() {} //Every base class must have virtual destructor
};

int SelectIndexSoftmax(const std::vector<double>& chances, const double tau);

struct SelectionEqual : public SelectionBase
{
  int SelectIndex(const std::vector<double>& chances) const override;
};

struct SelectionSoftmax : public SelectionBase
{
  SelectionSoftmax(const double tau = 0.1) : mTau(tau)  {}
  int SelectIndex(const std::vector<double>& chances) const override;
  const double mTau;
};

} //~namespace nabl
} //~namespace ribi


#endif // NARMEDBANDITLEARNERSELECTION_H
