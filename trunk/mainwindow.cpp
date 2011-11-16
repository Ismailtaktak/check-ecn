#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    mItemDockWidget = new ItemDockWidget(this);
    mCentralWidget = new CentralWidget(this);

    addDockWidget(Qt::LeftDockWidgetArea, mItemDockWidget);
    setCentralWidget(mCentralWidget);


    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(save()));
    connect(mItemDockWidget,SIGNAL(itemActivated(int)),this,SLOT(load(int)));
    connect(mCentralWidget,SIGNAL(savable(bool)),ui->actionSave,SLOT(setEnabled(bool)));
    connect(ui->actionBold,SIGNAL(toggled(bool)),this,SLOT(setBold(bool)));

    showMaximized();


    mCentralWidget->setEnabled(false);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::save()
{
    int item = mItemDockWidget->currentItem();
    mCentralWidget->setEnabled(false);
    mCentralWidget->saveItem(item);
    mCentralWidget->setEnabled(true);

}

void MainWindow::load(int item)
{

    mCentralWidget->loadItem(item);
    mCentralWidget->setEnabled(true);

}

void MainWindow::setBold(bool bold)
{

    mCentralWidget->textEditA()->setFontUnderline(bold);
    mCentralWidget->textEditB()->setFontUnderline(bold);

}
