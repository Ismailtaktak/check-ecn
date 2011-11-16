#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "itemdockwidget.h"
#include "centralwidget.h"
#include <QTextEdit>


namespace Ui {
    class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


public slots:
    void save();
    void load(int item);
    void setBold(bool bold);

private:
    Ui::MainWindow *ui;
    ItemDockWidget * mItemDockWidget;
    CentralWidget * mCentralWidget;

};

#endif // MAINWINDOW_H
