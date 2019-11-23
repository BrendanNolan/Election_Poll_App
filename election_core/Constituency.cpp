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
