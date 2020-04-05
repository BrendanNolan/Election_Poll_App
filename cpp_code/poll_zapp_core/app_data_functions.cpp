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
           + QDir::toNativeSeparators("/py_scripts/politician_scraping.py");
}

QString paths::constituencyScrapingScript()
{
    return pollZAppAppData()
           + QDir::toNativeSeparators("/py_scripts/constituency_scraping.py");
}

QString paths::pollResultScrapingScript()
{
    return pollZAppAppData()
           + QDir::toNativeSeparators("/py_scripts/poll_result_scraping.py");
}

QString paths::picturesDataDir()
{
    return pollZAppAppData() + QDir::toNativeSeparators("/Pictures/");
}

QString paths::scriptsSourceDir()
{
    QDir scripts(QDir::toNativeSeparators("../../py_scripts/"));
    return scripts.absolutePath();
}

QString paths::picturesSourceDir()
{
    QDir pictures(QDir::toNativeSeparators("../../Pictures/"));
    return pictures.absolutePath();
}
