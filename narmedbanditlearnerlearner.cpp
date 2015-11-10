#include "narmedbanditlearnerlearner.h"

#include <cassert>

#include "narmedbanditlearnerhelper.h"
#include "narmedbanditlearnerselection.h"

ribi::nabl::Learner::Learner(
  const std::vector<double>& initRewards,
  const double learningRate,
  const double epsilon
) : mRewards(initRewards),
    mSelection{},
    mLearningRate(learningRate),
    mEpsilon(epsilon),
    mLastAction{}
{

}
int ribi::nabl::Learner::SelectAction() const
{
  //Explore or exploit?
  if (GetRandomUniform() < mEpsilon)
  { //Select random action
    mLastAction = std::rand() % mRewards.size();
  }
  else
  {
    //Selects an action probabilistically
    //and stores this action
    assert(mSelection.get()!=0);
    mLastAction = mSelection->SelectIndex(mRewards);
  }
  return mLastAction;
}

void ribi::nabl::Learner::EvaluateAction(const double reward)
{
  //Assert mLastAction is a valid index
  assert(mLastAction >= 0 && mLastAction < static_cast<int>(mRewards.size()));
  //Change the expected reward
  mRewards[mLastAction] += (mLearningRate * (reward - mRewards[mLastAction]));
}


void ribi::nabl::Learner::SetSelection(std::unique_ptr<SelectionBase> selection)
{
  mSelection = std::move(selection);
}
