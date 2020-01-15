#ifndef ELECTIONCOREFUNCTIONS_H
#define ELECTIONCOREFUNCTIONS_H

class QAbstractListModel;
class QModelIndex;

bool isIndexValid(const QModelIndex& index, const QAbstractListModel& model);

#endif // ELECTIONCOREFUNCTIONS_H
