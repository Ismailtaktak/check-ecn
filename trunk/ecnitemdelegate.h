#ifndef ECNITEMDELEGATE_H
#define ECNITEMDELEGATE_H

#include <QItemDelegate>
#include <QPainter>
class EcnItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit EcnItemDelegate(QObject *parent = 0);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

signals:

public slots:

};

#endif // ECNITEMDELEGATE_H
