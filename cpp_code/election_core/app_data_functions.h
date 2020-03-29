#ifndef ELECTION_CORE_DEFINITIONS_H
#define ELECTION_CORE_DEFINITIONS_H

#include <QDir>
#include <QString>

#include <cstdlib>

namespace paths
{

QString pollZAppAppData()
{
    return std::getenv("POLL_ZAPP");
}

QString databasePath()
{
    return pollZAppAppData()
           + QDir::toNativeSeparators("/databases/primary_database.db");
}

QString politicianScrapingScript()
{
    return pollZAppAppData()
           + QDir::toNativeSeparators("/scripts/politician_scraping.py");
}

QString constituencyScrapingScript()
{
    return pollZAppAppData()
           + QDir::toNativeSeparators("/scripts/constituency_scraping.py");
}

QString pollResultScrapingScript()
{
    return pollZAppAppData()
           + QDir::toNativeSeparators("/scripts/poll_result_scraping.py");
}

}// namespace paths

#endif// ELECTION_CORE_DEFINITIONS_H
