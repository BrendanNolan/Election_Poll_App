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
    void paintAxes() const;
    void paintBars() const;

    void reset();

private:
    const PlotData* histogramData_;

    QHash<QString, QRect> bars_;
};

#endif// HISTOGRAMPAINTER_H
