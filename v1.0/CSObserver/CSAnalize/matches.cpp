#include "matches.h"


Match::Match(QString url, QString t1, QString t2, QString tour, QString type, QString date)
{
    connect(this,SIGNAL(clicked()),this,SLOT(signalRewrite()));
    baseUrl = url;
    team1 = t1;
    team2 = t2;
    tournament = tour;
    matchType = type;
    matchDate = date;

    lblTeam1->setText(t1);
    lblTeam2->setText(t2);
    lblType->setText(type);
    lblTour->setText(tour);
    lblDate->setText(date);

    QVBoxLayout* baselay = new QVBoxLayout();
    QVBoxLayout* lay = new QVBoxLayout();
    QHBoxLayout* lay1 = new QHBoxLayout();
    QHBoxLayout* lay3 = new QHBoxLayout();

    QFont f = lblTeam1->font(); f.setPixelSize(settings->headTextSize);
    lblTeam1->setFont(f);
    f = lblTeam2->font(); f.setPixelSize(settings->headTextSize);
    lblTeam2->setFont(f);

    lay1->addStretch(1);
    lay1->addWidget(lblTeam1);                      lblTeam1->setFixedSize(settings->basicWidth*0.3,settings->roundsHeight/3); lblTeam1->setAlignment(Qt::AlignCenter);
    lay1->addStretch(1);
    lay1->addWidget(versus);
    lay1->addStretch(1);
    lay1->addWidget(lblTeam2);                      lblTeam2->setFixedSize(settings->basicWidth*0.3,settings->roundsHeight/3); lblTeam2->setAlignment(Qt::AlignCenter);
    lay1->addStretch(1);

    lay3->addWidget(lblDate);                       lblDate->setFixedSize(settings->basicWidth*0.3,settings->roundsHeight/6); lblDate->setAlignment(Qt::AlignLeft);
    lay3->addStretch(1);
    lay3->addWidget(lblTour);                       lblTour->setFixedSize(settings->basicWidth*0.3,settings->roundsHeight/6); lblTour->setAlignment(Qt::AlignCenter);
    lay3->addStretch(1);
    lay3->addWidget(lblType);                       lblType->setFixedSize(settings->basicWidth*0.3,settings->roundsHeight/6); lblType->setAlignment(Qt::AlignRight);

    lay->addLayout(lay1);
    lay->addStretch(1);
    lay->addLayout(lay3);

    setLayout(lay);
    setFixedSize(settings->basicWidth*0.95,settings->roundsHeight);
    //versus->move((width()-versus->width())/2,(height()-versus->height())/2);
}

void Match::signalRewrite()
{
    emit clickedMatch(settings->basicUrl + baseUrl);
}

Matches::Matches(QString url)
{
    connect(page,SIGNAL(loadFinished(bool)),this,SLOT(isLoaded()));
    setWindowTitle("CSObserver");

    baseUrl = url;

    matcheslay->setSizeConstraint(QLayout::SetMinAndMaxSize);
    matchList->setLayout(matcheslay);
    matchList->setMaximumSize(settings->basicWidth-150,100000);
    lay->addWidget(sa);
    sa->setWidget(matchList);
    setLayout(lay);
    setFixedSize(settings->basicWidth+20,settings->basicHeight+20);

    load();
}

void Matches::parse(QString html)
{
    HtmlParse parser;

    QString basestr = parser.cutAfter(html,"Upcoming CS:GO matches",1,0); int k=0;
    for(int i=1; i<4; i++)
    {
        QString str = parser.cutAfterWith(basestr,"match-day",1+i,1); int j=1;
        QString date = parser.findText(str,"div","standard-headline");

        while(true)
        {
            QString pstr = parser.cutAfter(str,"<a ",j,0);
            if(pstr=="empty") break;
            QString type = parser.findText(pstr,"div","map-text");
            if(parser.findText(pstr,"span","event-name")=="empty") {j++; continue;}                          // Проверка на считываемость
            Match *match = new Match(parser.findAdress(pstr),
                                    parser.findText(pstr,"div","team",1),
                                    parser.findText(pstr,"div","team",2),
                                    parser.findText(pstr,"span","event-name"),
                                    (type=="empty") ? (parser.findText(pstr,"div","map map-text")) : (type),
                                    date + " " + parser.findText(pstr,"div","time"));
            connect(match,SIGNAL(clickedMatch(QString)),this,SLOT(clickedMatch(QString)));
            matcheslay->addWidget(match);
            buttons << match;
            match->show();
            j++;
        }
    }
    createPage();
}

void Matches::createPage()
{
    disconnect(page,SIGNAL(loadFinished(bool)),this,SLOT(isLoaded()));
    page->deleteLater();
    page = new QWebEnginePage(this);
    connect(page,SIGNAL(loadFinished(bool)),this,SLOT(isLoaded()));
}

void Matches::clickedMatch(QString url)
{
    infospase = new MatchInfo(url);
    connect(infospase,SIGNAL(closed()),this,SLOT(backToList()));
    lay->addWidget(infospase);
    infospase->show();
    sa->hide();
    for(int i=0; i<buttons.size(); i++)
    {
        matcheslay->removeWidget(buttons[i]);
        buttons[i]->deleteLater();
    }
    buttons.clear();
}

void Matches::backToList()
{
    disconnect(infospase,SIGNAL(closed()),this,SLOT(backToList()));
    lay->removeWidget(infospase);
    infospase->deleteLater();
    sa->show();
    load();
}

void Matches::load()
{
    page->load(QUrl(baseUrl));
}

void Matches::isLoaded()
{
    page->toHtml([this](const QString& result){
         parse(result);
    });
}
