#include "canvas.h"
#include "hierarchy/entity.hpp"
#include "tree-model.h"

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

    const auto display = [treeModel = treeModel_,
                          &painter](const hy::display_info_t& di) {
      const auto entry = std::string("|-- ") + di.name;
      const QColor col = di.selected   ? QColor(0xffffff00)
                       : !di.collapsed ? QColor(0xffffffff)
                                       : QColor(0xff00ffff);
      painter.setPen(col);
      painter.drawText(2 + di.indent * 20, 14 + di.level * 14, entry.c_str());
    };

    const auto display_connection = [&painter](int level, int indent) {
      painter.setPen(QColor(0xffffffff));
      painter.drawText(2 + indent * 20, 14 + level * 14, "|");
    };

    hy::display_hierarchy(
      treeModel_->entities_, treeModel_->interaction_,
      treeModel_->root_handles_, display, []() {}, display_connection);
  }
} // namespace qt_hy
