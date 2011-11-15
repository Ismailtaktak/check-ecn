#ifndef ECNITEMMODEL_H
#define ECNITEMMODEL_H

#include <QtSql>
#include <QAbstractTableModel>


class EcnItemModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit EcnItemModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    int score(const QModelIndex &index);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    double progression();
    int validCount();
    int flagCount();
    int emptyCount();

public slots:
    void clearProgress();
    void select(const QString& filter = QString());
    void setScore(const QModelIndex &index, int score);

private:
    QList<QSqlRecord> mRecords;

};

#endif // ECNITEMMODEL_H
