/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2024 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include "focus_helper.h"
#include <QWidget>

namespace xe {
namespace ui {
namespace qt {

// method to access protected properties and methods on QWidget*
// https://stackoverflow.com/a/52318892
// we are using to access focusNextPrevChild(). This is because
// the public method nextInFocusChain() was returning widgets that weren't
// interactable, but focusNextPrevChild() behaved exactly as you'd expect for
// controller input.
using Method = bool (QWidget::*)(bool);
struct Helper : QWidget {
  static Method get_focusNextPrevChild() { return &Helper::focusNextPrevChild; }
};
static Method const focusNextPrevChildProxy = Helper::get_focusNextPrevChild();

bool FocusHelper::FocusNextInteractable(QWidget* target_widget) {
  if (target_widget) {
    return std::invoke(focusNextPrevChildProxy, target_widget, true);
  }
  return false;
}

bool FocusHelper::FocusPrevInteractable(QWidget* target_widget) {
  if (target_widget) {
    return std::invoke(focusNextPrevChildProxy, target_widget, false);
  }
  return false;
}

}  // namespace qt
}  // namespace ui
}  // namespace xe