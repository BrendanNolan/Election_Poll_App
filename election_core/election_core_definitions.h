#ifndef ELECTIONDEFINITIONS_H
#define ELECTIONDEFINITIONS_H

#include <QString>

namespace paths
{

static const QString
    databasePath("C:\\CPP_Stuff\\Election_Poll_App\\primary_database.db");

static const QString politicianScrapingScript(
    "C:\\CPP_Stuff\\Election_Poll_App\\Scripts\\politician_scraping.py");
static const QString constituencyScrapingScript(
    "C:\\CPP_Stuff\\Election_Poll_App\\Scripts\\constituency_scraping.py");
static const QString pollResultScrapingScript(
    "C:\\CPP_Stuff\\Election_Poll_App\\Scripts\\poll_result_scraping.py");

}// namespace paths

#endif// ELECTIONDEFINITIONS_H
