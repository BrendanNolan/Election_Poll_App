#ifndef HISTOGRAMPAINTER_H
#define HISTOGRAMPAINTER_H

#include <QRect>
#include <QString>

#include "IPlotPainter.h"
#include "PlotData.h"

class QPaintDevice;

struct HistogramBar
{
    QString name_;
    QColor colour_;
    QRect rect_;
};

class HistogramPainter : public IPlotPainter
{
public:
    void setPlotData(const PlotData* data) override;
    void paint(QPaintDevice* paintDevice) override;

protected:
    void makeBars();
    void paintAxes() const;
    void paintBars() const;

    void reset();

private:
    const PlotData* histogramData_;

    QVector<HistogramBar> bars_;
};

#endif// HISTOGRAMPAINTER_H
