//---------------------------------------------------------------------------
/*
NarmedBanditLearner, an N-armed bandit and learner class demonstration
Copyright (C) 2006-2015  Richel Bilderbeek

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
// From http://www.richelbilderbeek.nl/ToolNarmedBanditLearner.htm
//---------------------------------------------------------------------------
#include "narmedbanditlearnermenudialog.h"

int main(int argc, char * argv[])
{
  const std::vector<std::string> args = { ribi::nabl::menu_dialog::ConvertArguments(argc,argv) };
  ribi::nabl::menu_dialog d;
  return d.Execute(args);
}
