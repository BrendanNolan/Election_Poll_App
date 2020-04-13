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

void PlotData::addDataPoint(const PlotDataPoint& dataPoint)
{
    dataPoints_.append(dataPoint);
}

void PlotData::addNumericalMetaData(const QString& metaDataName, double value)
{
    numericalMetaData_[metaDataName] = value;
}

void PlotData::addTextMetaData(const QString& metaDataName, const QString& text)
{
    textMetaData_[metaDataName] = text;
}

const QVector<PlotDataPoint>& PlotData::dataPoints() const
{
    return dataPoints_;
}

const QHash<QString, double>& PlotData::numericalMetaData() const
{
    return numericalMetaData_;
}

const QHash<QString, QString>& PlotData::textMetaData() const
{
    return textMetaData_;
}

bool PlotData::operator==(const PlotData& other) const
{
    return dataPoints_ == other.dataPoints_
           && numericalMetaData_ == other.numericalMetaData_
           && textMetaData_ == other.textMetaData_;
}
