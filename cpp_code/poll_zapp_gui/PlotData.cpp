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

bool PlotDataPoint::operator==(const PlotDataPoint& other) const
{
    return name_ == other.name_ && colour_ == other.colour_
           && value_ == other.value_;
}

void PlotData::add(const PlotDataPoint& dataPoint)
{
    dataPoints_.append(dataPoint);
}

bool PlotData::operator==(const PlotData& other) const
{
    return dataPoints_ == other.dataPoints_;
}
