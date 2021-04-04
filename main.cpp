#include "tree-model.h"
#include "main-window.h"
#include "canvas.h"

#include <QApplication>
#include <QTreeView>
#include <QHBoxLayout>

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  qt_hy::TreeModelHierarchy model;

  auto* view = new QTreeView();
  view->setModel(&model);

  auto* canvas = new qt_hy::Canvas();
  canvas->treeModel_ = &model;

  auto* layout = new QHBoxLayout();
  layout->addWidget(view);
  layout->addWidget(canvas);

  qt_hy::MainWindow window;
  window.setCentralWidget(new QWidget);
  window.centralWidget()->setLayout(layout);
  window.setWindowTitle(QObject::tr("Hierarchy"));
  window.show();

  return app.exec();
}
