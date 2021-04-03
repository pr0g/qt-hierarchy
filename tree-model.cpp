#include "tree-model.h"

namespace qt_hy {
  TreeModelHierarchy::TreeModelHierarchy(QObject* parent)
    : QAbstractItemModel(parent) {
    root_handles_ = demo::create_sample_entities(entities_);
    interaction_.selected_ = root_handles_.front();
    interaction_.neighbors_ = root_handles_;
  }

  QVariant TreeModelHierarchy::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) {
      return QVariant();
    }

    if (role != Qt::DisplayRole) {
      return QVariant();
    }

    auto id = index.internalId();
    thh::handle_t handle;
    memcpy(&handle, &id, sizeof(id));

    QString name;
    entities_.call(handle, [&name](const hy::entity_t& entity) {
      name = QString(entity.name_.c_str());
    });

    return name;
  }

  Qt::ItemFlags TreeModelHierarchy::flags(const QModelIndex& index) const {
    if (!index.isValid()) {
      return Qt::NoItemFlags;
    }

    return QAbstractItemModel::flags(index);
  }

  QVariant TreeModelHierarchy::headerData(
    int section, Qt::Orientation orientation, int role) const {
    if (section == 0 && role == Qt::DisplayRole) {
      return QString("Entities");
    }
    return QVariant();
  }

  QModelIndex TreeModelHierarchy::index(
    int row, int column, const QModelIndex& parent) const {
    if (!hasIndex(row, column, parent)) {
      return QModelIndex();
    }

    std::vector<thh::handle_t> handles;
    if (!parent.isValid()) {
      handles = root_handles_;
    } else {
      auto id = parent.internalId();
      thh::handle_t parent_handle;
      memcpy(&parent_handle, &id, sizeof(id));
      entities_.call(
        parent_handle, [&handles](const hy::entity_t& parent_entity) {
          handles = parent_entity.children_;
        });
    }

    if (row < handles.size()) {
      const thh::handle_t handle = handles[row];
      quintptr id;
      memcpy(&id, &handle, sizeof(handle));
      return createIndex(row, column, id);
    }

    return QModelIndex();
  }

  QModelIndex TreeModelHierarchy::parent(const QModelIndex& index) const {
    if (!index.isValid()) {
      return QModelIndex();
    }
    auto id = index.internalId();
    thh::handle_t child_handle;
    memcpy(&child_handle, &id, sizeof(id));

    thh::handle_t parent;
    entities_.call(child_handle, [&parent](const hy::entity_t& entity) {
      parent = entity.parent_;
    });

    if (parent == thh::handle_t(-1, -1)) {
      return QModelIndex();
    }

    int offset = 0;
    entities_.call(parent, [&offset, child_handle](const hy::entity_t& entity) {
      offset = std::find(
                 entity.children_.begin(), entity.children_.end(), child_handle)
             - entity.children_.begin();
    });

    quintptr pid;
    memcpy(&pid, &parent, sizeof(parent));
    return createIndex(offset, 0, pid);
  }

  int TreeModelHierarchy::rowCount(const QModelIndex& parent) const {
    if (parent.column() > 0) {
      return 0;
    }
    std::vector<thh::handle_t> handles;
    if (parent.isValid()) {
      auto id = parent.internalId();
      thh::handle_t parent_handle;
      memcpy(&parent_handle, &id, sizeof(id));
      entities_.call(
        parent_handle, [&handles](const hy::entity_t& parent_entity) {
          handles = parent_entity.children_;
        });
    } else {
      handles = root_handles_;
    }
    return handles.size();
  }

  int TreeModelHierarchy::columnCount(const QModelIndex& parent) const {
    return 1;
  }
} // namespace qt_hy
