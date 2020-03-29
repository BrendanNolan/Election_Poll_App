#ifndef ELECTIONDEFINITIONS_H
#define ELECTIONDEFINITIONS_H

#include <QString>

namespace paths
{

static const QString databasePath(
    DATABASE_PATH);

static const auto politicianScrapingScript =
    QString(SCRIPTS_PATH) + "\\politician_scraping.py";
static const auto constituencyScrapingScript =
    QString(SCRIPTS_PATH) + "\\constituency_scraping.py";
static const auto pollResultScrapingScript =
    QString(SCRIPTS_PATH) + "\\poll_result_scraping.py";

}// namespace paths

#endif// ELECTIONDEFINITIONS_H
