#include "matchinfo.h"

extern WebPageQueue *webQueue;

MatchInfo::MatchInfo(QString url)
{
    connect(page,SIGNAL(loadFinished(bool)),this,SLOT(isLoaded()));
    connect(filter,SIGNAL(clicked()),this,SLOT(reFilter()));
    connect(back,SIGNAL(clicked()),this,SLOT(closing()));
    connect(monthFrom,SIGNAL(activated(int)),this,SLOT(entFromMonth(int)));
    connect(monthTo,SIGNAL(activated(int)),this,SLOT(entToMonth(int)));
    connect(mapSelect,SIGNAL(activated(int)),this,SLOT(reMap(int)));

    matchFilters << "empty" << "matchType=Lan" << "matchType=Online" << "matchType=BigEvents" << "matchType=Majors" ;
    rankingFilters << "empty" << "rankingFilter=Top5" << "rankingFilter=Top10" << "rankingFilter=Top20" << "rankingFilter=Top30" << "rankingFilter=Top50" ;
    playersFilters << "empty" << "minLineupMatch=1" << "minLineupMatch=2" << "minLineupMatch=3" << "minLineupMatch=4" ;
    mapsList << "Cache" << "Dust2" << "Inferno" << "Mirage" << "Nuke" << "Overpass" << "Train" << "Vertigo";
    mapsIconList << "cache.png" << "dust2.png" << "inferno.png" << "mirage.png" << "nuke.png" << "overpass.png" << "train.png" << "vertigo.png";
    mapsUrlList << "/map/29" << "/map/31" << "/map/33" << "/map/32" << "/map/34" << "/map/40" << "/map/35" << "/map/46";

    QStringList list;
    baseurl = url;

    QHBoxLayout* flay1 = new QHBoxLayout();                 flay1->setMargin(0); flay1->setSpacing(5);
    QHBoxLayout* flay2 = new QHBoxLayout();                 flay2->setMargin(0); flay2->setSpacing(5);
    QVBoxLayout* flay = new QVBoxLayout();                  flay->setMargin(5); flay->setSpacing(1);

    flay1->addWidget(matchFilter);                          list.clear(); list << "All matches" << "LAN" << "Online" << "Big events" << "Majors";
                                                            matchFilter->addItems(list); matchFilter->setCurrentIndex(0);
    flay1->addWidget(timeFilter);                           list.clear(); list << "All time" << "Custom" << "Last month" << "Last 2 month" << "Last 3 month" << "Last 6 month" << "Last year";
                                                            timeFilter->addItems(list); timeFilter->setCurrentIndex(3);
    flay1->addWidget(rankingFilter);                        list.clear(); list << "All" << "Top 5" << "Top 10" << "Top 20" << "Top 30" << "Top 50";
                                                            rankingFilter->addItems(list); rankingFilter->setCurrentIndex(0);
    flay1->addWidget(minPlayers);                           list.clear(); list << "All" << "min. 1 pl." << "min. 2 pl." << "min. 3 pl." << "min. 4 pl.";
                                                            minPlayers->addItems(list); minPlayers->setCurrentIndex(3);

    flay2->addWidget(headFrom);                             headFrom->hide();
    flay2->addWidget(dayFrom);                              dayFrom->hide();
    flay2->addWidget(monthFrom);                            list.clear(); for(int i=1; i<=12;i++) list << QString::number(i);
                                                            monthFrom->addItems(list); monthFrom->hide();
    flay2->addWidget(yearFrom);                             list.clear(); for(int i=2010; i<=QDate::currentDate().year();i++) list << QString::number(i);
                                                            yearFrom->addItems(list); yearFrom->hide();
    flay2->addWidget(headTo);                               headTo->hide();
    flay2->addWidget(dayTo);                                dayTo->hide();
    flay2->addWidget(monthTo);                              list.clear(); for(int i=1; i<=12;i++) list << QString::number(i);
                                                            monthFrom->addItems(list); yearFrom->setCurrentIndex(QDate::currentDate().month()-1); monthTo->hide();
    flay2->addWidget(yearTo);                               list.clear(); for(int i=2010; i<=QDate::currentDate().year();i++) list << QString::number(i);
                                                            yearFrom->addItems(list); yearFrom->setCurrentIndex(yearFrom->count()-1); yearTo->hide();
                                                            dayTo->setCurrentIndex(QDate::currentDate().day()-1);
    mapSelect->clear();                                     list.clear(); list << mapsList;
                                                            mapSelect->addItems(list);

    for(int i=0; i<8; i++)
    {
        sa[i] = new QScrollArea();
        mapxHlay[i] = new QWidget();
        QHBoxLayout* hlay = new QHBoxLayout();
        hlay->setSizeConstraint(QLayout::SetMinAndMaxSize);
        mapxHlay[i]->setLayout(hlay);
        mapxHlay[i]->setMaximumSize(settings->basicWidth-150,100000);
        mapxInfo[i] = new TeamMapInfo();
        mapxInfo[i+8] = new TeamMapInfo();
        mapxlay[i] = new QVBoxLayout();
        mapxlay[i+8] = new QVBoxLayout();
        mapxlay[i]->addWidget(mapxInfo[i]);
        mapxlay[i]->addStretch(1);
        mapxlay[i+8]->addWidget(mapxInfo[i+8]);
        mapxlay[i+8]->addStretch(1);
        hlay->addLayout(mapxlay[i]);
        hlay->addStretch(1);
        hlay->addLayout(mapxlay[i+8]);
        mapxHlay[i]->setLayout(hlay);
        sa[i]->setWidget(mapxHlay[i]);
        sa[i]->hide();
        //maplay->addWidget(mapxHlay[i]);
    }

    QHBoxLayout *xlay = new QHBoxLayout();
    xlay->addLayout(team1lay);
    xlay->addStretch(1);
    xlay->addLayout(team2lay);

    flay->addLayout(flay1);
    flay->addLayout(flay2);
    flay->addWidget(filter);

    QVBoxLayout* lay = new QVBoxLayout();

    //maplay->setSizeConstraint(QLayout::SetMinAndMaxSize);
    //container->setLayout(maplay);
    //container->setMaximumSize(settings->basicWidth-150,100000);

    lay->addLayout(flay);
    lay->addLayout(xlay);
    lay->addWidget(mapSelect);
    //lay->addWidget(sa);                                     sa->setFixedSize(settings->basicWidth-25,settings->scrollAreaHeight);
    for(int i=0; i<8; i++)
    {
        lay->addWidget(sa[i]);
        sa[i]->setFixedHeight(settings->scrollAreaHeight);
    }
    lay->addStretch(1);
    lay->addWidget(back);
    setLayout(lay);
    setFixedSize(settings->basicWidth, settings->basicHeight);

    mapSelect->setCurrentIndex(0);
    load();
}

void MatchInfo::createPage()
{
    disconnect(page,SIGNAL(loadFinished(bool)),this,SLOT(isLoaded()));
    page->deleteLater();
    page = new QWebEnginePage(this);
    connect(page,SIGNAL(loadFinished(bool)),this,SLOT(isLoaded()));
}

void MatchInfo::timeFilterChanged(int i)
{
    if(i==1)
    {
        headFrom->show();
        dayFrom->show();
        monthFrom->show();
        yearFrom->show();
        headTo->show();
        dayTo->show();
        monthTo->show();
        yearTo->show();
    }
    else
    {
        headFrom->hide();
        dayFrom->hide();
        monthFrom->hide();
        yearFrom->hide();
        headTo->hide();
        dayTo->hide();
        monthTo->hide();
        yearTo->hide();
    }
}

QString MatchInfo::createFilter()
{
    QString filt = ""; int i = rankingFilter->currentIndex();
    QString str;

    if(minPlayers->currentIndex()>0) filt += "&" + playersFilters[minPlayers->currentIndex()];

    if(timeFilter->currentText()=="Custom")
    {
        str.clear();

        filt += "&" + str;
    }
    else if(timeFilter->currentText()=="Last month")
    {
        str.clear();
        str += "startDate=" + QDate::currentDate().addMonths(-1).toString("yyyy-MM-dd");
        str += "&endDate=" + QDate::currentDate().toString("yyyy-MM-dd");
        filt += "&" + str;
    }
    else if(timeFilter->currentText()=="Last 2 month")
    {
        str.clear();
        str += "startDate=" + QDate::currentDate().addMonths(-2).toString("yyyy-MM-dd");
        str += "&endDate=" + QDate::currentDate().toString("yyyy-MM-dd");
        filt += "&" + str;
    }
    else if(timeFilter->currentText()=="Last 3 month")
    {
        str.clear();
        str += "startDate=" + QDate::currentDate().addMonths(-3).toString("yyyy-MM-dd");
        str += "&endDate=" + QDate::currentDate().toString("yyyy-MM-dd");
        filt += "&" + str;
    }
    else if(timeFilter->currentText()=="Last 6 month")
    {
        str.clear();
        str += "startDate=" + QDate::currentDate().addMonths(-6).toString("yyyy-MM-dd");
        str += "&endDate=" + QDate::currentDate().toString("yyyy-MM-dd");
        filt += "&" + str;
    }

    if(matchFilter->currentText()=="Last year")
    {
        str.clear();
        str += "startDate=" + QDate::currentDate().addMonths(-12).toString("yyyy-MM-dd");
        str += "&endDate=" + QDate::currentDate().toString("yyyy-MM-dd");
        filt += "&" + str;
    }

    if(matchFilter->currentIndex()>0) filt += "&" + matchFilters[minPlayers->currentIndex()];

    if(rankingFilter->currentIndex()>0) filt += "&" + rankingFilters[minPlayers->currentIndex()];

    actFilter = filt;
    return filt;
}

void MatchInfo::parse(QString html)
{
    HtmlParse parser;

    QString str = parser.cutAfter(html,"standard-box teamsBox",1,1), filt = actFilter; filt[0]='?';
    if(firstStatLoad)
    {
        info1 = new TeamInfo(settings->basicUrl + "/stats/teams/" + parser.cutUrlSection(parser.findAdress(str),2) + "/" + parser.findText(str,"div","teamName",1),actFilter);
        info2 = new TeamInfo(settings->basicUrl + "/stats/teams/" + parser.cutUrlSection(parser.findAdress(str,3),2) + "/" + parser.findText(str,"div","teamName",2),actFilter);
        team1lay->addWidget(info1);
        team2lay->addWidget(info2);
        connect(info1,SIGNAL(lineupFilter(QString)),this,SLOT(infoLoaded1(QString)));
        connect(info2,SIGNAL(lineupFilter(QString)),this,SLOT(infoLoaded2(QString)));
        firstStatLoad = false;
    }

    createPage();
}

void MatchInfo::entFromMonth(int i)
{
    QStringList list;
    for(int i=1; i<= QDate(2000,i+1,1).daysInMonth(); i++)
    {
        list << QString((i<10) ? ("0" + QString::number(i)) : (QString::number(i)));
    }
    dayFrom->addItems(list);
}

void MatchInfo::entToMonth(int i)
{
    QStringList list;
    for(int i=1; i<= QDate(2000,i+1,1).daysInMonth(); i++)
    {
        list << QString((i<10) ? ("0" + QString::number(i)) : (QString::number(i)));
    }
    dayTo->addItems(list);
}

void MatchInfo::reFilter()
{
    createFilter();
    info1->reFilter(actFilter);
    info2->reFilter(actFilter);
    for(int i=0; i<8; i++)
    {
        mapxInfo[i]->reFilter(lineup1 + actFilter);
        mapxInfo[i+8]->reFilter(lineup2 + actFilter);
    }
}

void MatchInfo::reMap(int j)
{
    for(int i=0; i<8; i++)
    {
        if(i==j)
        {
            if(lineup1 != "empty")
            {
                if(!mapxInfo[i]->loading && !mapxInfo[i]->loaded)
                    mapxInfo[i]->init(settings->lineupUrl + mapsUrlList[i],lineup1 + actFilter,team1name,mapsList[i],settings->basicCatalog + mapsIconList[i]);
            }
            if(lineup2 != "empty")
            {
                if(!mapxInfo[i+8]->loading && !mapxInfo[i+8]->loaded)
                    mapxInfo[i+8]->init(settings->lineupUrl + mapsUrlList[i],lineup2 + actFilter,team2name,mapsList[i],settings->basicCatalog + mapsIconList[i]);
            }
            sa[i]->show();
        }
        else
        {
            sa[i]->hide();
        }
    }
}

void MatchInfo::load()
{
    webQueue->addPage(page,baseurl + createFilter());
    //page->load(QUrl(baseurl + createFilter()));
}

void MatchInfo::isLoaded()
{
    page->toHtml([this](const QString& result){
         parse(result);
    });
}

void MatchInfo::closing()
{
    emit closed();
    //page->deleteLater();
    //delete(settings);
}

void MatchInfo::infoLoaded1(QString lineupFilter)
{
    lineup1 = lineupFilter;
    team1name = info1->teamName->text();
    reMap(mapSelect->currentIndex());
}

void MatchInfo::infoLoaded2(QString lineupFilter)
{
    lineup2 = lineupFilter;
    team2name = info2->teamName->text();
    reMap(mapSelect->currentIndex());
}
