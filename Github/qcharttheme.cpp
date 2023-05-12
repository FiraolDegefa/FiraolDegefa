#include "qcharttheme.h"

QChartTheme::QChartTheme(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant QChartTheme::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex QChartTheme::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex QChartTheme::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int QChartTheme::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int QChartTheme::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant QChartTheme::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
