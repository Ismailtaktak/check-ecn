#include "centralwidget.h"
#include "ui_centralwidget.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDebug>
CentralWidget::CentralWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CentralWidget)
{
    ui->setupUi(this);

    ui->splitter->setStretchFactor(1,100);

    QPalette p=ui->textEditA->palette();
    p.setColor(QPalette::Active,QPalette::Base,QColor(247,220,195));
    ui->textEditA->setPalette(p);

    ui->textEditA->setFontPointSize(20);

    QDir dir;
    dir.mkdir("fiches");

    connect(ui->editButton,SIGNAL(toggled(bool)),this,SLOT(setEditable(bool)));
    connect(ui->textEditA,SIGNAL(textChanged()),this,SLOT(setSavable()));
    connect(ui->textEditB,SIGNAL(textChanged()),this,SLOT(setSavable()));



}

CentralWidget::~CentralWidget()
{
    delete ui;
}

QTextEdit * CentralWidget::textEditA()
{
    return ui->textEditA;
}

QTextEdit * CentralWidget::textEditB()
{
    return ui->textEditB;
}

void CentralWidget::clear()
{
    ui->textEditA->clear();
    ui->textEditB->clear();
}

void CentralWidget::loadItem(int item)
{

    QString fileNameA = "item_"+QString::number(item)+".html";
    QString fileNameB = "item_full_"+QString::number(item)+".html";

    clear();


    QStringList files;
    files<<fileNameA<<fileNameB;

    foreach ( QString fileName, files)
    {

        qDebug()<<"load "<<fileName;
        QFile file("fiches/"+fileName);
        if ( file.open( QIODevice::ReadOnly | QIODevice::Text ) )
        {
            QTextStream stream( &file );
            if ( fileName == fileNameA)
                ui->textEditA->setHtml(stream.readAll());

            if ( fileName == fileNameB)
                ui->textEditB->setHtml(stream.readAll());

            file.close();
        }

    }

    emit savable(false);
}

void CentralWidget::saveItem(int item)
{
    QString fileNameA = "item_"+QString::number(item)+".html";
    QString fileNameB = "item_full_"+QString::number(item)+".html";

    QStringList files;
    files<<fileNameA<<fileNameB;

    foreach ( QString fileName, files)
    {
        QFile file("fiches/"+fileName);
        qDebug()<<"save "<<fileName;
        if ( file.open( QIODevice::WriteOnly | QIODevice::Text ) )
        {
            QTextStream stream( &file );
            if ( fileName == fileNameA)
                stream<<ui->textEditA->toHtml();

            if ( fileName == fileNameB)
                stream<<ui->textEditB->toHtml();

            file.close();
        }
    }

    emit savable(false);


}

void CentralWidget::setEditable(bool editable)
{
    ui->textEditA->setReadOnly(!editable);
    ui->textEditB->setReadOnly(!editable);

}

void CentralWidget::setSavable()
{
    emit savable(true);

}


QTextEdit * CentralWidget::currentTextEdit()
{
    if ( ui->textEditA->hasFocus())
        return ui->textEditA;
    else return ui->textEditB;
}

