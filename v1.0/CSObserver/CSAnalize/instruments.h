#ifndef INSTRUMENTS_H
#define INSTRUMENTS_H

#include <QObject>
#include <QDebug>
#include <QWebEnginePage>


class WebPageQueue : public QObject
{
    Q_OBJECT
public:
    void addPage(QWebEnginePage* page, QString url);

private:
    QVector <QWebEnginePage*> pages;
    QVector <QString> urls;
    bool loading = false;

public slots:
    void nextPage();

};

class BaseSettings
{
public:
    QString basicUrl = "https://www.hltv.org";
    QString teamUrl = "https://www.hltv.org/stats/teams";
    QString matchesUrl = "https://www.hltv.org/matches";
    QString lineupUrl = "https://www.hltv.org/stats/lineup";
    QString basicCatalog = "";

    bool defaultFull = false;

    int basicWidth = 950;
    int sectionWidth = 420;

    int basicHeight = 700;
    int scrollAreaHeight = 400;
    int roundsHeight = 100;
    int mapStatHeight = 150;
    int mapHeight = 200;
    int buttHeight = 30;

    int picSize = 11;

    int basicTextSize = 10;
    int headTextSize = 15;
};


class HtmlParse : public QObject
{

public:
    HtmlParse();

    QString cutBetween(QString html, QString start, QString finish);

    QString cutAfter(QString html, QString findIt);
    QString cutAfter(QString html, QString findIt, int num);
    QString cutAfter(QString html, QString findIt, int num, int levelUp);
    QString cutAfterWith(QString html, QString findIt, int num, int levelUp);
    QString cutUrlSection(QString html, int num);

    QString findText(QString str, QString xstr);
    QString findText(QString str, QString xstr, int num);
    QString findText(QString str, QString xstr, QString className);
    QString findText(QString str, QString xstr, QString className, int num);
    QString findField(QString str, QString xstr);
    QString findField(QString str, QString xstr, int num);
    QString findImage(QString html);
    QString findImage(QString html, int num);
    QString findAdress(QString html);
    QString findAdress(QString html, int num);

    QString cutAfterAndFindText(QString html, QString findIt, QString xstr);

private:
    long findEnd(QString html, int sp, int fp, int j);
    long findEnd2(QString html, int sp, int fp, int j);

};

#endif // INSTRUMENTS_H
