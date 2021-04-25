#ifndef TEAMINFO_H
#define TEAMINFO_H

#include "instruments.h"

#include <QDebug>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QComboBox>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QNetworkAccessManager>
#include <QNetworkReply>


class mapStat : public QWidget
{
    Q_OBJECT

public:
    mapStat(QString url, QString tname);
    QWidget* wgtFull = new QWidget();
    QWidget* wgtDemo = new QWidget();
    QHBoxLayout* layTop = new QHBoxLayout();
    QHBoxLayout* layBot = new QHBoxLayout();
    QHBoxLayout* layHead = new QHBoxLayout();
    QVBoxLayout* layRounds = new QVBoxLayout();
    QHBoxLayout* lay = new QHBoxLayout(this);
    QHBoxLayout* layFull = new QHBoxLayout(wgtFull);
    QHBoxLayout* layDemo = new QHBoxLayout(wgtDemo);

    QLabel* team1Head = new QLabel;
    QLabel* team2Head = new QLabel;
    QLabel* results = new QLabel();
    QLabel* round1Ic = new QLabel();
    QLabel* round16Ic = new QLabel();
    QLabel* tournament = new QLabel();
    QLabel* date = new QLabel();
    QLabel* opponent = new QLabel();
    QLabel* roundTopIcon[30];
    QLabel* roundBotIcon[30];
    QPushButton *full = new QPushButton();
    QWebEnginePage* page = new QWebEnginePage(this);
    BaseSettings* settings = new BaseSettings();

    QString baseurl;
    QString filter="";
    QString teamName;
    QIcon icon1;
    QIcon icon2;
    int resTeam1[30];
    int resTeam2[30];
    int rounds=0;

private:
    void createPage();

    QString t_win = "t_win.png";
    QString ct_win = "ct_win.png";
    QString bomb_exploded = "bomb_exploded.png";
    QString bomb_defused = "bomb_defused.png";
    QString defeat = "defeat.png";
    QString stopwatch = "stopwatch.png";

    float iconCoef = 0.21;
    float xxxCoef = 0.2;

public slots:
    void roundEdit(int team, int pos, int res, QString icon);
    void roundParse(QString html, int team, int half);
    void parse(QString html);
    void load();
    void reFilter(QString filter);
    void isLoaded();
    void createFull();
    void createDemo();
    void openFull();
    void openDemo();
};

class TeamMapInfo : public QWidget
{
    Q_OBJECT

public:
    TeamMapInfo();
    TeamMapInfo(QString url, QString filter, QString tname, QString name, QString iconUrl);
    void init(QString url, QString filter, QString tname, QString name, QString iconUrl);
    void interfaseCreate();

    QLabel *header = new QLabel();
    QLabel *matches = new QLabel();
    QLabel *matchStat = new QLabel();
    QLabel *roundsStat = new QLabel();
    QLabel *pistolStat = new QLabel();
    QVector <mapStat*> maps;

    bool loading = false;
    bool loaded = false;
    bool initialized = false;

private:
    QWebEnginePage* page = new QWebEnginePage(this);
    BaseSettings* settings = new BaseSettings();

    QVBoxLayout *lay = new QVBoxLayout();
    QVBoxLayout *rlay = new QVBoxLayout();

    QString mapurl = "", teamName = "";
    QString filter="";
    bool fmenu=false;

    void parse(QString html);
    void createPage();

public slots:
    void load();
    void isLoaded();
    void reFilter(QString filter);

signals:
    //void loading();

};

struct Player
{
    QLabel* nick = new QLabel();
    QLabel* photo = new QLabel();
    QString name = "";
    QString photoUrl = "";
    QString url = "";
};

class TeamInfo : public QWidget
{
    Q_OBJECT

public:
    TeamInfo(QString url, QString filter);
    QString currentLineupFilter();

    QVBoxLayout* lay = new QVBoxLayout();
    QLabel* teamName = new QLabel();
    QLabel* winStat = new QLabel();
    QLabel* kdaStat = new QLabel();
    QVector <Player> players;
    QString actFilter="";

private:
    void parse(QString html);
    void createPage();

    QWebEnginePage* page = new QWebEnginePage(this);
    BaseSettings* settings = new BaseSettings();
    QString baseurl="";
    QString filter="";


public slots:
    void load();
    void isLoaded();
    void reFilter(QString filter);

signals:
    void loading();
    void lineupFilter(QString str);

};

#endif // TEAMINFO_H
