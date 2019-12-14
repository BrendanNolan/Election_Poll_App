#ifndef LISTMODELFUNCTIONS_H
#define LISTMODELFUNCTIONS_H

class QAbstractListModel;
class QModelIndex;

bool isIndexValid(const QModelIndex& index, const QAbstractListModel& model);

#endif
