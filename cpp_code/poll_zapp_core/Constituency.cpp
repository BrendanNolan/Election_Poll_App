#include "Constituency.h"

Constituency::Constituency(
    const QString& name, float latitude, float longitude, float areaSqKm)
    : name_(name)
    , latitude_(latitude)
    , longitude_(longitude)
    , areaSqKm_(areaSqKm)
{
}

int Constituency::id() const
{
    return id_;
}

void Constituency::setId(int id)
{
    id_ = id;
}

QString Constituency::name() const
{
    return name_;
}

void Constituency::setName(const QString& name)
{
    name_ = name;
}

float Constituency::latitude() const
{
    return latitude_;
}

void Constituency::setLatitude(float latitude)
{
    latitude_ = latitude;
}

float Constituency::longitude() const
{
    return longitude_;
}

void Constituency::setLongitude(float longitude)
{
    longitude_ = longitude;
}

float Constituency::areaSqKm() const
{
    return areaSqKm_;
}

void Constituency::setAreaSqKm(float sqKm)
{
    areaSqKm_ = sqKm;
}
