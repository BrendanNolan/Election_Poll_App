#ifndef APP_DATA_FUNCTIONS_H
#define APP_DATA_FUNCTIONS_H

#include <QString>

#include <cstdlib>

namespace paths
{

QString pollZAppAppData();
QString databasePath();
QString politicianScrapingScript();
QString constituencyScrapingScript();
QString pollResultScrapingScript();
QString picturesDataDir();

QString scriptsSourceDir();
QString picturesSourceDir();

}// namespace paths

#endif// APP_DATA_FUNCTIONS_H
