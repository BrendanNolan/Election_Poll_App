#include "HistogramPainter.h"

void HistogramPainter::setPlotData(const PlotData* histogram)
{
    histogram_ = histogram;
}

void HistogramPainter::paint(QPaintDevice* paintDevice)
{
    reset();
    if (!histogram_ || !paintDevice)
        return;
}

void HistogramPainter::makeBars()
{

}

void HistogramPainter::reset()
{
    histogram_ = nullptr;
    bars_.clear();
}
