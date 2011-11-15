#include "ecnitemdelegate.h"
#include <QPushButton>
EcnItemDelegate::EcnItemDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

void EcnItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{


    return QItemDelegate::paint(painter,option,index);

}

QWidget * EcnItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    if ( index.column() == 2)
        return new QPushButton("salut",parent);

 //   return QItemDelegate::createEditor(parent,option,index);


}

void EcnItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{


}

void EcnItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    editor->setGeometry(option.rect);

}

void EcnItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{

}
