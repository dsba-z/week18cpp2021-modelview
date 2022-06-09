#include "customproxymodel.h"

CustomProxyModel::CustomProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
    maxFare = 1000;
    minFare = -1;
}


bool CustomProxyModel::filterAcceptsRow(int sourceRow,
                                              const QModelIndex &sourceParent) const
{
    QModelIndex indexFare = sourceModel()->index(sourceRow, 9, sourceParent);

    return fareInRange(sourceModel()->data(indexFare).toDouble());
}

bool CustomProxyModel::fareInRange(double fare) const
{
    return fare >= minFare && fare < maxFare;
}

void CustomProxyModel::setFilterMinimumFare(double fare)
{
    minFare = fare;
    invalidateFilter();
}

void CustomProxyModel::setFilterMaximumFare(double fare)
{
    maxFare = fare;
    invalidateFilter();
}
