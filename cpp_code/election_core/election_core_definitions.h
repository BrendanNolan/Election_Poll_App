#ifndef ELECTIONDEFINITIONS_H
#define ELECTIONDEFINITIONS_H

#include <QDir>
#include <QString>

#include <cstdlib>

namespace paths
{

static const QString pollZAppAppData(std::getenv("POLL_ZAPP"));

static const auto databasePath =
    pollZAppAppData
    + QDir::toNativeSeparators("/databases/primary_database.db");

static const auto politicianScrapingScript =
    pollZAppAppData
    + QDir::toNativeSeparators("/scripts/politician_scraping.py");

static const auto constituencyScrapingScript =
    pollZAppAppData
    + QDir::toNativeSeparators("/scripts/constituency_scraping.py");

static const auto pollResultScrapingScript =
    pollZAppAppData
    + QDir::toNativeSeparators("/scripts/poll_result_scraping.py");

}// namespace paths

#endif// ELECTIONDEFINITIONS_H
