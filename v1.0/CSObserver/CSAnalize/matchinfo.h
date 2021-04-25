#ifndef MATCHINFO_H
#define MATCHINFO_H

#include "teaminfo.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QImage>
#include <QTextEdit>
#include <QPushButton>
#include <QWebEngineView>
#include <QWebEnginePage>


class MatchInfo : public QWidget
{
    Q_OBJECT

public:
    MatchInfo(QString url);
    QString createFilter();

private:
    void parse(QString html);
    void createPage();

    QWebEnginePage* page = new QWebEnginePage(this);
    BaseSettings* settings = new BaseSettings();

    //QWidget* container = new QWidget();
    QLabel* headFrom = new QLabel("С (д,м,г):");
    QLabel* headTo = new QLabel("По (д,м,г):");
    QComboBox* matchFilter = new QComboBox();
    QComboBox* timeFilter = new QComboBox();
    QComboBox* rankingFilter = new QComboBox();
    QComboBox* minPlayers = new QComboBox();
    QComboBox* dayFrom = new QComboBox();
    QComboBox* monthFrom = new QComboBox();
    QComboBox* yearFrom = new QComboBox();
    QComboBox* dayTo = new QComboBox();
    QComboBox* monthTo = new QComboBox();
    QComboBox* yearTo = new QComboBox();
    QComboBox* mapSelect = new QComboBox();
    QPushButton* filter = new QPushButton("Применить фильтр");
    QPushButton* back = new QPushButton("Вернуться к списку матчей");

    //QVBoxLayout* maplay = new QVBoxLayout();
    QVBoxLayout* team1lay = new QVBoxLayout();
    QVBoxLayout* team2lay = new QVBoxLayout();
    QScrollArea *sa[8];
    QWidget* mapxHlay[8];
    QVBoxLayout* mapxlay[16];

    TeamInfo* info1;
    TeamInfo* info2;
    TeamMapInfo* mapxInfo[16]; bool isMapx[16];

    bool firstStatLoad = true;
    QString baseurl;
    QString actFilter;
    QString team1name="", team2name="";
    QString lineup1 = "empty", lineup2 = "empty";
    QStringList matchFilters;
    QStringList timeFilters;
    QStringList rankingFilters;
    QStringList playersFilters;
    QStringList mapsList;
    QStringList mapsIconList;
    QStringList mapsUrlList;

public slots:
    void timeFilterChanged(int i);
    void entFromMonth(int i);
    void entToMonth(int i);
    void load();
    void reMap(int i);
    void reFilter();
    void isLoaded();
    void infoLoaded1(QString lineupFilter);
    void infoLoaded2(QString lineupFilter);
    void closing();

signals:
    void loading();
    void closed();
};

#endif // MATCHINFO_H
