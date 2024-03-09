#include "cpu_pane.h"

namespace xe {
namespace ui {
namespace qt {

void CPUPane::Build() {
  QWidget* widget = new QWidget();
  widget->setStyleSheet("background: gray");

  SetContentWidget(widget);
}

}  // namespace qt
}  // namespace ui
}  // namespace xe