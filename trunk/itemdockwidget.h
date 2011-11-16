#ifndef ITEMDOCKWIDGET_H
#define ITEMDOCKWIDGET_H

#include <QDockWidget>
#include <QKeyEvent>
#include <QProgressBar>
#include "ecnitemmodel.h"
#include "ecnitemdelegate.h"
#include "QSortFilterProxyModel"
#include <QPropertyAnimation>


namespace Ui {
    class ItemDockWidget;
}

class ItemDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit ItemDockWidget(QWidget *parent = 0);
    ~ItemDockWidget();

    void keyPressEvent(QKeyEvent * event);
    int currentItem();

public slots:
    void filterState(int state );
    void addScore(const QModelIndex& index);
    void showAbout();
    void updateStatus();
    void remiseAZero();
protected slots:
    void activated(const QModelIndex& index);

signals:
    void itemActivated(int item);


private:
    Ui::ItemDockWidget *ui;
    EcnItemModel * mModel;
    QSortFilterProxyModel * mSortModel;
    QPropertyAnimation * mAnimation;


};

#endif // ITEMDOCKWIDGET_H
