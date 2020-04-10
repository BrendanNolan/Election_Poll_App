#ifndef IPLOTPAINTER_H
#define IPLOTPAINTER_H

#include <QColor>
#include <QVector>

class PlotData;
class QPaintDevice;

class IPlotPainter
{
public:
    virtual ~IPlotPainter() = default;
    virtual void setPlotData(const PlotData* plot) = 0;
    virtual void paint(QPaintDevice* paintDevice) = 0;
};

#endif// IPLOTPAINTER_H
