#ifndef PLOTDATA_H
#define PLOTDATA_H

#include <QColor>
#include <QHash>
#include <QString>
#include <QVector>

struct PlotDataPoint
{
    PlotDataPoint();
    PlotDataPoint(const QString& name, const QColor& colour, int value);
    bool operator==(const PlotDataPoint& other) const;

    QString name_;
    QColor colour_;
    int value_;
};

class PlotData
{
public:
    void addDataPoint(const PlotDataPoint& dataPoint);
    void addNumericalMetaData(const QString& metaDataName, double value);
    void addTextMetaData(const QString& metaDataName, const QString& text);
    
    const QVector<PlotDataPoint>& dataPoints() const;
    const QHash<QString, double>& numericalMetaData() const;
    const QHash<QString, QString>& textMetaData() const;

    bool operator==(const PlotData& other) const;

private:
    QVector<PlotDataPoint> dataPoints_;
    QHash<QString, double> numericalMetaData_;
    QHash<QString, QString> textMetaData_;
};

#endif// PLOTDATA_H
