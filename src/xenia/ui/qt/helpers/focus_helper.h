/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2024 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef XENIA_UI_QT_FOCUSHELPER_H_
#define XENIA_UI_QT_FOCUSHELPER_H_

class QWidget;

namespace xe {
namespace ui {
namespace qt {

/**
 * Helper functions that can focus the next interactable widget in the UI
 * hierarchy from a given target widget.
 *
 * Indirectly calls QWidget::focusNextPrevChild()
 */
class FocusHelper {
 public:
  /**
   * Focuses the next interactable widget in the widget hierarchy from a given
   * target widget.
   * @param target_widget target to find focusable widget for.
   * @return whether a widget could be focused
   */
  static bool FocusNextInteractable(QWidget* target_widget);

  /**
   * Focuses the previous interactable widget in the widget hierarchy from a
   * given target widget.
   * @param target_widget target to find focusable widget for.
   * @return whether a widget could be focused
   */
  static bool FocusPrevInteractable(QWidget* target_widget);
};

}  // namespace qt
}  // namespace ui
}  // namespace xe

#endif  // XENIA_UI_QT_FOCUSHELPER_H_