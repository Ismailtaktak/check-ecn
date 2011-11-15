#include "ecnitemmodel.h"
#include <QDebug>
EcnItemModel::EcnItemModel(QObject *parent) :
    QAbstractTableModel(parent)
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("ecn");
    db.setDatabaseName("ecn.sqlite");

    bool ok = db.open();

    qDebug()<<ok;


    select();




}

int EcnItemModel::rowCount(const QModelIndex &parent) const
{
    return mRecords.count();
}

int EcnItemModel::columnCount(const QModelIndex &parent) const
{
    if ( mRecords.count()>0)
        return mRecords.first().count();
    else return 0;
}

QVariant EcnItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if ( index.row() >= mRecords.count())
        return QVariant();

    if (role == Qt::DisplayRole)
        return mRecords.at(index.row()).value(index.column());

    if ( role == Qt::BackgroundColorRole)
    {
        if ( mRecords.at(index.row()).value(2).toInt() == 1)
            return QColor(255,255,0,30);

        if ( mRecords.at(index.row()).value(2).toInt() == 2)
            return QColor(0,255,0,30);
    }

    if ( role == Qt::TextColorRole)
    {
        if ( mRecords.at(index.row()).value(2).toInt() == 2)
        {
           return Qt::gray;
        }

    }

    if ( role == Qt::FontRole)
    {
        if ( index.column() == 0)
        {
            QFont font = QFont();
            font.setBold(true);
           return font;
        }

    }

    if ( role == Qt::ToolTipRole)
    {
        return "Double cliquer ou <Enter> pour marquer , <Suppr> pour demarquer";

    }

    if ( role == Qt::DecorationRole)
    {

        if ( index.column() == 0)
        {

            int score =  mRecords.at(index.row()).value(2).toInt();

            switch ( score)
            {
            case 0 : return QIcon(":bad.gif"); break;
            case 1 : return QIcon(":tag.png"); break;
            case 2 : return QIcon(":valid.gif"); break;

            }




        }


    }



    return QVariant();
}

Qt::ItemFlags EcnItemModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return 0;

    if ( index.row() >= mRecords.count())
        return 0;

    if ( index.column() == 2)
        return (Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable);	;

    return QAbstractTableModel::flags(index);
}

void EcnItemModel::select(const QString &filter)
{
    mRecords.clear();


    QSqlQuery query;

    if ( filter.isEmpty())
        query.exec("Select * from items");

    else
        query.exec("SELECT * from items where nom LIKE '%"+filter+"%'");

    qDebug()<<query.lastQuery();



    while ( query.next())
    {
        // beginInsertRows(QModelIndex(),0,0);
        mRecords.append(query.record());
        // endInsertRows();
    }

    emit layoutChanged();

}

void EcnItemModel::setScore(const QModelIndex &index, int score)
{

    if ( !index.isValid())
        return;

    QString id = mRecords.at(index.row()).value("id").toString();

    QSqlQuery query;

    query.exec("UPDATE items SET score="+QString::number(score)+" WHERE id = "+id);

    select();

}

int EcnItemModel::score(const QModelIndex &index)
{
    if (!index.isValid())
        return 0;

    return mRecords.at(index.row()).value(2).toInt();
}

QVariant EcnItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ( (orientation == Qt::Horizontal) && (role == Qt::DisplayRole))
    {
        if ( section == 0)
            return "N°";

        if ( section == 1)
            return "item";

        if ( section == 2)
            return "etat";


    }

    return QAbstractTableModel::headerData(section,orientation,role);
}

double EcnItemModel::progression()
{
    double score = 0;
    foreach ( QSqlRecord rec , mRecords)
        score += rec.value("score").toInt();


    return score / (double)(mRecords.count());



}

int EcnItemModel::validCount()
{
    int count = 0;
    foreach ( QSqlRecord rec , mRecords){
        if ( rec.value("score") == 2)
            count ++;


    }
return count;
}

int EcnItemModel::flagCount()
{
    int count = 0;
    foreach ( QSqlRecord rec , mRecords){
        if ( rec.value("score") == 1)
            count ++;


    }
return count;
}

int EcnItemModel::emptyCount()
{
    int count = 0;
    foreach ( QSqlRecord rec , mRecords){
        if ( rec.value("score") == 0)
            count ++;


    }
    return count;
}

void EcnItemModel::clearProgress()
{
    QSqlQuery query;
    query.exec("UPDATE items SET score=0");
    select();



}
