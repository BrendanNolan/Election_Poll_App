#ifndef PLOTDATA_H
#define PLOTDATA_H

#include <QColor>
#include <QString>
#include <QVector>

struct PlotDataPoint
{
    PlotDataPoint();
    PlotDataPoint(const QString& name, const QColor& colour, int value);
    bool operator==(const PlotDataPoint& other) const;

    QString name_;
    QColor colour_;
    int value_;
};

class PlotData
{
public:
    void add(const PlotDataPoint& dataPoint);
    bool operator==(const PlotData& other) const;

private:
    QVector<PlotDataPoint> dataPoints_;
};

#endif// PLOTDATA_H
