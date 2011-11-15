#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QProgressBar>
#include "ecnitemmodel.h"
#include "ecnitemdelegate.h"
#include "QSortFilterProxyModel"
#include <QPropertyAnimation>

namespace Ui {
    class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent * event);

public slots:
    void filterState(int state );
    void addScore(const QModelIndex& index);
    void showAbout();
    void updateStatus();
    void remiseAZero();

private:
    Ui::MainWindow *ui;
    EcnItemModel * mModel;
    QSortFilterProxyModel * mSortModel;
    QPropertyAnimation * mAnimation;
};

#endif // MAINWINDOW_H
