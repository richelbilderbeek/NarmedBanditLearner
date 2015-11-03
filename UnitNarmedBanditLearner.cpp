//---------------------------------------------------------------------------
/*
  NarmedBanditLearner, an N-armed bandit and learner class demonstration
  Copyright (C) 2006  Richel Bilderbeek

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl
//---------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <cmath>
#include <ctime>
#include <memory>
#include <ctime>
#include <iterator>
//---------------------------------------------------------------------------
void ShowAbout()
{
  std::cout
    << "N-armed-bandit learner V1.1                                                    " << std::endl
    << "Programmed by Richel Bilderbeek                                                " << std::endl
    << "at the 23rd of September 2006 (V1.0)                                           " << std::endl
    << "and at the 16rd of July 2008 (V1.1)                                            " << std::endl
    << "From http://www.richelbilderbeek.nl                                            " << std::endl
    << "                                                                               " << std::endl
    << "This program generates an N-armed bandit class (in this case of 6 arms)        " << std::endl
    << "of which each arm has a certain chance to yield a reward (from 10% to 90%)     " << std::endl
    << "A learner class then tries to find out the most rewarding arm.                 " << std::endl
    << "This is done by action-reward epsilon-learning                                 " << std::endl
    << "  * epsilon-learning: by a certain chance, epsilon, explore                    " << std::endl
    << "                      by a chance of 1-epsilon, choose the 'best' arm          " << std::endl
    << "  * action-reward: every action has a certain expected reward, which gradually " << std::endl
    << "                   reaches the actual reward.                                  " << std::endl
    << "The learner has two ways of action selection, which are explained by this      " << std::endl
    << "  example: imagine two actions, action A with expected reward 0.1 and          " << std::endl
    << "  action B with expected reward 0.9.                                           " << std::endl
    << "  * Equal selection: the chance action A is taken is 10%                       " << std::endl
    << "  * Softmax selection: the chance action A is taken is less:                   " << std::endl
    << "                        std::exp( 0.1 / tau)                                   " << std::endl
    << "      p(A) = ---------------------------------------------                     " << std::endl
    << "              std::exp( 0.1 / tau) + std::exp( 0.9 / tau)                      " << std::endl
    << "                                                                               " << std::endl
    << "    For tau = 0.1 (as in this program), p(A) equals 0.0034 %                   " << std::endl
    << "                                                                               " << std::endl
    << std::endl;
}
//---------------------------------------------------------------------------
void ShowLicence()
{
  std::cout
    << "NarmedBanditLearner, an N-armed bandit and learner class demonstration" << std::endl
    << "Copyright (C) 2006  Richel Bilderbeek                                 " << std::endl
    << "                                                                      " << std::endl
    << "This program is free software: you can redistribute it and/or modify  " << std::endl
    << "it under the terms of the GNU General Public License as published by  " << std::endl
    << "the Free Software Foundation, either version 3 of the License, or     " << std::endl
    << "(at your option) any later version.                                   " << std::endl
    << "                                                                      " << std::endl
    << "This program is distributed in the hope that it will be useful,       " << std::endl
    << "but WITHOUT ANY WARRANTY; without even the implied warranty of        " << std::endl
    << "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         " << std::endl
    << "GNU General Public License for more details.                          " << std::endl
    << "You should have received a copy of the GNU General Public License     " << std::endl
    << "along with this program.  If not, see <http://www.gnu.org/licenses/>. " << std::endl
    << std::endl;
}
//---------------------------------------------------------------------------
//From htpp://www.richelbilderbeek.nl/CppGetRandomUniform.htm
const double GetRandomUniform()
{
  return static_cast<double>(std::rand())/static_cast<double>(RAND_MAX);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppCoutContainer.htm
template <class Container>
void CoutContainer(const Container& c)
{
  std::copy(c.begin(),c.end(),std::ostream_iterator<Container::value_type>(std::cout,"\n"));
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppRandomizeTimer.htm
void RandomizeTimer()
{
  std::srand(std::time(0));
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppAskUserForString.htm
const std::string AskUserForString()
{
  std::string s;
  std::getline(std::cin,s);
  return s;
}
//---------------------------------------------------------------------------
struct GibbsFunctor : public std::binary_function<double, double, double>
{
  GibbsFunctor(const double& tau) : mTau(tau) {}
  const double operator() (const double sum, const double x) const
  {
    return sum + Gibbs(x);
  }
  const double mTau;
  double Gibbs(const double x) const { return std::exp( x / mTau );  }
  static double Gibbs(const double x, const double tau) { return std::exp( x / tau );  }
};
//---------------------------------------------------------------------------
//Default chances for the N-armed bandit
const std::vector<double> GetDefaultChances()
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
//---------------------------------------------------------------------------
//A State
struct SelectionBase
{
  virtual const int SelectIndex(const std::vector<double>& chances) const = 0;
  virtual ~SelectionBase() {} //Every base class must have virtual destructor
};
//---------------------------------------------------------------------------
const int SelectIndexSoftmax(const std::vector<double>& chances, const double tau)
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
//---------------------------------------------------------------------------
struct SelectionEqual : public SelectionBase
{
  const int SelectIndex(const std::vector<double>& chances) const
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
};
//---------------------------------------------------------------------------
struct SelectionSoftmax : public SelectionBase
{
  SelectionSoftmax(const double tau = 0.1) : mTau(tau)  {}
  const int SelectIndex(const std::vector<double>& chances) const
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
  const double mTau;
};
//---------------------------------------------------------------------------
struct Learner
{
  Learner(
    const std::vector<double>& initRewards,
    const double learningRate = 0.01,
    const double epsilon = 0.01)
    : mRewards(initRewards),
      mLearningRate(learningRate),
      mEpsilon(epsilon)
  {

  }
  const int SelectAction() const
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

  void EvaluateAction(const double reward)
  {
    //Assert mLastAction is a valid index
    assert(mLastAction >= 0 && mLastAction < static_cast<int>(mRewards.size()));
    //Change the expected reward
    mRewards[mLastAction] += (mLearningRate * (reward - mRewards[mLastAction]));
  }

  const std::vector<double>& GetRewards() const { return  mRewards; }

  void SetSelection(std::auto_ptr<SelectionBase> selection)
  {
    mSelection = selection;
  }
  private:
  std::vector<double> mRewards;
  std::auto_ptr<SelectionBase> mSelection; //A State
  const double mLearningRate;
  const double mEpsilon;
  mutable int mLastAction;
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
struct NarmedBandit
{
  NarmedBandit(const std::vector<double>& chances)
  : mChances(chances)
  {

  }
  const bool PlayAction(const int action) const
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
  const std::vector<double> mChances;

};
//---------------------------------------------------------------------------

int main()
{
  RandomizeTimer();

  ShowLicence();
  std::cout << "Press any key to start" << std::endl;
  AskUserForString();
  ShowAbout();
  std::cout << "Press any key to continue" << std::endl;
  AskUserForString();

  //Create a bandit with 6 arms
  NarmedBandit bandit(GetDefaultChances());
  //Create a learner with 6 actions (all with expected reward 0.0)
  Learner learner(std::vector<double>(6,0.0));
  //Assume that the bandit has as many arms as the learner has actions
  assert(bandit.mChances.size() == learner.GetRewards().size());
  { //Set the selection, chosen at random
    const int distributionIndex = (std::rand() >> 4) % 2; //Lower bits have lower randomness
    switch (distributionIndex)
    {
      case 0: //Set the equal selection
        std::cout << "The learner chooses an action by normal selection" << std::endl;
        learner.SetSelection(std::auto_ptr<SelectionBase>(new SelectionEqual));
        break;
      case 1: //Set the softmax selection
        std::cout << "The learner chooses an action by softmax selection" << std::endl;
        learner.SetSelection(std::auto_ptr<SelectionBase>(new SelectionSoftmax(0.1)));
        break;
      default: assert(!"Should not get here");
    }
  }
  //Keep track of the total rewards gathered by the learner
  double sumReward = 0.0;

  //Let the learner take many actions
  for (int i=0; i<10000; ++i)
  {

    { //Optional output
      //#define I_WANT_TO_SEE_ALL
      #ifdef I_WANT_TO_SEE_ALL
      //Show start of action
      std::cout << std::endl << "Starting action " << i << std::endl;
      //Show the expected rewards of the learner
      CoutContainer(learner.GetRewards());
      #endif
    }
    //Let the learner select an action
    const int action = learner.SelectAction();
    const bool wasSuccess = bandit.PlayAction(action);
    const double reward = (wasSuccess ? 1.0 : 0.0);
    learner.EvaluateAction(reward);
    //Track the total rewards gained by the learner
    sumReward+=reward;
  }

  //Show the expected rewards of the learner
  std::cout << std::endl << "Final expected rewards of the learner: " << std::endl;
  CoutContainer(learner.GetRewards());
  //Show the bandit's chances
  std::cout << std::endl << "Winchances of the bandit: " << std::endl;
  CoutContainer(bandit.mChances);
  //Show the total reward gained
  std::cout << std::endl << "The learner gained " << sumReward << " reward in total." <<std::endl;

  std::cout << "Program done" << std::endl;
  std::cout << "Press any key to quit" << std::endl;
  AskUserForString();
  ShowLicence();
}
//---------------------------------------------------------------------------

