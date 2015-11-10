#include "narmedbanditlearnersimulation.h"

#include <cassert>
#include <iostream>
#include <iterator>

#include "narmedbanditlearnerhelper.h"
#include "narmedbanditlearnernarmedbandit.h"
#include "narmedbanditlearnerlearner.h"
#include "narmedbanditlearnerselection.h"

//From http://www.richelbilderbeek.nl/CppCoutContainer.htm
template <class Container>
void CoutContainer(const Container& c)
{
  std::copy(c.begin(),c.end(),std::ostream_iterator<typename Container::value_type>(std::cout,"\n"));
}

ribi::nabl::simulation::simulation()
{

}

void ribi::nabl::simulation::run()
{
  RandomizeTimer();

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
        learner.SetSelection(std::unique_ptr<SelectionBase>(new SelectionEqual));
        break;
      case 1: //Set the softmax selection
        std::cout << "The learner chooses an action by softmax selection" << std::endl;
        learner.SetSelection(std::unique_ptr<SelectionBase>(new SelectionSoftmax(0.1)));
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

}
