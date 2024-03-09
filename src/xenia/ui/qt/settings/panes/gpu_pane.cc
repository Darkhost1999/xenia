#include "gpu_pane.h"

namespace xe {
namespace ui {
namespace qt {

void GPUPane::Build() {
  QWidget* widget = new QWidget();
  widget->setStyleSheet("background: orange");

  SetContentWidget(widget);
}

}  // namespace qt
}  // namespace ui
}  // namespace xe