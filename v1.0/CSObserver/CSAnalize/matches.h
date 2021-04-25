#ifndef MATCHES_H
#define MATCHES_H

#include "matchinfo.h"

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


class Match : public QPushButton
{
    Q_OBJECT

public:
    Match(QString url, QString t1, QString t2, QString tour, QString type, QString date);

    BaseSettings* settings = new BaseSettings();
    QLabel* lblTeam1 = new QLabel();
    QLabel* lblTeam2 = new QLabel();
    QLabel* versus = new QLabel(" vs ",this);
    QLabel* lblTour = new QLabel();
    QLabel* lblType = new QLabel();
    QLabel* lblDate = new QLabel();

    QString baseUrl="", team1="", team2="", tournament="", matchType="", matchDate="";
    QDate date;
    QTime time;

public slots:
    void signalRewrite();

signals:
    void clickedMatch(QString url);

};


class Matches : public QWidget
{
    Q_OBJECT

public:
    Matches(QString url);

private:
    void parse(QString html);
    void createPage();

    QWebEnginePage* page = new QWebEnginePage(this);
    BaseSettings* settings = new BaseSettings();

    QVBoxLayout *lay = new QVBoxLayout();
    QVBoxLayout *matcheslay = new QVBoxLayout();
    QScrollArea *sa = new QScrollArea();
    QWidget *matchList = new QWidget();
    MatchInfo *infospase;

    QVector <Match*> buttons;
    QString baseUrl="";

public slots:
    void clickedMatch(QString url);
    void backToList();
    void load();
    void isLoaded();

signals:


};

#endif // MATCHES_H
