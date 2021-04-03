#pragma once

#include <QWidget>

namespace qt_hy {
  class Canvas : public QWidget {
    Q_OBJECT
  public:
    explicit Canvas(QWidget* parent = nullptr);
    ~Canvas() = default;

  protected:
    void paintEvent(QPaintEvent* event) override;
  };
} // namespace qt_hy
