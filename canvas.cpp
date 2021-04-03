#include "canvas.h"

#include <QPainter>
#include <QSizePolicy>

namespace qt_hy {
  Canvas::Canvas(QWidget* parent) : QWidget(parent) {
    setMinimumSize(250, 100);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  }

  void Canvas::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.drawRect(QRect(0, 0, width(), height()));
  }
} // namespace qt_hy
