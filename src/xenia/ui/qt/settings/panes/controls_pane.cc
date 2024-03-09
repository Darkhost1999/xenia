#include "controls_pane.h"

namespace xe {
namespace ui {
namespace qt {

void ControlsPane::Build() {
  QWidget* widget = new QWidget();
  widget->setStyleSheet("background: yellow");

  SetContentWidget(widget);
}

}  // namespace qt
}  // namespace ui
}  // namespace xe