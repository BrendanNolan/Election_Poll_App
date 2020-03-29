#include "app_data_functions.h"

#include <QDir>

QString paths::pollZAppAppData()
{
    return std::getenv("POLL_ZAPP");
}

QString paths::databasePath()
{
    return pollZAppAppData()
           + QDir::toNativeSeparators("/databases/primary_database.db");
}

QString paths::politicianScrapingScript()
{
    return pollZAppAppData()
           + QDir::toNativeSeparators("/scripts/politician_scraping.py");
}

QString paths::constituencyScrapingScript()
{
    return pollZAppAppData()
           + QDir::toNativeSeparators("/scripts/constituency_scraping.py");
}

QString paths::pollResultScrapingScript()
{
    return pollZAppAppData()
           + QDir::toNativeSeparators("/scripts/poll_result_scraping.py");
}

QString paths::scriptsSourceDir()
{
    QDir scripts(QDir::toNativeSeparators("../../scripts/"));
    return scripts.absolutePath();
}
