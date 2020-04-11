#include "HistogramPainter.h"

#include <QPaintDevice>
#include <QPainter>
#include <QPoint>
#include <QSize>

#include <algorithm>

#include "PlotData.h"

HistogramBar::HistogramBar(
    const QString& name, const QColor& colour, const QRect& rect)
    : name_(name)
    , colour_(colour)
    , rect_(rect)
{
}

void HistogramPainter::paint(const PlotData& data, QPaintDevice* paintDevice)
{
    bars_.clear();
    histogramData_ = &data;
    paintDevice_ = paintDevice;
    if (!paintDevice)
        return;
    makeBars();
    paintAxes();
    paintBars();
}

void HistogramPainter::makeBars()
{
    bars_.clear();
    if (!paintDevice_ || !histogramData_)
        return;
    auto width = paintDevice_->width();
    auto height = paintDevice_->height();

    const auto& dataPoints = histogramData_->dataPoints();
    if (dataPoints.isEmpty())
        return;
    bars_.reserve(dataPoints.size());
    auto barWidth = (0.8 * width) / dataPoints.size();

    std::transform(
        dataPoints.cbegin(),
        dataPoints.cend(),
        std::back_inserter(bars_),
        [width, height, barWidth](const PlotDataPoint& dp) {
            return HistogramBar(
                dp.name_,
                dp.colour_,
                QRect(
                    QPoint(),
                    QSize(barWidth, 0.9 * height * dp.value_ / 100.0)));
        });

    QPoint axesOrigin(0.1 * width, 0.9 * height);
    auto barBottomLeft = axesOrigin;
    for (auto& bar : bars_)
    {
        bar.rect_.moveBottomLeft(barBottomLeft);
        barBottomLeft += QPoint(barWidth, 0);
    }
}

void HistogramPainter::paintAxes() const
{
}

void HistogramPainter::paintBars() const
{
    if (!paintDevice_ || bars_.isEmpty())
        return;

    QPainter painter(paintDevice_);
    for (const auto& bar : bars_)
    {
        painter.drawRect(bar.rect_);
        painter.fillRect(bar.rect_, bar.colour_);
    }
}
