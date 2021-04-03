#include "tree-model.h"

#include <QApplication>
#include <QTreeView>

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  qt_hy::TreeModelHierarchy model;

  QTreeView view;
  view.setModel(&model);
  view.setWindowTitle(QObject::tr("Hierarchy"));
  view.show();

  return app.exec();
}
