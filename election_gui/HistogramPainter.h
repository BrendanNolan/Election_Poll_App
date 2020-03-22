#ifndef HISTOGRAMPAINTER_H
#define HISTOGRAMPAINTER_H

#include <QHash>
#include <QRect>
#include <QString>

class QPaintDevice;

using Histogram = QHash<QString, int>;

class HistogramPainter
{
public:
    HistogramPainter(const Histogram* histogram = nullptr);
    virtual ~HistogramPainter() = default;
    
    void setHistogram(const Histogram* histogram);
    virtual void paint(QPaintDevice* paintDevice);

protected:
    void makeBars();
    
    void reset();

private:
    const Histogram* histogram_;

    QHash<QString, QRect> bars_;
};

#endif// HISTOGRAMPAINTER_H
