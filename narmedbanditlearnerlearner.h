#ifndef NARMEDBANDITLEARNERLEARNER_H
#define NARMEDBANDITLEARNERLEARNER_H

#include <memory>
#include <vector>

namespace ribi {
namespace nabl {

struct SelectionBase;

struct Learner
{
  Learner(
    const std::vector<double>& initRewards,
    const double learningRate = 0.01,
    const double epsilon = 0.01
  );
  int SelectAction() const;
  void EvaluateAction(const double reward);
  const std::vector<double>& GetRewards() const { return mRewards; }
  void SetSelection(std::unique_ptr<SelectionBase> selection);
  private:
  std::vector<double> mRewards;
  std::unique_ptr<SelectionBase> mSelection; //A State
  const double mLearningRate;
  const double mEpsilon;
  mutable int mLastAction;
};

} //~namespace nabl
} //~namespace ribi


#endif // NARMEDBANDITLEARNERLEARNER_H
