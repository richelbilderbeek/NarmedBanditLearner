#include "narmedbanditlearnermenudialog.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <cassert>
#include <iostream>

#include <boost/lexical_cast.hpp>

#include "testtimer.h"
#include "narmedbanditlearnersimulation.h"
#include "trace.h"
#pragma GCC diagnostic pop

ribi::nabl::menu_dialog::menu_dialog() noexcept
{
  #ifndef NDEBUG
  test();
  #endif
}

int ribi::nabl::menu_dialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 2)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }

  std::cout
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

  simulation s;
  s.run();
  return 0;
}

ribi::About ribi::nabl::menu_dialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "N-armed-bandit learner",
    "an N-armed bandit and learner class demonstration",
    "the 10th of November 2015",
    "2006-2015",
    "http://www.richelbilderbeek.nl/ToolNarmedBanditLearner.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("TestTimer version: " + TestTimer::GetVersion());
  a.AddLibrary("Trace version: " + Trace::GetVersion());
  return a;
}

ribi::Help ribi::nabl::menu_dialog::GetHelp() const noexcept
{
  return ribi::Help(
    this->GetAbout().GetFileTitle(),
    this->GetAbout().GetFileDescription(),
    {
    },
    {
    }
  );
}

std::string ribi::nabl::menu_dialog::GetVersion() const noexcept
{
  return "1.2";
}

std::vector<std::string> ribi::nabl::menu_dialog::GetVersionHistory() const noexcept
{
  return {
    "2006-09-23: version 1.0",
    "2008-07-16: version 1.1",
    "2015-11-10: version 1.2: added menu, put classes in own units",
  };
}

#ifndef NDEBUG
void ribi::nabl::menu_dialog::test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
}
#endif
