#ifndef PLOTDATA_H
#define PLOTDATA_H

#include <QColor>
#include <QString>
#include <QVector>

struct PlotDataPoint
{
    PlotDataPoint();
    PlotDataPoint(const QString& name, const QColor& colour, int value);

    QString name_;
    QColor colour_;
    int value_;
};

#endif // PLOTDATA_H
