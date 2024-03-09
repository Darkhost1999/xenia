#include "xenia/ui/qt/main_window.h"

#include <QMessageBox>
#include <QVBoxLayout>
#include <QAbstractButton>

#include "build/version.h"
#include "events/hid_event.h"
#include "helpers/focus_helper.h"
#include "xenia/base/logging.h"
#include "xenia/ui/qt/widgets/status_bar.h"

#include "xenia/hid/sdl/sdl_hid.h"
#if XE_PLATFORM_WIN32
#include "xenia/hid/xinput/xinput_hid.h"
#endif

DECLARE_string(hid);

namespace xe {
namespace ui {
namespace qt {
MainWindow::MainWindow(WindowedAppContext& app_context, std::string_view title,
                       uint32_t width, uint32_t height)
    : Themeable<QtWindow>("MainWindow", app_context, title, width, height),
      input_helper_(new HidHelper(this)) {
  if (!input_helper_->Initialize()) {
    XELOGW("Failed to initialize HID Helper object");
    input_helper_->deleteLater();
  }
}

bool MainWindow::OpenImpl() {
  // Custom Frame Border
  // Disable for now until windows aero additions are added
  // setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

  shell_ = new XShell(this);
  this->setCentralWidget(shell_);

  status_bar_ = new XStatusBar(this);
  this->setStatusBar(status_bar_);

  QLabel* build_label = new QLabel;
  build_label->setObjectName("buildLabel");
  build_label->setText(QStringLiteral("Xenia: %1 / %2 / %3")
                           .arg(XE_BUILD_BRANCH)
                           .arg(XE_BUILD_COMMIT_SHORT)
                           .arg(XE_BUILD_DATE));
  status_bar_->addPermanentWidget(build_label);

  ThemeManager& theme_manager = ThemeManager::Instance();
  connect(&theme_manager, &ThemeManager::OnActiveThemeChanged, this,
          &MainWindow::OnActiveThemeChanged);

  Theme* active_theme = theme_manager.current_theme();
  if (active_theme) {
    connect(active_theme, &Theme::ThemeReloaded, this,
            &MainWindow::OnThemeReloaded);
  }

  QtWindow::OpenImpl();
  return true;
}

void MainWindow::AddStatusBarWidget(QWidget* widget, bool permanent) {
  if (permanent) {
    status_bar_->addPermanentWidget(widget);
  } else {
    status_bar_->addWidget(widget);
  }
}

void MainWindow::RemoveStatusBarWidget(QWidget* widget) {
  return status_bar_->removeWidget(widget);
}

void MainWindow::OnActiveThemeChanged(Theme* theme) {
  assert_true(theme != nullptr);

  disconnect(hot_reload_signal_);
  connect(theme, &Theme::ThemeReloaded, this, &MainWindow::OnThemeReloaded);
}

void MainWindow::OnThemeReloaded() {
  status_bar_->showMessage(QStringLiteral("Theme Reloaded"), 3000);
}

bool MainWindow::event(QEvent* event) {
  if (event->type() == HidEvent::ButtonPressType) {
    auto button_event = static_cast<ButtonPressEvent*>(event);
    bool is_repeat = button_event->is_repeat();
    auto buttons = button_event->buttons();
    QWidget* focused = QApplication::focusWidget();

    // handle dpad
    if (buttons & (kInputDpadDown | kInputDpadUp) && !is_repeat) {
      // invoke focusNextPrevChild via our helper
      bool forward = !!(buttons & kInputDpadDown);
      if (forward) {
        FocusHelper::FocusNextInteractable(focused);
      } else {
        FocusHelper::FocusPrevInteractable(focused);
      }

      return true;
    }

    // handle A button
    if (buttons & kInputButtonA && !is_repeat) {
      if (auto button = qobject_cast<QAbstractButton*>(focused)) {
        button->click();
      }
    }
  }

  return Themeable<QtWindow>::event(event);
}

}  // namespace qt
}  // namespace ui
}  // namespace xe