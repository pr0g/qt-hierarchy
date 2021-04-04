#include "canvas.h"
#include "main-window.h"
#include "tree-model.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QTreeView>

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  qt_hy::TreeModelHierarchy model;

  auto* view = new QTreeView();
  view->setModel(&model);
  view->expandAll(); // start expanded

  QObject::connect(
    view, &QTreeView::collapsed, &model, &qt_hy::TreeModelHierarchy::collapsed);
  QObject::connect(
    view, &QTreeView::expanded, &model, &qt_hy::TreeModelHierarchy::expanded);

  auto* canvas = new qt_hy::Canvas();
  canvas->treeModel_ = &model;

  auto* layout = new QHBoxLayout();
  layout->addWidget(view);
  layout->addWidget(canvas);

  QObject::connect(
    view, &QTreeView::collapsed, canvas, QOverload<>::of(&qt_hy::Canvas::update));
  QObject::connect(
    view, &QTreeView::expanded, canvas, QOverload<>::of(&qt_hy::Canvas::update));

  qt_hy::MainWindow window;
  window.setCentralWidget(new QWidget);
  window.centralWidget()->setLayout(layout);
  window.setWindowTitle(QObject::tr("Hierarchy"));
  window.show();

  return app.exec();
}
