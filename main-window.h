#pragma once

#include <QMainWindow>

namespace qt_hy {
  class MainWindow : public QMainWindow {
    Q_OBJECT
  public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() = default;
  private:
  };
} // namespace qt_hy
