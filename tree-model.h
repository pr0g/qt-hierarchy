#include "hierarchy/entity.hpp"

#include <QAbstractItemModel>
#include <QModelIndex>

class TreeModelHierarchy : public QAbstractItemModel
{
public:
  explicit TreeModelHierarchy(QObject *parent = nullptr);
  ~TreeModelHierarchy() = default;

  QVariant data(const QModelIndex &index, int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  QModelIndex index(int row, int column,
                    const QModelIndex &parent = QModelIndex()) const override;
  QModelIndex parent(const QModelIndex &index) const override;
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
  thh::container_t<hy::entity_t> entities_;
  std::vector<thh::handle_t> root_handles_;
  hy::interaction_t interaction_;
};