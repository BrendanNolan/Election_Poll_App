#ifndef CONSTITUENCY_H
#define CONSTITUENCY_H

#include <QUrl>
#include <QString>

class Constituency
{
public:
    Constituency() = default;
    Constituency(
        const QString& name, float latitude, float longitude, float areaSqKm);

    int id() const;
    void setId(int id);
    QString name() const;
    void setName(const QString& name);
    float latitude() const;
    void setLatitude(float latitude);
    float longitude() const;
    void setLongitude(float longitude);
    float areaSqKm() const;
    void setAreaSqKm(float sqKm);

private:
    int id_ = -1;
    QString name_ = QString("");
    float latitude_ = 0.0f;
    float longitude_ = 0.0f;
    float areaSqKm_ = -1;
};

#endif// CONSTITUENCY_H
