#ifndef CLINETABLEMODEL_H
#define CLINETABLEMODEL_H

#include "cline.h"
#include <QStringList>
#include <QAbstractTableModel>

class CLineTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    CLineTableModel(QObject *parent);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool removeRow(int row, const QModelIndex &parent);    
    void sort(int column, Qt::SortOrder order);
    Qt::ItemFlags flags(const QModelIndex & index) const;    

    void clear();

    void addCline(CLine cline);
    QList<CLine> getClines();

private:
    QList<CLine> listClines;
    //static QStringList listHeaders;
};

#endif // CLINETABLEMODEL_H
