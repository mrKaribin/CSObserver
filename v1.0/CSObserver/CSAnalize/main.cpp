#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>

#include "matches.h"
#include "delphinosyncro.h"

WebPageQueue *webQueue = new WebPageQueue;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setAttribute (Qt :: AA_UseOpenGLES);

    BaseSettings settings;

    //MainWindow* reader = new MainWindow();
    //reader->show();

    //TeamMapInfo *map = new TeamMapInfo("https://www.hltv.org/stats/lineup/map/34?lineup=2553&lineup=7356&lineup=9574&lineup=11652&lineup=15204&minLineupMatch=3&startDate=2019-02-08&endDate=2019-05-08","Virtus.pro","Nuke","C:\\Users\\demam\\OneDrive\\Documents\\QtProjects\\CSAnalize\\nuke.png");
    //map->show();

    //TeamInfo *info = new TeamInfo("https://www.hltv.org/stats/teams/5378/Virtus.pro?startDate=2019-02-09&endDate=2019-05-09");
    //info->show();

    //MatchInfo* minfo = new MatchInfo("https://www.hltv.org/matches/2332806/astralis-vs-nip-blast-pro-series-madrid-2019");
    //minfo->show();

    Delphinosyncro* securitySystem = new Delphinosyncro();

    //Matches* matches = new Matches(settings.matchesUrl);
    //matches->show();


    return a.exec();
}
