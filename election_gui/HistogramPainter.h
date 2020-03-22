#ifndef HISTOGRAMPAINTER_H
#define HISTOGRAMPAINTER_H

#include <QHash>
#include <QString>

class QPaintDevice;

using Histogram = QHash<QString, int>;

class HistogramPainter
{
public:
    void paint(const Histogram& histogram, QPaintDevice* paintDevice) const;
};

#endif// HISTOGRAMPAINTER_H
