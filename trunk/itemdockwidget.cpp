#include "itemdockwidget.h"
#include "ui_itemdockwidget.h"
#include <QApplication>
ItemDockWidget::ItemDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::ItemDockWidget)
{

    ui->setupUi(this);

    mModel = new EcnItemModel;
    mSortModel = new QSortFilterProxyModel;
    mSortModel->setSourceModel(mModel);
    mSortModel->setFilterKeyColumn(1);
    mSortModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    connect(ui->lineEdit,SIGNAL(textChanged(QString)),mSortModel,SLOT(setFilterRegExp(QString)));
    connect(ui->comboBox,SIGNAL(activated(int)),this,SLOT(filterState(int)));

    connect(ui->tableView,SIGNAL(clicked(QModelIndex)),this,SLOT(activated(QModelIndex)));

    //    connect(ui->actionAbout_Qt,SIGNAL(triggered()),qApp,SLOT(aboutQt()));
    //    connect(ui->actionAbout_checkECN,SIGNAL(triggered()),this,SLOT(showAbout()));
    //    connect(ui->tableView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(addScore(QModelIndex)));
    //    connect(ui->actionRemise_zero,SIGNAL(triggered()),this,SLOT(remiseAZero()));

    ui->tableView->setModel(mSortModel);
    ui->tableView->hideColumn(2);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->sortByColumn(0,Qt::AscendingOrder);
    ui->tableView->setColumnWidth(0,50);
    ui->comboBox->setCurrentIndex(3);


    updateStatus();
}

ItemDockWidget::~ItemDockWidget()
{
    delete ui;
}


void ItemDockWidget::filterState(int state)
{

    if ( state == 3)
    {
        mSortModel->setFilterKeyColumn(1);
        mSortModel->setFilterRegExp(ui->lineEdit->text());
        ui->lineEdit->setEnabled(true);
        return;

    }
    ui->lineEdit->setEnabled(false);
    mSortModel->setFilterKeyColumn(2);
    mSortModel->setFilterRegExp(QString::number(state));

}

void ItemDockWidget::addScore(const QModelIndex &index)
{

    QModelIndex realIndex = mSortModel->mapToSource(index);
    int score = mModel->score(realIndex);

    if ( score >=2)
        return;
    mModel->setScore(realIndex,score + 1 );
    updateStatus();



}

void ItemDockWidget::keyPressEvent(QKeyEvent *event)
{

    if ( event->key() == Qt::Key_Delete)
    {
        QModelIndex realIndex = mSortModel->mapToSource(ui->tableView->currentIndex());
        //        int score = mModel->score(realIndex);
        //        if ( score <=0)
        //            return;

        mModel->setScore(realIndex,0 );
        updateStatus();

    }
    if ( event->key() == Qt::Key_Return)
    {
        addScore(ui->tableView->currentIndex());

    }

}

void ItemDockWidget::showAbout()
{/*

    QMessageBox::about(this,qApp->applicationName()+" "+qApp->applicationVersion()
                       , "www.omed-soft.com\nsacha schutz\nistdasklar@gmail.com\nGPL3");*/
}

void ItemDockWidget::updateStatus()
{

    //    QString total = QString::number(mModel->rowCount());
    //    QString empty = QString::number(mModel->emptyCount());
    //    QString flag = QString::number(mModel->flagCount());
    //    QString valid = QString::number(mModel->validCount());

    //    statusBar()->showMessage("non fait: "+empty+"   "
    //                             "en cours: "+flag+"   "
    //                             "fait: "+valid+"   "
    //                             );


    //    ui->progressBar->setValue(mModel->progression() * 100);




}

void ItemDockWidget::remiseAZero()
{

    //    int ret = QMessageBox::warning(this, qApp->applicationName(),
    //                                   "Etes vous sûr de vouloir supprimer toutes votre progression?",
    //                                   QMessageBox::Yes | QMessageBox::No);

    //    if ( ret == QMessageBox::Yes)
    //    {


    //        mModel->clearProgress();
    //        updateStatus();


    //    }



}

int ItemDockWidget::currentItem()
{

    if ( ui->tableView->selectionModel()->hasSelection())
    {

        QModelIndex index =  ui->tableView->selectionModel()->selectedRows().first();
        return index.data().toInt();

    }

    return 0;


}

void ItemDockWidget::activated(const QModelIndex &index)
{

    if (!currentItem())
        return;

    emit itemActivated(currentItem());
}
