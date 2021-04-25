#ifndef TEAMS_H
#define TEAMS_H

#include "teaminfo.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QWebEngineView>
#include <QWebEnginePage>


class Teams : public QWidget
{
    Q_OBJECT

public:
    Teams(QWidget* parent);

private:
    TeamMapInfo* cache; bool isCache;
    TeamMapInfo* dust2; bool isDuts2;
    TeamMapInfo* inferno; bool isInferno;
    TeamMapInfo* mirage; bool isMirage;
    TeamMapInfo* nuke; bool isNuke;
    TeamMapInfo* overpass; bool isOverpass;
    TeamMapInfo* train; bool isTrain;
    TeamMapInfo* vertigo; bool isVertigo;


public slots:


signals:


};

#endif // TEAMS_H
