#pragma once

#include <QWidget>

namespace qt_hy {
  class TreeModelHierarchy;

  class Canvas : public QWidget {
    Q_OBJECT
  public:
    explicit Canvas(QWidget* parent = nullptr);
    ~Canvas() = default;

  TreeModelHierarchy* treeModel_ = nullptr;

  private:
    void paintEvent(QPaintEvent* event) override;
  };
} // namespace qt_hy
