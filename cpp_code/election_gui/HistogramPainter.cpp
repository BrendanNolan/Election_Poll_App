#include "HistogramPainter.h"

void HistogramPainter::setPlotData(const PlotData* histogram)
{
    histogramData_ = histogram;
}

void HistogramPainter::paint(QPaintDevice* paintDevice)
{
    reset();
    if (!histogramData_ || !paintDevice)
        return;
    makeBars();
    paintAxes();
    paintBars();
}

void HistogramPainter::makeBars()
{
}

void HistogramPainter::paintAxes() const
{
}

void HistogramPainter::paintBars() const
{
}

void HistogramPainter::reset()
{
    histogramData_ = nullptr;
    bars_.clear();
}
