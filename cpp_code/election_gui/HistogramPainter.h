#ifndef HISTOGRAMPAINTER_H
#define HISTOGRAMPAINTER_H

#include <QHash>
#include <QRect>
#include <QString>

#include "IPlotPainter.h"

class QPaintDevice;

class HistogramPainter : public IPlotPainter
{
public:
    void setPlotData(const PlotData* histogram) override;
    void paint(QPaintDevice* paintDevice) override;

protected:
    void makeBars();
    
    void reset();

private:
    const PlotData* histogram_;

    QHash<QString, QRect> bars_;
};

#endif// HISTOGRAMPAINTER_H
