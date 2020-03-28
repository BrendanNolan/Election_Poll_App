#include "Constituency.h"

Constituency::Constituency(const QString& name, int latitude, int longitude)
    : name_(name)
    , latitude_(latitude)
    , longitude_(longitude)
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

int Constituency::latitude() const
{
    return latitude_;
}

void Constituency::setLatitude(int latitude)
{
    latitude_ = latitude;
}

int Constituency::longitude() const
{
    return longitude_;
}

void Constituency::setLongitude(int longitude)
{
    longitude_ = longitude;
}
