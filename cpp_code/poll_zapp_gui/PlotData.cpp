#include "PlotData.h"

PlotDataPoint::PlotDataPoint()
{
}

PlotDataPoint::PlotDataPoint(
    const QString& name, const QColor& colour, int value)
    : name_(name)
    , colour_(colour)
    , value_(value)
{
}
