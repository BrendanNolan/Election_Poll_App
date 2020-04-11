#ifndef HISTOGRAMPAINTER_H
#define HISTOGRAMPAINTER_H

#include <QRect>
#include <QString>

#include "IPlotPainter.h"

class PlotData;
class QPaintDevice;

struct HistogramBar
{
    HistogramBar(const QString& name, const QColor& colour, const QRect& rect);

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
    QPaintDevice* paintDevice_ = nullptr;

    QVector<HistogramBar> bars_;
};

#endif// HISTOGRAMPAINTER_H
