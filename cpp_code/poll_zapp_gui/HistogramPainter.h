#ifndef HISTOGRAMPAINTER_H
#define HISTOGRAMPAINTER_H

#include <QRect>
#include <QString>

#include "IPlotPainter.h"

class PlotData;
class QPaintDevice;

struct HistogramBar
{
    HistogramBar() = default;
    HistogramBar(const QString& name, const QColor& colour, const QRect& rect);

    QString name_;
    QColor colour_;
    QRect rect_;
};

class HistogramPainter : public IPlotPainter
{
public:
    void paint(const PlotData& data, QPaintDevice* paintDevice) override;

protected:
    void makeBars();
    void paintAxes() const;
    void paintBars() const;

private:
    const PlotData* histogramData_;
    QPaintDevice* paintDevice_ = nullptr;

    QVector<HistogramBar> bars_;
};

#endif// HISTOGRAMPAINTER_H
