#include "clinetablemodel.h"
#include <QDebug>

CLineTableModel::CLineTableModel(QObject *parent) : QAbstractTableModel(parent)
{    
    listClines.clear();
}

QVariant CLineTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            switch(section)
            {
            case 0: return tr("Server");
            case 1: return tr("Port");
            case 2: return tr("Username");
            case 3: return tr("Password");
            }

        }
        else
        {
            return section+1;
        }
    }
    return QVariant();
}

int CLineTableModel::rowCount(const QModelIndex &parent) const
{
    return listClines.size();
}

int CLineTableModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant CLineTableModel::data(const QModelIndex &index, int role) const
{    
    if(role == Qt::DisplayRole || role == Qt::EditRole && index.row() <= listClines.size()-1)
    {
        CLine cline = listClines[index.row()];
        switch(index.column())
        {
        case 0:
            return cline.getServer();
        case 1:
            return cline.getPort();
        case 2:
            return cline.getUsername();
        case 3:
            return cline.getPassword();
        default:
            return "";
        }
    }
    return QVariant();

}

bool CLineTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        int port = 0;
        QString txt = value.toString();
        switch(index.column())
        {
        case 0:
            if(CLine::isServerValid(txt))
                listClines[index.row()].setServer(txt);
            break;
        case 1:
            bool ok;
            port = value.toInt(&ok);

            if(ok && CLine::isPortValid(port))
                listClines[index.row()].setPort(port);

            break;
        case 2:
            if(CLine::isUsernameValid(txt))
                listClines[index.row()].setUsername(txt);
            break;
        case 3:
            if(CLine::isPasswordValid(txt))
                listClines[index.row()].setPassword(txt);
            break;
        }
    }
    return true;

}

bool CLineTableModel::removeRow(int row, const QModelIndex &parent)
{
    if(row >= listClines.size()) return false;

    beginRemoveRows(QModelIndex(), row, row);
    listClines.removeAt(row);
    endRemoveRows();
    return true;
}

void CLineTableModel::sort(int column, Qt::SortOrder order)
{
    if(order == Qt::AscendingOrder)
    {
        emit layoutAboutToBeChanged();
        switch (column)
        {
        case 0:
            qSort(listClines.begin(), listClines.end(), CLine::sortOnServerAsc);
            break;
        case 1:
            qSort(listClines.begin(), listClines.end(), CLine::sortOnPortAsc);
            break;
        case 2:
            qSort(listClines.begin(), listClines.end(), CLine::sortOnUsernameAsc);
            break;
        case 3:
            qSort(listClines.begin(), listClines.end(), CLine::sortOnPasswordAsc);
            break;
        }
        emit layoutChanged();
    }
    else
    {
        emit layoutAboutToBeChanged();
        switch (column)
        {
        case 0:
            qSort(listClines.begin(), listClines.end(), CLine::sortOnServerDesc);
            break;
        case 1:
            qSort(listClines.begin(), listClines.end(), CLine::sortOnPortDesc);
            break;
        case 2:
            qSort(listClines.begin(), listClines.end(), CLine::sortOnUsernameDesc);
            break;
        case 3:
            qSort(listClines.begin(), listClines.end(), CLine::sortOnPasswordDesc);
            break;
        }
        emit layoutChanged();
    }
}

Qt::ItemFlags CLineTableModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;
}

void CLineTableModel::clear()
{
    int n=rowCount()-1;
    beginRemoveRows(QModelIndex(), 0, n);
    listClines.clear();
    endRemoveRows();
}

void CLineTableModel::addCline(CLine cline)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    listClines.append(cline);
    endInsertRows();
}

QList<CLine> CLineTableModel::getClines()
{
    return listClines;
}
