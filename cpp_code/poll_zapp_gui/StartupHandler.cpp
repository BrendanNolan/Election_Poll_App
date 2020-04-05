#include "StartupHandler.h"

#include <QDir>
#include <QFile>

#include <cstdlib>
#include <exception>

#include "app_data_functions.h"

void StartupHandler::performStartupTasks()
{
    QDir dir;
    dir.mkpath(paths::pollZAppAppData());
    QDir pzAppData(paths::pollZAppAppData());
    if (!pzAppData.exists())
    {
        throw std::exception(
            "PollZapp app data directory does not exist and could not be "
            "created.");
    }
    pzAppData.mkdir("py_scripts");
    pzAppData.mkdir("databases");
    pzAppData.mkdir("Pictures");

    QFile::copy(
        paths::scriptsSourceDir()
            + QDir::toNativeSeparators("/politician_scraping.py"),
        paths::politicianScrapingScript());
    QFile::copy(
        paths::scriptsSourceDir()
            + QDir::toNativeSeparators("/poll_result_scraping.py"),
        paths::pollResultScrapingScript());
    QFile::copy(
        paths::scriptsSourceDir()
            + QDir::toNativeSeparators("/constituency_scraping.py"),
        paths::constituencyScrapingScript());

    QDir picturesSrcDir(paths::picturesSourceDir());
    auto fileInfoList = picturesSrcDir.entryInfoList();
    for (const auto& entry : fileInfoList)
    {
        QFile::copy(
            entry.absoluteFilePath(),
            paths::picturesDataDir()
                + QDir::toNativeSeparators("/" + entry.fileName()));
    }
}
