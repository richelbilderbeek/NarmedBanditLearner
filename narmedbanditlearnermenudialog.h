#ifndef NARMEDBANDITLEARNERMENUDIALOG_H
#define NARMEDBANDITLEARNERMENUDIALOG_H

#include "menudialog.h"

namespace ribi {
namespace nabl {

///GUI independent GrayCoder menu dialog
struct menu_dialog final : public MenuDialog
{
  explicit menu_dialog() noexcept;

  private:
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept override;
  About GetAbout() const noexcept override;
  Help GetHelp() const noexcept override;
  std::string GetVersion() const noexcept override;
  std::vector<std::string> GetVersionHistory() const noexcept override;

  #ifndef NDEBUG
  static void test() noexcept;
  #endif

};

} //~namespace nabl
} //~namespace ribi

#endif // NARMEDBANDITLEARNERMENUDIALOG_H
