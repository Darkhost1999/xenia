#include "settings_pane.h"

namespace xe {
namespace ui {
namespace qt {

void SettingsPane::SetContentWidget(QWidget* widget) {
  if (widget) {
    widget_ = widget;
    setFocusProxy(widget_);
  }
}

}
}
}
