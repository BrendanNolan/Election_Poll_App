#ifndef IPLOTPAINTER_H
#define IPLOTPAINTER_H

#include <QColor>
#include <QVector>

struct PlotDataPoint
{
    PlotDataPoint(const QString& name, const QColor& colour, int value)
        : name_(name)
        , colour_(colour)
        , value_(value)
    {
    }

    QString name_;
    QColor colour_;
    int value_;
};

using PlotData = QVector<PlotDataPoint>;

class QPaintDevice;

class IPlotPainter
{
public:
    virtual ~IPlotPainter() = default;
    virtual void setPlotData(const PlotData* plot) = 0;
    virtual void paint(QPaintDevice* paintDevice) = 0;
};

#endif// IPLOTPAINTER_H
