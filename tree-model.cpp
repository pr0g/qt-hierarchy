#include "tree-model.h"

namespace qt_hy {
  static thh::handle_t handle_from_id(const quintptr id) {
    thh::handle_t handle;
    memcpy(&handle, &id, sizeof(id));
    return handle;
  }

  static quintptr id_from_handle(const thh::handle_t handle) {
    quintptr id;
    memcpy(&id, &handle, sizeof(handle));
    return id;
  }

  TreeModelHierarchy::TreeModelHierarchy(QObject* parent)
    : QAbstractItemModel(parent) {
    root_handles_ = demo::create_sample_entities(entities_);
    interaction_.neighbors_ = root_handles_;
  }

  QVariant TreeModelHierarchy::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) {
      return QVariant();
    }

    if (role != Qt::DisplayRole) {
      return QVariant();
    }

    QString name;
    entities_.call(
      handle_from_id(index.internalId()), [&name](const hy::entity_t& entity) {
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
      entities_.call(
        handle_from_id(parent.internalId()),
        [&handles](const hy::entity_t& parent_entity) {
          handles = parent_entity.children_;
        });
    }

    if (row < handles.size()) {
      return createIndex(row, column, id_from_handle(handles[row]));
    }

    return QModelIndex();
  }

  QModelIndex TreeModelHierarchy::parent(const QModelIndex& index) const {
    if (!index.isValid()) {
      return QModelIndex();
    }

    const auto child_handle = handle_from_id(index.internalId());
    thh::handle_t parent_handle;
    entities_.call(child_handle, [&parent_handle](const hy::entity_t& entity) {
      parent_handle = entity.parent_;
    });

    if (parent_handle == thh::handle_t(-1, -1)) {
      return QModelIndex();
    }

    int offset = 0;
    entities_.call(
      parent_handle, [&offset, child_handle](const hy::entity_t& entity) {
        offset =
          std::find(
            entity.children_.begin(), entity.children_.end(), child_handle)
          - entity.children_.begin();
      });

    return createIndex(offset, 0, id_from_handle(parent_handle));
  }

  int TreeModelHierarchy::rowCount(const QModelIndex& parent) const {
    if (parent.column() > 0) {
      return 0;
    }
    std::vector<thh::handle_t> handles;
    if (parent.isValid()) {
      entities_.call(
        handle_from_id(parent.internalId()),
        [&handles](const hy::entity_t& parent_entity) {
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

  void TreeModelHierarchy::collapsed(const QModelIndex& index) {
    if (!index.isValid()) {
      return;
    }

    interaction_.collapsed_.push_back(handle_from_id(index.internalId()));
  }

  void TreeModelHierarchy::expanded(const QModelIndex& index) {
    if (!index.isValid()) {
      return;
    }

    interaction_.collapsed_.erase(
      std::remove(
        interaction_.collapsed_.begin(), interaction_.collapsed_.end(),
        handle_from_id(index.internalId())),
      interaction_.collapsed_.end());
  }

  void TreeModelHierarchy::selected(
    const QModelIndex& current, const QModelIndex& previous) {
    if (!current.isValid() || !previous.isValid()) {
      return;
    }

    interaction_.selected_ = handle_from_id(current.internalId());
  }
} // namespace qt_hy
