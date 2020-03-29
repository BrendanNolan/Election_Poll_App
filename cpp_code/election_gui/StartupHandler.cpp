#include "StartupHandler.h"

#include <QDir>
#include <QFile>

#include <cstdlib>
#include <exception>

#include "election_core_definitions.h"

void StartupHandler::performStartupTasks()
{
    QDir pollZappData(paths::pollZAppAppData);
    if (!pollZappData.exists())
    {
        QDir appData(std::getenv("APPDATA"));
        if (!appData.exists())
            throw std::exception(
                "APPDATA environment variable is either absent or does not "
                "point to a valid directory.");
        if (!pollZappData.mkpath(paths::pollZAppAppData))
            throw std::exception("Could not create directory for app.");
    }
    pollZappData.mkdir("scripts");
    pollZappData.mkdir("databases");

    QDir scriptsSourceDir(QDir::toNativeSeparators("../../scripts/"));
    auto scriptsSourceDirAbsPath = scriptsSourceDir.absolutePath();

    QFile::copy(
        scriptsSourceDirAbsPath
            + QDir::toNativeSeparators("politician_scraping.py"),
        paths::politicianScrapingScript);
    QFile::copy(
        scriptsSourceDirAbsPath
            + QDir::toNativeSeparators("poll_result_scraping.py"),
        paths::pollResultScrapingScript);
    QFile::copy(
        scriptsSourceDirAbsPath
            + QDir::toNativeSeparators("constituency_scraping.py"),
        paths::constituencyScrapingScript);
}
