#ifndef WINBODY_H
#define WINBODY_H

#include "matches.h"
#include "teams.h"
#include "tournaments.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QWebEngineView>
#include <QWebEnginePage>


class WinBody : public QWidget
{
    Q_OBJECT

public:
    WinBody();

private:
    QVBoxLayout *blay = new QVBoxLayout();
    QHBoxLayout *lay = new QHBoxLayout();
    QPushButton *reload = new QPushButton("Обновить",this);


public slots:


signals:


};

#endif // WINBODY_H
