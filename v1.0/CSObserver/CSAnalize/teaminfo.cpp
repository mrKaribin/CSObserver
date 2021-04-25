#include "teaminfo.h"

extern WebPageQueue *webQueue;

mapStat::mapStat(QString url, QString tname)
{
    connect(page,SIGNAL(loadFinished(bool)),this,SLOT(isLoaded()));
    if(settings->defaultFull) connect(full,SIGNAL(clicked()),this,SLOT(openFull()));
    else connect(full,SIGNAL(clicked()),this,SLOT(openDemo()));

    for(int i=0; i<30; i++)
    {
        roundTopIcon[i] = new QLabel();
        roundBotIcon[i] = new QLabel();
    }
    baseurl = url;
    teamName = tname;

    createFull();
    createDemo();
    lay->addWidget(wgtFull);
    lay->addWidget(wgtDemo);
    lay->addStretch(1);
    lay->addWidget(full); full->setMaximumSize(settings->buttHeight,settings->roundsHeight); full->resize(settings->buttHeight,settings->roundsHeight);
    setLayout(lay);
    setMaximumSize(settings->sectionWidth,settings->roundsHeight);

    settings->defaultFull ? openFull() : openDemo();

    load();
    //qDebug() << url << endl;
}

void mapStat::createFull()
{
    QLabel* lbl1 = new QLabel("|"), *lbl2 = new QLabel("|"), *hd1 = new QLabel("T1"), *hd2 = new QLabel("T2");

    hd1->setFixedSize(settings->picSize*2,settings->picSize); layTop->setMargin(0); layTop->setSpacing(3);
    hd2->setFixedSize(settings->picSize*2,settings->picSize); layBot->setMargin(0); layBot->setSpacing(3);

    layTop->addWidget(hd1);
    layBot->addWidget(hd2);

    for(int i=0; i<30; i++)
    {
        if(i==15)
        {
            layTop->addWidget(lbl1);            lbl1->setFixedSize(settings->picSize/2,settings->picSize); lbl1->setAlignment(Qt::AlignCenter);
            layBot->addWidget(lbl2);            lbl2->setFixedSize(settings->picSize/2,settings->picSize); lbl2->setAlignment(Qt::AlignCenter);
        }
        layTop->addWidget(roundTopIcon[i]);     roundTopIcon[i]->setFixedSize(settings->picSize,settings->picSize);
        layBot->addWidget(roundBotIcon[i]);     roundBotIcon[i]->setFixedSize(settings->picSize,settings->picSize);
    }

    layHead->addStretch(1);
    layHead->addWidget(team1Head);
    layHead->addStretch(1);
    layHead->addWidget(new QLabel("    vs    "));
    layHead->addStretch(1);
    layHead->addWidget(team2Head);
    layHead->addStretch(1);

    layRounds->addLayout(layHead);              layRounds->setMargin(1); layRounds->setSpacing(1);
    layRounds->addLayout(layTop);
    layRounds->addLayout(layBot);

    layFull->addLayout(layRounds);              layFull->setMargin(1); layFull->setSpacing(5);
    wgtFull->setLayout(layFull);
}

void mapStat::createDemo()
{
                                                layDemo->setMargin(0);layDemo->setSpacing(8);
    QHBoxLayout* lay1 = new QHBoxLayout();      lay1->setMargin(0); lay1->setSpacing(5);

    layDemo->addWidget(date);                   //date->setFixedSize(settings->sectionWidth*0.2,settings->roundsHeight/3);
    layDemo->addWidget(opponent);               opponent->setFixedSize(settings->sectionWidth*0.2,settings->roundsHeight/3);
    layDemo->addWidget(tournament);             tournament->setFixedSize(settings->sectionWidth*0.28,settings->roundsHeight/3);

    lay1->addWidget(round1Ic);                  round1Ic->setFixedSize(settings->roundsHeight*iconCoef,settings->roundsHeight*iconCoef);
    lay1->addWidget(round16Ic);                 round16Ic->setFixedSize(settings->roundsHeight*iconCoef,settings->roundsHeight*iconCoef);
    lay1->addWidget(results);                   results->setFixedSize(settings->sectionWidth*0.08,settings->roundsHeight/3);
    QWidget *wgt = new QWidget();               results->setAlignment(Qt::AlignCenter);
    wgt->setLayout(lay1);

    layDemo->addStretch(1);
    layDemo->addWidget(wgt);
    wgtDemo->setLayout(layDemo);
    wgtDemo->setFixedSize(settings->sectionWidth-settings->buttHeight-20, settings->roundsHeight/3);
}

void mapStat::load()
{
    webQueue->addPage(page,baseurl);
    //page->load(QUrl(baseurl));
}

void mapStat::reFilter(QString filt)
{
    filter = filt;
    load();
}

void mapStat::roundEdit(int team, int pos, int res, QString icon)
{
    int* type = (team==1) ? (resTeam1) : (resTeam2);
    QLabel** image = (team==1) ? (roundTopIcon) : (roundBotIcon);
    type[pos] = res;
    image[pos]->setPixmap(QPixmap(icon).scaled(settings->picSize,settings->picSize));
    image[pos]->setFixedSize(settings->picSize,settings->picSize);
    if(pos==0 && team==1) round1Ic->setPixmap(QPixmap(icon).scaled(settings->roundsHeight*iconCoef,settings->roundsHeight*iconCoef));
    if(pos==15 && team==1) round16Ic->setPixmap(QPixmap(icon).scaled(settings->roundsHeight*iconCoef,settings->roundsHeight*iconCoef));
}

void mapStat::roundParse(QString html, int team, int half)
{
    HtmlParse parser; half--;
    for(int f=1; f<=15; f++)
    {
        QString imgName = parser.findImage(html,f);

        if(imgName == "//static.hltv.org/images/scoreboard/emptyHistory.svg")
        {
            roundEdit(team,half*15+f-1,0,defeat);
        }
        else if(imgName == "//static.hltv.org/images/scoreboard/t_win.svg")
        {
            roundEdit(team,half*15+f-1,1,t_win);
        }
        else if(imgName == "//static.hltv.org/images/scoreboard/bomb_exploded.svg")
        {
            roundEdit(team,half*15+f-1,2,bomb_exploded);
        }
        else if(imgName == "//static.hltv.org/images/scoreboard/ct_win.svg")
        {
            roundEdit(team,half*15+f-1,3,ct_win);
        }
        else if(imgName == "//static.hltv.org/images/scoreboard/bomb_defused.svg")
        {
            roundEdit(team,half*15+f-1,4,bomb_defused);
        }
        else if(imgName == "//static.hltv.org/images/scoreboard/stopwatch.svg")
        {
            roundEdit(team,half*15+f-1,5,stopwatch);
        }
    }
}

void mapStat::parse(QString html)
{
    HtmlParse parser;
    QString stat = parser.cutAfter(html,"Round history");
    QString teamName1, teamName2, result, resT1, resT2, opp = ""; bool mres=false; int i=0, j=0, team1=0, team2=0;

    tournament->setText(parser.findText(html,"div","menu-header"));
    date->setText(parser.findText(parser.cutAfterWith(html,"small-text",1,1),"span").split(" ")[0]);

    QString res = parser.cutAfter(html,"match-info-row",1,0);
    result = parser.findField(res,"class",2);
    resT1 = parser.findText(res,"span",1);
    resT2 = parser.findText(res,"span",2);

    teamName1 = parser.findField(parser.cutAfter(stat,"round-history-team",2,0),"title");
    teamName2 = parser.findField(parser.cutAfter(stat,"round-history-team",4,0),"title");
    if(teamName1==teamName){
        if(result=="won") mres = true;
        if(result=="lost") mres = false;
        results->setText(resT1 + ":" + resT2);
        team1Head->setText(teamName1 + " (T1)");
        team2Head->setText(teamName2 + " (T2)");
        opp += teamName2;
        team1 = 1;
        team2 = 2;
    }
    else if(teamName=="empty"){
        if(result=="won") mres = true;
        if(result=="lost") mres = false;
        team1Head->setText(teamName1 + " (T1)");
        team2Head->setText(teamName2 + " (T2)");
        opp += teamName2;
        team1 = 1;
        team2 = 2;
    }
    else {
        if(result=="won") mres = false;
        if(result=="lost") mres = true;
        results->setText(resT2 + ":" + resT1);
        team1Head->setText(teamName2 + " (T1)");
        team2Head->setText(teamName1 + " (T2)");
        opp += teamName1;
        team1 = 2;
        team2 = 1;
    }

    opponent->setText(opp);
    if(mres) full->setStyleSheet(QString::fromUtf8("background-color: rgb(124, 252, 0);"));
    else full->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 128, 128);"));

    i = stat.indexOf("round-history-half")+18; j = stat.indexOf("</div>",i);
    roundParse(stat.mid(i,j-i),team1,1);

    i = stat.indexOf("round-history-half",i)+18; j = stat.indexOf("</div>",i);
    roundParse(stat.mid(i,j-i),team1,2);

    i = stat.indexOf("round-history-half",i)+18; j = stat.indexOf("</div>",i);
    roundParse(stat.mid(i,j-i),team2,1);

    i = stat.indexOf("round-history-half",i)+18; j = stat.indexOf("</div>",i);
    roundParse(stat.mid(i,j-i),team2,2);

    createPage();
}

void mapStat::createPage()
{
    disconnect(page,SIGNAL(loadFinished(bool)),this,SLOT(isLoaded()));
    page->deleteLater();
    page = new QWebEnginePage(this);
    connect(page,SIGNAL(loadFinished(bool)),this,SLOT(isLoaded()));
}

void mapStat::isLoaded()
{
    page->toHtml([this](const QString& result){
         parse(result);
    });
}

void mapStat::openFull()
{
    wgtDemo->hide();
    wgtFull->show();
    full->setText("<");
    setFixedSize(settings->sectionWidth,settings->roundsHeight/1.3);
    disconnect(full,SIGNAL(clicked()),this,SLOT(openFull()));
    connect(full,SIGNAL(clicked()),this,SLOT(openDemo()));
}

void mapStat::openDemo()
{
    wgtFull->hide();
    wgtDemo->show();
    full->setText(">");
    setFixedSize(settings->sectionWidth,settings->roundsHeight/2);
    disconnect(full,SIGNAL(clicked()),this,SLOT(openDemo()));
    connect(full,SIGNAL(clicked()),this,SLOT(openFull()));
}

TeamMapInfo::TeamMapInfo()
{
    interfaseCreate();
}

TeamMapInfo::TeamMapInfo(QString url, QString filt, QString tname, QString mname, QString icon)
{
    interfaseCreate();
    init(url,filt,tname,mname,icon);
}

void TeamMapInfo::interfaseCreate()
{
    connect(page,SIGNAL(loadFinished(bool)),this,SLOT(isLoaded()));

    header->setAutoFillBackground(true);
    header->setFixedSize(settings->sectionWidth,(int)settings->sectionWidth*0.1);
    header->setAlignment(Qt::AlignCenter);
    header->setStyleSheet("color: rgb(255, 230, 230)");
    QFont f = header->font(); f.setPixelSize(settings->headTextSize);
    header->setFont(f);
    lay->addWidget(header);
    lay->addWidget(matchStat);
    lay->addWidget(matches);
    lay->addWidget(roundsStat);
    lay->addWidget(pistolStat);
    setLayout(lay);
    resize(settings->sectionWidth,settings->sectionWidth/2);
}

void TeamMapInfo::init(QString url, QString filt, QString tname, QString mname, QString icon)
{
    if(loading) return;

    mapurl = url;
    filter = filt;
    teamName = tname;

    header->setText(mname);
    QImage img(icon);
    QPalette pal;
    pal.setBrush(backgroundRole(),QBrush(QPixmap::fromImage(img.scaled(settings->sectionWidth,(int)settings->sectionWidth*0.1))));
    header->setPalette(pal);

    initialized = true;
    load();
}

void TeamMapInfo::parse(QString html)
{
    HtmlParse parser;
    matchStat->setText("Выиграли матчей: " + parser.cutAfterAndFindText(html,"Win percent","span") + " из " + parser.cutAfterAndFindText(html,"Times played","span"));
    matches->setText("Статистика: " + parser.cutAfterAndFindText(html,"Wins / draws / losses","span"));
    roundsStat->setText("Выиграли раундов: " + parser.cutAfterAndFindText(html,"Rounds won","span") + " из " + parser.cutAfterAndFindText(html,"Total rounds played","span"));
    pistolStat->setText("Выиграли пистолеток: " + parser.cutAfterAndFindText(html,"Pistol round win percent","span") + " из " + parser.cutAfterAndFindText(html,"Pistol rounds","span"));

    lay->removeItem(rlay);
    for(int i=0; i<maps.size(); i++) maps[i]->deleteLater();
    rlay = new QVBoxLayout();
    lay->addLayout(rlay);

    QString matches = parser.cutAfter(html,">Matches</span>",1,2); int i=-1; int j=1; QString key = "time";
    while(true)
    {
        i = matches.indexOf(key,i+1);
        if(i!=-1)
        {
            QString adr = parser.cutAfter(matches,key,j,0);

            mapStat *map = new mapStat(settings->basicUrl + parser.findAdress(adr),teamName);
            maps << map;
            rlay->addWidget(map);
            map->show();
            j++;
        }
        else break;
    }

    setLayout(lay);
    createPage();
    loading = false;
    loaded = true;
}

void TeamMapInfo::createPage()
{
    disconnect(page,SIGNAL(loadFinished(bool)),this,SLOT(isLoaded()));
    page->deleteLater();
    page = new QWebEnginePage(this);
    connect(page,SIGNAL(loadFinished(bool)),this,SLOT(isLoaded()));
}

void TeamMapInfo::load()
{
    loading = true;
    webQueue->addPage(page,mapurl + filter);
    //page->load(QUrl(mapurl + filter));
}

void TeamMapInfo::reFilter(QString filt)
{
    if(!initialized) return;
    filter = filt;
    load();
}

void TeamMapInfo::isLoaded()
{
    page->toHtml([this](const QString& result){
        parse(result);
    });
}

TeamInfo::TeamInfo(QString url, QString filt)
{
    connect(page,SIGNAL(loadFinished(bool)),this,SLOT(isLoaded()));

    baseurl = url;
    filt[0]='?';
    filter = filt;

    QHBoxLayout* prlay = new QHBoxLayout();                 prlay->setMargin(5); prlay->setSpacing(1);
    QVBoxLayout* pr1lay = new QVBoxLayout();                pr1lay->setMargin(5); pr1lay->setSpacing(1);
    QVBoxLayout* pr2lay = new QVBoxLayout();                pr2lay->setMargin(5); pr2lay->setSpacing(1);
    QVBoxLayout* pr3lay = new QVBoxLayout();                pr3lay->setMargin(5); pr3lay->setSpacing(1);
    QVBoxLayout* pr4lay = new QVBoxLayout();                pr4lay->setMargin(5); pr4lay->setSpacing(1);
    QVBoxLayout* pr5lay = new QVBoxLayout();                pr5lay->setMargin(5); pr5lay->setSpacing(1);
    lay->setMargin(5); lay->setSpacing(15);

    for(int i=0; i<5; i++)
    {
        Player player;
        players << player;
    }

    pr1lay->addWidget(players[0].photo);
    pr1lay->addWidget(players[0].nick);                     players[0].nick->setAlignment(Qt::AlignCenter);
    pr2lay->addWidget(players[1].photo);
    pr2lay->addWidget(players[1].nick);                     players[1].nick->setAlignment(Qt::AlignCenter);
    pr3lay->addWidget(players[2].photo);
    pr3lay->addWidget(players[2].nick);                     players[2].nick->setAlignment(Qt::AlignCenter);
    pr4lay->addWidget(players[3].photo);
    pr4lay->addWidget(players[3].nick);                     players[3].nick->setAlignment(Qt::AlignCenter);
    pr5lay->addWidget(players[4].photo);
    pr5lay->addWidget(players[4].nick);                     players[4].nick->setAlignment(Qt::AlignCenter);
    prlay->addLayout(pr1lay);
    prlay->addLayout(pr2lay);
    prlay->addLayout(pr3lay);
    prlay->addLayout(pr4lay);
    prlay->addLayout(pr5lay);

    lay->addWidget(teamName);                               teamName->setAlignment(Qt::AlignCenter);
                                                            QFont f = teamName->font(); f.setPixelSize(settings->headTextSize); teamName->setFont(f);
    lay->addStretch(1);
    lay->addWidget(winStat);
    lay->addWidget(kdaStat);
    lay->addStretch(1);
    lay->addLayout(prlay);
    setLayout(lay);
    setFixedSize(settings->sectionWidth,settings->mapStatHeight);

    load();
}

void TeamInfo::parse(QString html)
{
    HtmlParse parser;
    QString fltr="";

    teamName->setText(parser.findText(parser.cutAfter(html,"Team context",1,1),"span","context-item-name"));
    winStat->setText("Статистика по " + parser.findText(html,"div","large-strong",1) + " матчам: " + parser.findText(html,"div","large-strong",2));
    kdaStat->setText("K/D показатель: " + parser.findText(html,"div","large-strong",6) + " (" + parser.findText(html,"div","large-strong",3) + "/" + parser.findText(html,"div","large-strong",4) + ")");

    for(int i=0; i<5; i++)
    {
        QString peace = parser.cutAfter(html,"col teammate",i+1,0);
        players[i].name = peace.mid(peace.indexOf("alt=")+5,peace.indexOf('"',peace.indexOf("alt=")+7)-peace.indexOf("alt=")+5);
        players[i].nick->setText(parser.findText(peace,"div","text-ellipsis"));
        players[i].url = parser.findAdress(peace);
        players[i].photoUrl = parser.findImage(peace);
        fltr += "&lineup=" + parser.cutUrlSection(players[i].url,3);
    }
    fltr[0]='?';
    emit lineupFilter(fltr);
    createPage();
}

void TeamInfo::createPage()
{
    disconnect(page,SIGNAL(loadFinished(bool)),this,SLOT(isLoaded()));
    page->deleteLater();
    page = new QWebEnginePage(this);
    connect(page,SIGNAL(loadFinished(bool)),this,SLOT(isLoaded()));
}

QString TeamInfo::currentLineupFilter()
{
    QString filt;

    return filt;
}

void TeamInfo::load()
{
    webQueue->addPage(page,baseurl + filter);
    //page->load(QUrl(baseurl + filter));
}

void TeamInfo::reFilter(QString filt)
{
    filter = filt;
    load();
}

void TeamInfo::isLoaded()
{
    page->toHtml([this](const QString& result){
         parse(result);
    });
}
