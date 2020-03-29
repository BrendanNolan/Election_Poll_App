#ifndef IPLOTPAINTER_H
#define IPLOTPAINTER_H

using PlotData = QHash<QString, int>;

class QPaintDevice;

class IPlotPainter
{
public:
    virtual void setPlotData(const PlotData* plot) = 0;
    virtual void paint(QPaintDevice* paintDevice) = 0;
};

#endif// IPLOTPAINTER_H
