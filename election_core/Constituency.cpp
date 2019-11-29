#include "Constituency.h"

Constituency::Constituency(const QString& name)
    : name_(name)
{}

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

bool Constituency::isValid() const
{
    if (id_ < 0 || latitude_ < 0 || longitude < 0 || name_ == "")
        return false;
    return true;
}
