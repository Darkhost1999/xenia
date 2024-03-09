#ifndef XENIA_UI_QT_SIDEBAR_H_
#define XENIA_UI_QT_SIDEBAR_H_

#include <QToolBar>
#include "xenia/ui/qt/themeable_widget.h"
#include "xenia/ui/qt/widgets/sidebar_button.h"

namespace xe {
namespace ui {
namespace qt {

class XSideBar : public Themeable<QToolBar> {
 public:
  explicit XSideBar();

  /**
   * Adds a new action (button) to this sidebar.
   * @param text title to give this action.
   * @return a pointer to the created button.
   */
  XSideBarButton* addAction(const QString& text);
  /**
   * Adds a new action (button) to this sidebar.
   * @param glyph a glyph code to assign a glyph icon to the created button.
   * @param text title to give this action.
   * @return a pointer to the created button.
   */
  XSideBarButton* addAction(QChar glyph, const QString& text);

  /**
   * Add a spacer to this sidebar. A spacer is just an empty QWidget.
   * @param size size of the spacer.
   * @return a pointer to the created spacer.
   */
  QWidget* addSpacing(int size);

  /**
   * @return the button group containing all buttons in this sidebar.
   */
  QButtonGroup* buttonGroup() const { return buttons_; }

  /**
   * Gets the currently selected sidebar button.
   * @return the index of currently selected button, or -1 if none selected.
   */
  int currentSelection() const;

 protected:
  void focusInEvent(QFocusEvent* event) override;
  bool event(QEvent* event) override;

 private:
  QButtonGroup* buttons_;
  int index_tracker_ = 0;
};

}  // namespace qt
}  // namespace ui
}  // namespace xe

#endif
