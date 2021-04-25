#include "delphinosyncro.h"
#include "matches.h"

KeyWidget::KeyWidget(QString _key, QString _product, QString _license)
{
    if(_license != "empty" && _license != "over")
        license(true);
    else
        license(false);

    key = _key;
    product = _product;
    QIcon icon;
    key_label->setText(key);
    product_label->setText(product);
    //icon.addPixmap(QPixmap(destroyIcon).scaled(iconSize,iconSize));
    icon = QIcon(destroyIcon);
    destroy->setIcon(icon);
    destroy->setIconSize(QSize(iconSize,iconSize));
    //icon.addPixmap(QPixmap(activityIcon1).scaled(iconSize,iconSize));
    icon = QIcon(activityIcon1);
    activity->setIcon(icon);
    activity->setIconSize(QSize(iconSize,iconSize));

    QHBoxLayout* lay = new QHBoxLayout();
    lay->addWidget(product_label);
    lay->addWidget(key_label);
    lay->addStretch(1);
    lay->addWidget(activity);
    lay->addWidget(destroy);
    setLayout(lay);
    if(!licensed) activity->hide();

    connect(destroy,SIGNAL(clicked()),this,SLOT(destroyClicked()));
    connect(activity,SIGNAL(clicked()),this,SLOT(activityClicked()));
}

bool KeyWidget::isActive()
{
    return activated;
}

bool KeyWidget::isLicensed()
{
    return licensed;
}

void KeyWidget::active(bool is)
{
    QIcon icon;
    if(!is){
        icon.addPixmap(QPixmap(activityIcon1).scaled(iconSize,iconSize));
        activity->setIcon(icon);
    }
    else if(is){
        icon.addPixmap(QPixmap(activityIcon2).scaled(iconSize,iconSize));
        activity->setIcon(icon);
    }
    activated = is;
}

void KeyWidget::license(bool is)
{
    if(is)
        activity->show();
    else
        activity->hide();
    licensed = is;
}

void KeyWidget::productDestroyed()
{
    emit destroyedThis(product);
}

void KeyWidget::destroyClicked()
{
    emit destroyThis(key);
}

void KeyWidget::activityClicked()
{
    if(!activated)
    {
        emit turnOn(product);
    }
    else
    {
        emit turnOff(product);
    }
}

Delphinosyncro::Delphinosyncro()
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    setMouseTracking(true);
    setWindowTitle("Delphino Launcher");

    screen_width = QApplication::desktop()->screenGeometry(0).width();
    screen_height = QApplication::desktop()->screenGeometry(0).height();

    QAction* actionShowHide = new QAction("Свернуть/Развернуть",this);
    QAction* actionClose = new QAction("Выйти",this);
    trayMenu->addAction(actionShowHide);
    trayMenu->addAction(actionClose);

    QIcon icon(logoAdr);
    trayIcon->setIcon(icon);
    trayIcon->setContextMenu(trayMenu);
    trayIcon->show();
    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(trayIconClicked(QSystemTrayIcon::ActivationReason)));
    connect(actionShowHide,SIGNAL(triggered()),this,SLOT(launcherShowHide()));
    connect(actionClose,SIGNAL(triggered()),this,SLOT(closeLauncher()));

    QVBoxLayout* loadlay = new QVBoxLayout();
    QHBoxLayout* loadhlay = new QHBoxLayout();
    QHBoxLayout* loadh2lay = new QHBoxLayout();
    QHBoxLayout* loadh3lay = new QHBoxLayout();
    QHBoxLayout* loadh4lay = new QHBoxLayout();
    QLabel* logo = new QLabel();
    logo->setPixmap(QPixmap(logoAdr).scaled(80,80));
    QLabel* name = new QLabel("Delphino");

    QFont f = name->font(); f.setPixelSize(16); name->setFont(f);
    f = loadInfo->font(); f.setPixelSize(11); loadInfo->setFont(f);
    f = loadAlarmInfo->font(); f.setPixelSize(9); loadAlarmInfo->setFont(f);
    loadAlarmInfo->setStyleSheet("color: rgb(255, 43, 43)");


    loadhlay->addWidget(logo);
    loadhlay->addWidget(name);
    loadh2lay->addStretch(1);
    loadh2lay->addLayout(loadhlay);
    loadh2lay->addStretch(1);
    loadh3lay->addStretch(1);
    loadh3lay->addWidget(loadInfo);
    loadh3lay->addStretch(1);
    loadh4lay->addStretch(1);
    loadh4lay->addWidget(loadAlarmInfo);
    loadh4lay->addStretch(1);
    loadlay->setAlignment(Qt::AlignCenter);
    loadlay->addLayout(loadh2lay);
    loadlay->addLayout(loadh3lay);
    loadlay->addLayout(loadh4lay);
    loading->setLayout(loadlay);
    loading->resize(ww,wh);
    loading->move(-ww - 20, -wh - 20);


    QVBoxLayout* keylay = new QVBoxLayout();
    QVBoxLayout* keyvlay1 = new QVBoxLayout();
    QHBoxLayout* keyhlay1 = new QHBoxLayout();
    keyvlay1->setAlignment(Qt::AlignCenter);
    QLabel* keyhead = new QLabel("Активация");
    QLabel* sphead = new QLabel("Введите код активации");
    QPushButton* act = new QPushButton("Активировать");
    QPushButton* aut = new QPushButton("Авторизация");
    QPushButton* kmain = new QPushButton("Главная");

    connect(act,SIGNAL(clicked()),this,SLOT(activating()));
    connect(aut,SIGNAL(clicked()),this,SLOT(openLoginSpace()));
    connect(kmain,SIGNAL(clicked()),this,SLOT(openMainSpace()));

    f = keyhead->font(); f.setPixelSize(18); keyhead->setFont(f);
    f = sphead->font(); f.setPixelSize(10); sphead->setFont(f);

    keyhlay1->addWidget(kmain);
    keyhlay1->addStretch(1);
    keyhlay1->addWidget(aut);
    keyhlay1->addStretch(1);
    keyhlay1->addWidget(act);
    keyvlay1->addWidget(keyhead);
    keyvlay1->addWidget(sphead);
    keyvlay1->addWidget(key);
    keylay->addLayout(keyvlay1);
    keylay->addLayout(keyhlay1);
    keyspace->setLayout(keylay);
    keyspace->resize(ww,wh);
    keyspace->move(-ww - 20, -wh - 20);


    QVBoxLayout* loginlay = new QVBoxLayout();
    QVBoxLayout* loginvlay = new QVBoxLayout();
    QHBoxLayout* loginhlay1 = new QHBoxLayout();
    QHBoxLayout* loginhlay2 = new QHBoxLayout();
    QHBoxLayout* loginhlay3 = new QHBoxLayout();
    loginvlay->setAlignment(Qt::AlignCenter);
    QLabel* loghead = new QLabel("Авторизация");
    QLabel* logsphead1 = new QLabel("Введите логин:");
    QLabel* logsphead2 = new QLabel("Введите пароль:");
    QPushButton* log = new QPushButton("Войти");
    QPushButton* reg = new QPushButton("Регистрация");
    QPushButton* back = new QPushButton("Главная");

    connect(log,SIGNAL(clicked()),this,SLOT(logining()));
    connect(reg,SIGNAL(clicked()),this,SLOT(openRegistrationSpace()));
    connect(back,SIGNAL(clicked()),this,SLOT(openMainSpace()));

    f = loghead->font(); f.setPixelSize(18); loghead->setFont(f);
    f = logsphead1->font(); f.setPixelSize(10); logsphead1->setFont(f);
    f = logsphead2->font(); f.setPixelSize(10); logsphead2->setFont(f);

    loginhlay1->addWidget(logsphead1);
    loginhlay1->addWidget(login);
    loginhlay2->addWidget(logsphead2);
    loginhlay2->addWidget(password);
    loginhlay3->addWidget(back);
    loginhlay3->addStretch(1);
    loginhlay3->addWidget(reg);
    loginhlay3->addStretch(1);
    loginhlay3->addWidget(log);
    loginvlay->addWidget(loghead);
    loginvlay->addLayout(loginhlay1);
    loginvlay->addLayout(loginhlay2);
    loginlay->addLayout(loginvlay);
    loginlay->addLayout(loginhlay3);
    loginspase->setLayout(loginlay);
    loginspase->resize(ww,wh);
    loginspase->move(-ww - 20, -wh - 20);


    QVBoxLayout* reglay = new QVBoxLayout();
    QVBoxLayout* regvlay = new QVBoxLayout();
    QHBoxLayout* reghlay1 = new QHBoxLayout();
    QHBoxLayout* reghlay2 = new QHBoxLayout();
    QHBoxLayout* reghlay3 = new QHBoxLayout();
    QHBoxLayout* reghlay4 = new QHBoxLayout();
    regvlay->setAlignment(Qt::AlignCenter);
    QLabel* reghead = new QLabel("Регистрация");
    QLabel* regsphead1 = new QLabel("Введите логин:");
    QLabel* regsphead2 = new QLabel("Введите пароль:");
    QLabel* regsphead3 = new QLabel("Введите email:");
    QPushButton* registr = new QPushButton("Регистрация");
    QPushButton* entry = new QPushButton("Войти");
    QPushButton* main = new QPushButton("Главная");

    connect(registr,SIGNAL(clicked()),this,SLOT(registration()));
    connect(entry,SIGNAL(clicked()),this,SLOT(openLoginSpace()));
    connect(main,SIGNAL(clicked()),this,SLOT(openMainSpace()));

    f = reghead->font(); f.setPixelSize(18); reghead->setFont(f);
    f = regsphead1->font(); f.setPixelSize(10); regsphead1->setFont(f);
    f = regsphead2->font(); f.setPixelSize(10); regsphead2->setFont(f);
    f = regsphead3->font(); f.setPixelSize(10); regsphead3->setFont(f);

    reghlay1->addWidget(regsphead1);
    reghlay1->addWidget(newlogin);
    reghlay2->addWidget(regsphead2);
    reghlay2->addWidget(newpassword);
    reghlay3->addWidget(regsphead3);
    reghlay3->addWidget(newemail);
    reghlay4->addWidget(main);
    reghlay4->addStretch(1);
    reghlay4->addWidget(entry);
    reghlay4->addStretch(1);
    reghlay4->addWidget(registr);
    regvlay->addWidget(reghead);
    regvlay->addLayout(reghlay1);
    regvlay->addLayout(reghlay2);
    regvlay->addLayout(reghlay3);
    reglay->addLayout(regvlay);
    reglay->addLayout(reghlay4);
    registrationspace->setLayout(reglay);
    registrationspace->resize(ww,wh);
    registrationspace->move(-ww - 20, -wh - 20);


    QVBoxLayout* mainlay = new QVBoxLayout();
    QWidget* accwgt = new QWidget();
    QWidget* keywgt = new QWidget();
    QVBoxLayout* mainvlay1 = new QVBoxLayout();
    QVBoxLayout* mainvlay2 = new QVBoxLayout();
    QHBoxLayout* mainhlay1 = new QHBoxLayout();
    QHBoxLayout* mainhlay2 = new QHBoxLayout();
    QHBoxLayout* mainhlay3 = new QHBoxLayout();
    QHBoxLayout* mainhlay4 = new QHBoxLayout();
    QHBoxLayout* mainhlay5 = new QHBoxLayout();
    QLabel* mainhead1 = new QLabel("Мой аккаунт");
    QLabel* mainhead2 = new QLabel("Лицензионные ключи");
    QPushButton* activate = new QPushButton("Запустить все");
    QPushButton* license = new QPushButton("Обновить ключи");
    QPushButton* hide = new QPushButton();
    QPushButton* close = new QPushButton();

    connect(accEdit,SIGNAL(clicked()),this,SLOT(openLoginSpace()));
    connect(keyEdit,SIGNAL(clicked()),this,SLOT(openKeySpace()));
    connect(atrun,SIGNAL(stateChanged(int)),this,SLOT(isAutorun(int)));
    connect(activate,SIGNAL(clicked()),this,SLOT(runAll()));
    connect(license,SIGNAL(clicked()),this,SLOT(activatingAll()));
    connect(hide,SIGNAL(clicked()),this,SLOT(launcherShowHide()));
    connect(close,SIGNAL(clicked()),this,SLOT(closeLauncher()));

    hide->setIcon(QIcon(hideIcon));
    hide->setIconSize(QSize(iconSize,iconSize));
    close->setIcon(QIcon(closeIcon));
    close->setIconSize(QSize(iconSize,iconSize));
    mainhlay3->addStretch(1);
    mainhlay3->addWidget(hide);
    mainhlay3->addWidget(close);

    mainhlay1->addWidget(mainsp1head1);
    mainhlay1->addWidget(mainsp1data1);
    mainhlay2->addWidget(mainsp1head2);
    mainhlay2->addWidget(mainsp1data2);
    mainvlay1->addWidget(mainhead1);
    mainvlay1->addLayout(mainhlay1);
    mainvlay1->addLayout(mainhlay2);
    mainvlay1->addWidget(mainsp1head3);
    mainhlay4->addLayout(mainvlay1);
    mainhlay4->addStretch(1);
    mainhlay4->addWidget(accEdit);
    accwgt->setLayout(mainhlay4);

    mainvlay2->addWidget(mainhead2);
    mainvlay2->addLayout(keyslay);
    mainvlay2->addWidget(mainsp2head2);
    mainvlay2->addWidget(keyEdit);
    keywgt->setLayout(mainvlay2);

    mainhlay5->addWidget(atrun);
    mainhlay5->addStretch(1);
    mainhlay5->addWidget(license);
    mainhlay5->addWidget(activate);

    mainlay->addLayout(mainhlay3);
    //mainlay->addStretch(1);
    mainlay->addWidget(accwgt);
    mainlay->addStretch(1);
    mainlay->addWidget(keywgt);
    mainlay->addStretch(1);
    mainlay->addLayout(mainhlay5);
    mainspace->setLayout(mainlay);
    mainspace->resize(ww,wh);
    mainspace->move(-ww - 20, -wh - 20);


    activespace = mainspace;
    wx = (screen_width - ww) / 2;
    wy = (screen_height - wh) / 2;
    setGeometry(wx,wy,ww,wh);
    loading->move(0,0);
    loading->show();
    isLoading = true;

    setStyleSheet("background: rgb(210, 225, 245)");
    //setStyleSheet("button: rgb(100, 150, 250)");
    setStyleSheet("color: rgb(50, 20, 20)");
    show();

    QPropertyAnimation* animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(300);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    while(animation->state() == QPropertyAnimation::Running)
    {
        QApplication::processEvents();
    }


    timer->start(1000);
    loadInfo->setText("Обработка данных...");
    ConnectDatabase();
    ReadDatabase();
    reloadKeysLay();
    loadInfo->setText("Соединение с сервером...");
    socket = new QTcpSocket(this);
    connect(timer, SIGNAL(timeout()), timer, SLOT(stop()));
    connect(exitTimeout, SIGNAL(timeout()), this, SLOT(reconnectTimeout()));
    connect(closeTimeout, SIGNAL(timeout()), this, SLOT(closeLauncher()));
    connect(connectionCheck, SIGNAL(timeout()), this, SLOT(checkConnection()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(hostFound()), this, SLOT(hostFounded()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(reading()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(connectingError(QAbstractSocket::SocketError)));
    socket->connectToHost(host,port);
}

void Delphinosyncro::mousePressEvent(QMouseEvent *ev)
{
    mousePos = ev->pos();
    isPressed = true;
}

void Delphinosyncro::mouseMoveEvent(QMouseEvent *ev)
{
    if(isPressed)
        move(ev->pos()-mousePos+QPoint(QWidget::x(),QWidget::y()));
}

void Delphinosyncro::mouseReleaseEvent(QMouseEvent *ev)
{
    isPressed = false;
}

void Delphinosyncro::swapToSpace(QWidget *wgt)
{
    QPropertyAnimation* animation1 = new QPropertyAnimation(activespace, "geometry");
    QPropertyAnimation* animation2 = new QPropertyAnimation(wgt, "geometry");

    if(mainspace != activespace) mainspace->move(-ww - 20, -wh - 20);
    if(loginspase != activespace) loginspase->move(-ww - 20, -wh - 20);
    if(registrationspace != activespace) registrationspace->move(-ww - 20, -wh - 20);
    if(keyspace != activespace) keyspace->move(-ww - 20, -wh - 20);

    animation1->setDuration(500);
    animation1->setStartValue(QRect(0, 0, ww, wh));
    animation1->setEndValue(QRect(ww + 50, 0, ww, wh));
    animation2->setDuration(500);
    animation2->setStartValue(QRect(-ww - 50, 0, ww, wh));
    animation2->setEndValue(QRect(0,0,ww,wh));

    animation1->start();
    animation2->start();
    activespace = wgt;
}

void Delphinosyncro::startLoading(QString mess)
{
    QPropertyAnimation* animation1 = new QPropertyAnimation(activespace, "geometry");
    QPropertyAnimation* animation2 = new QPropertyAnimation(loading, "geometry");

    if(mainspace != activespace) mainspace->move(-ww - 20, -wh - 20);
    if(loginspase != activespace) loginspase->move(-ww - 20, -wh - 20);
    if(registrationspace != activespace) registrationspace->move(-ww - 20, -wh - 20);
    if(keyspace != activespace) keyspace->move(-ww - 20, -wh - 20);

    loadInfo->setText(mess);
    animation1->setDuration(500);
    animation1->setStartValue(loading->geometry());
    animation1->setEndValue(QRect(0, wh + 50, ww, wh));
    animation2->setDuration(500);
    animation2->setStartValue(QRect(0, -ww - 50, ww, wh));
    animation2->setEndValue(QRect(0,0,ww,wh));

    animation1->start();
    animation2->start();
    timer->start(1000);
    isLoading = true;
}

void Delphinosyncro::finishLoading()
{
    if(isFirstStart && !myKeyWidget.isEmpty() && autorun)
        launcherShowHide();
    if(!isLoadComplete && timer->isActive())
    {
        isLoadComplete = true;
        connect(timer,SIGNAL(timeout()),this,SLOT(finishLoading()));
    }
    if(timer->isActive())
        return;
    if(isLoadComplete && !timer->isActive())
    {
        isLoadComplete = false;
        disconnect(timer,SIGNAL(timeout()),this,SLOT(finishLoading()));
    }

    QPropertyAnimation* animation1 = new QPropertyAnimation(activespace, "geometry");
    QPropertyAnimation* animation2 = new QPropertyAnimation(loading, "geometry");

    animation1->setDuration(500);
    animation1->setStartValue(QRect(0, wh + 50, ww, wh));
    animation1->setEndValue(QRect(0, 0, ww, wh));
    animation2->setDuration(500);
    animation2->setStartValue(loading->geometry());
    animation2->setEndValue(QRect(0, -wh - 50, ww, wh));

    animation1->start();
    animation2->start();
    isLoading = false;
}

void Delphinosyncro::ConnectDatabase()
{
    base = QSqlDatabase::addDatabase("QSQLITE");
    base.setDatabaseName("delphinobase");
    base.setUserName("user");
    //base.setDatabaseName("server");
    base.setPassword("topsecretpasswordjajajalefrut");
    if(!base.open())
        QMessageBox::critical(0,"Database error","Can not open database: " + base.lastError().text());

    QSqlQuery query;
    QStringList lst = base.tables();
    if(lst.size() == 0 || (lst.size() != 0 && lst[0] != "DATAS"))
    {
        if(!query.exec("CREATE TABLE DATAS (name TEXT, date TEXT)"))
            QMessageBox::critical(0,"Database error","Can not create table: " + base.lastError().text());
    }
}

void Delphinosyncro::ReadDatabase()
{
    QSqlQuery query;
    QSqlRecord rec;

    if(!query.exec("SELECT * FROM DATAS;"))
         QMessageBox::critical(0,"Database error","Can not read datas: " + base.lastError().text());
    rec = query.record();
    while(query.next())
    {
        QString name = query.value(rec.indexOf("name")).toString();
        if(name == "login")
            myLogin = query.value(rec.indexOf("date")).toString();
        else if(name == "password")
            myPassword = query.value(rec.indexOf("date")).toString();
        else if(name == "autorun")
            autorun = query.value(rec.indexOf("date")).toString()=="true" ? true : false;
        else if(name == "key")
        {
            QString str = query.value(rec.indexOf("date")).toString();
            int i = str.indexOf(":");
            addKey(str.mid(0,i));
            editKey(str.mid(0,i),str.mid(i+1,str.size()-i-1),"empty");
        }
    }
    atrun->setCheckState(autorun ? Qt::Checked : Qt::Unchecked);
    if(myKey.size() != 0)
        haveKey(true);
    else
        haveKey(false);
    if(myLogin != "empty" && myPassword != "empty")
        haveAccount(true);
    else
        haveAccount(false);
}

void Delphinosyncro::WriteDate(QString s, QString f)
{
    QSqlQuery query;
    QString str = "INSERT INTO DATAS (name, date) "
                  "VALUES ('%1', '%2');";
    QString res = str.arg(s)
                     .arg(f);
    if(!query.exec(res))
        QMessageBox::critical(0,"Database error","Can not write datas: " + base.lastError().text());

}

void Delphinosyncro::SaveDatabase()
{
    QSqlQuery query;
    if(!query.exec("DELETE FROM DATAS;"))
        QMessageBox::critical(0,"Database error","Can not delete datas: " + base.lastError().text());

    WriteDate("login",myLogin);
    WriteDate("password",myPassword);
    WriteDate("autorun",autorun ? "true" : "false");
    for(int i=0; i<myKey.size(); i++)
        WriteDate("key",myKey[i] + ":" + myProduct[i]);
}

void Delphinosyncro::haveAccount(bool have)
{
    if(have)
    {
        mainsp1head1->show();
        mainsp1data1->show();
        mainsp1head2->show();
        mainsp1data2->show();
        mainsp1head3->hide();
        mainsp1data1->setText(myLogin);
        mainsp1data2->setText(myPassword);
        login->setText(myLogin);
        password->setText(myPassword);
    }
    else
    {
        mainsp1head1->hide();
        mainsp1data1->hide();
        mainsp1head2->hide();
        mainsp1data2->hide();
        mainsp1head3->show();
        myLogin = "empty";
        myPassword = "empty";
        login->setText("");
        password->setText("");
    }
}

void Delphinosyncro::haveKey(bool have)
{
    if(have)
    {
        mainsp2head2->hide();
        reloadKeysLay();
    }
    else
    {
        mainsp2head2->show();
        reloadKeysLay();
    }
}

void Delphinosyncro::reloadKeysLay()
{
    QStringList keys = myKey;
    QStringList prods = myProduct;
    QStringList lics = myLicense;
    QVector <KeyWidget*> widgets = myKeyWidget;
    for(int j=0; j<widgets.size(); j++)
    {
        bool ok = false;
        for(int i=0; i<keys.size(); i++)
        {
            if(widgets[j]->key.compare(keys[i]) == 0 && widgets[j]->product.compare(prods[i]) == 0)
            {
                ok = true;
                if(lics[i] != "empty" && lics[i] != "over")
                    widgets[j]->license(true);
                else
                    widgets[j]->license(false);
                keys.removeAt(i);
                prods.removeAt(i);
                lics.removeAt(i);
                widgets.remove(j);
                break;
            }
        }
        if(!ok)
        {
            for(int i=0; i<keyslay->count(); i++)
            {
                QLayoutItem* item = keyslay->itemAt(i);
                if(item->widget() == widgets[j])
                {
                    item->widget()->hide();
                    keyslay->removeItem(item);
                    keyslay->removeWidget(item->widget());
                    for(int k=0; k<myKeyWidget.size(); k++)
                    {
                        if(widgets[j]->key.compare(myKeyWidget[k]->key) == 0)
                        {
                            if(myKeyWidget[k]->isActive()) myKeyWidget[k]->activityClicked();
                            myKeyWidget[k]->deleteLater();
                            myKeyWidget.remove(k);
                        }
                    }
                    delete item;
                    keyslay->update();
                }
            }
        }
    }
    for(int i=0; i<keys.size(); i++)
    {
        KeyWidget* wgt = new KeyWidget(myKey[i],myProduct[i],myLicense[i]);
        keyslay->addWidget(wgt);
        keyslay->update();
        myKeyWidget << wgt;
        connect(wgt,SIGNAL(destroyThis(QString)),this,SLOT(deleteKey(QString)));
        connect(wgt,SIGNAL(turnOn(QString)),this,SLOT(turnOnProduct(QString)));
        connect(wgt,SIGNAL(turnOff(QString)),this,SLOT(turnOffProduct(QString)));
        connect(wgt,SIGNAL(destroyedThis(QString)),this,SLOT(turnOffProduct(QString)));
    }
}

void Delphinosyncro::openMainSpace()
{
    swapToSpace(mainspace);
}

void Delphinosyncro::openKeySpace()
{
    key->setText("");
    swapToSpace(keyspace);
}

void Delphinosyncro::openLoginSpace()
{
    swapToSpace(loginspase);
}

void Delphinosyncro::isAutorun(int ar)
{
    if(ar == Qt::Checked)
        autorun = true;
    if(ar == Qt::Unchecked)
        autorun = false;
    SaveDatabase();
}

void Delphinosyncro::addNotice(QString head, QString body)
{
    trayIcon->showMessage(head,body,QIcon(),10000);
}

void Delphinosyncro::exitFromAccount()
{
    myLogin = "empty";
    myPassword = "empty";
    haveAccount(false);
    for(int i=0; i<myKey.size(); i++)
        deleteKey(myKey[i]);
    haveKey(false);
    SaveDatabase();
    reloadKeysLay();
    accEdit->setText("Добавить");
    disconnect(accEdit,SIGNAL(clicked()),this,SLOT(exitFromAccount()));
    connect(accEdit,SIGNAL(clicked()),this,SLOT(openLoginSpace()));
    writing("Client : unlogining");
}

void Delphinosyncro::addKey(QString key)
{
    for(int i=0; i<myKey.size(); i++)
    {
        if(myKey[i].compare(key) == 0)
            return;
    }
    myKey << key;
    myProduct << "empty";
    myLicense << "empty";
    reloadKeysLay();
}

void Delphinosyncro::editKey(QString key, QString product, QString license)
{
    for(int i=0; i<myKey.size(); i++)
    {
        if(myKey[i].compare(key) == 0)
        {
            QString lastLicense = myLicense[i];
            myProduct[i] = product;
            myLicense[i] = license;
            reloadKeysLay();
            if((lastLicense == "over" || lastLicense == "empty" ) && (license != "empty" && license != "over") && autorun)
                turnOnProduct(product);
            else if((lastLicense != "over" && lastLicense != "empty" ) && (license == "empty" || license == "over"))
                turnOffProduct(product);
            SaveDatabase();
        }
    }
}

void Delphinosyncro::deleteKey(QString _key)
{
    for(int i=0; i<myKey.size(); i++)
    {
        if(myKey[i].compare(_key) == 0)
        {
            writing("Client : key_disconnecting & Key : " + myKey[i]);
            myKey.removeAt(i);
            myProduct.removeAt(i);
            myLicense.removeAt(i);
            reloadKeysLay();
        }
    }
}

void Delphinosyncro::openRegistrationSpace()
{
    swapToSpace(registrationspace);
}

void Delphinosyncro::connected()
{
    //qDebug() << "Соединение установлено. Авторизация ПО...";
    loadInfo->setText("Соединение установлено. Авторизация ПО...");
    errorsCount = 0;
    lastSocketError = "";
    if(!connectionCheck->isActive()) connectionCheck->start(15000);
    if(exitTimeout->isActive()) exitTimeout->stop();
    if(loadAlarmInfo->isVisible()) loadAlarmInfo->setVisible(false);
    for(int i=0; i<myKey.size(); i++)
        myLicense[i] = "empty";
    isAutorization = true;
    writing(createAutorizationMessage());
}

void Delphinosyncro::hostFounded()
{
    loadInfo->setText("Хост найден. Соединение...");
}

void Delphinosyncro::connectingError(QAbstractSocket::SocketError err)
{
    QString mess;
    errorsCount++;
    if(!exitTimeout->isActive()) exitTimeout->start(300000);

    if(err == QAbstractSocket::ConnectionRefusedError)
        mess = "Соединение было разорвано другим узлом (или по тайм-ауту)";
    else if(err == QAbstractSocket::RemoteHostClosedError)
        mess = "Соединение было разорвано сервером";
    else if(err == QAbstractSocket::HostNotFoundError)
        mess = "Адрес сервера не найден";
    else if(err == QAbstractSocket::SocketAccessError)
        mess = "Приложение не получило необходимых прав";
    else if(err == QAbstractSocket::SocketResourceError)
        mess = "Системе не хватает ресурсов";
    else if(err == QAbstractSocket::SocketTimeoutError)
        mess = "Время для соединения с сервером истекло";
    else if(err == QAbstractSocket::DatagramTooLargeError)
        mess = "Объём передаваемых данных выше установленного в операционной системе ограничения";
    else if(err == QAbstractSocket::NetworkError)
        mess = "Непредвиденные проблемы с сетью";
    else if(err == QAbstractSocket::AddressInUseError)
        mess = "Адрес сервера уже используется в режиме эксклюзивного использования";
    else if(err == QAbstractSocket::SocketAddressNotAvailableError)
        mess = "Адрес не найден на узле";
    else if(err == QAbstractSocket::UnsupportedSocketOperationError)
        mess = "Операция не поддерживается операционной системой";
    else if(err == QAbstractSocket::ProxyAuthenticationRequiredError)
        mess = "Ошибка прокси сервера";
    else if(err == QAbstractSocket::SslHandshakeFailedError)
        mess = "Подтверждение связи SSL/TLS завершилось неудачей";
    else if(err == QAbstractSocket::UnfinishedSocketOperationError)
        mess = "Последняя неудачная операция еще не завершена ";
    else if(err == QAbstractSocket::ProxyConnectionRefusedError)
        mess = "Невозможно связаться с прокси-сервером, поскольку соединение к этому серверу было запрещено";
    else if(err == QAbstractSocket::ProxyConnectionClosedError)
        mess = "Соединение с прокси-сервером было неожиданно закрыто";
    else if(err == QAbstractSocket::ProxyConnectionTimeoutError)
        mess = "Время соединения с прокси-сервером истекло";
    else if(err == QAbstractSocket::ProxyNotFoundError)
        mess = "Адрес прокси не был найден";
    else if(err == QAbstractSocket::ProxyProtocolError)
        mess = "Ответ прокси-сервера не интерпритируется";
    else if(err == QAbstractSocket::UnknownSocketError)
        mess = "Произошла неопределённая ошибка";

    if(mess.compare(lastSocketError) != 0)
    {
        addNotice("Соединение разорвано",mess);
        lastSocketError = mess;
        lastSocketErrorTime = QTime::currentTime();
        this->showNormal();
    }
    QString infoMess = "Повторная попытка соединения...";
    if(exitTimeout->isActive()) infoMess += "\nПри отсутствии соединения с сервером все продукты будут закрыты через " + QString::number(exitTimeout->remainingTime()/60000) + " минут";
    if(!isLoading) startLoading("Соединение с сервером...");
    loadAlarmInfo->setText(infoMess);
    loadAlarmInfo->setVisible(true);
    //if(socket->state() != QTcpSocket::UnconnectedState) socket->disconnectFromHost();
    //if(socket->state() != QTcpSocket::UnconnectedState) socket->waitForDisconnected();
    checkConnection();
}

void Delphinosyncro::checkConnection()
{
    if(socket->state() == QAbstractSocket::UnconnectedState)
    {
        socket->connectToHost(host,port);
        QString infoMess = "Повторная попытка соединения...";
        if(exitTimeout->isActive()) infoMess += "\nПри отсутствии соединения с сервером все продукты будут закрыты через " + QString::number(exitTimeout->remainingTime()/60000) + " минут";
        loadAlarmInfo->setText(infoMess);
        loadAlarmInfo->setVisible(true);
    }
        //connectingError(QAbstractSocket::UnknownSocketError);
}

void Delphinosyncro::reconnectTimeout()
{
    for(int i=0; i<myKeyWidget.size(); i++)
    {
        if(myKeyWidget[i]->isActive())
            turnOffProduct(myKeyWidget[i]->product);
    }
    exitTimeout->stop();
}

void Delphinosyncro::reading()
{
    QString command;
    QStringList head, data;
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_2);

    for (;;) {
            if (!m_nNextBlockSize) {
                if (socket->bytesAvailable() < sizeof(quint16)) {
                    break;
                }
                in >> m_nNextBlockSize;
            }

            if (socket->bytesAvailable() < m_nNextBlockSize) {
                break;
            }

            in >> command;
            m_nNextBlockSize = 0;
    }

    QStringList blocks = command.split(" & ");
    for(int i=0; i<blocks.size(); i++)
    {
        QStringList res = blocks[i].split(" : ");
        if(res.size() == 2)
        {
            head << res[0];
            data << res[1];
        }
    }

    if(blocks.size() > 0 && isAutorization && blocks[0].compare("Server : autorizated") == 0)
    {
        isAutorization = false;
        if(myLogin == "empty")
        {
            if(myKey.isEmpty())
            {
                loadInfo->setText("ПО авторизовано");
                finishLoading();
            }
            else
            {
                loadInfo->setText("ПО авторизовано. Активация ключей...");
                activatingAll();
            }
        }
        else
        {
            loadInfo->setText("ПО авторизовано. Вход в аккаунт...");
            logining();
        }
    }
    if(blocks.size() > 1 && isAutorization && blocks[0].compare("Server : autorization denied") == 0 && head[1].compare("Information") == 0)
    {
        QString mess = "";
        if(data[1].compare("unknown products") == 0)
            mess = "Продукты не поддерживаются сервером";
        if(data[1].compare("update needed") == 0 && blocks.size() > 2)
        {
            mess = "Необходимо обновление продукта " + data[2];
            showNormal();
            if(!isLoading) startLoading("Обратитесь за обновлением к автору ПО");
            else loadInfo->setText("Обратитесь за обновлением к автору ПО");
        }

        addNotice("Сервер отказал в подключении",mess);
        socket->disconnectFromHost();
        socket->close();
        closeTimeout->start(10000);
    }
    else if(blocks.size() > 0 && isLogining && blocks[0].compare("Server : logined") == 0)
    {
        accEdit->setText("Выйти");
        disconnect(accEdit,SIGNAL(clicked()),this,SLOT(openLoginSpace()));
        connect(accEdit,SIGNAL(clicked()),this,SLOT(exitFromAccount()));
        isLogining = false;
        QStringList keys;
        QStringList mykeys = myKey;
        myLogin = login->text();
        myPassword = password->text();
        haveAccount(true);
        for(int i=1; i<head.size(); i++)
        {
            if(head[i].compare("Key") == 0)
            {
                keys << data[i];
            }
        }
        if(keys.size() != 0){
            for(int i=0; i<mykeys.size(); i++)
                for(int j=0; j<keys.size(); j++)
                {
                    if(mykeys[i] == keys[j])
                    {
                        keys.removeAt(j);
                        mykeys.removeAt(i);
                    }
                }
            for(int i=0; i<keys.size(); i++)
                addKey(keys[i]);

        }
        for(int i=0; i<mykeys.size(); i++)
            writing("Client : key_connecting & Key : " + mykeys[i] + " & Login : " + myLogin);

        activespace = mainspace;
        SaveDatabase();
        if(myKey.isEmpty())
        {
            loadInfo->setText("Вход выполнен");
            finishLoading();
        }
        else {
            loadInfo->setText("Вход выполнен. Активация ключей...");
            activatingAll();
        }
    }
    else if(blocks.size() > 1 && isLogining && blocks[0].compare("Server : logining denied") == 0 && head[1].compare("Information") == 0)
    {
        QString mess;
        if(data[1].compare("account not found") == 0)
            mess = "Неверный логин или пароль";
        addNotice("Ошибка входа",mess);
        haveAccount(false);
        SaveDatabase();
        if(myKey.isEmpty())
        {
            loadInfo->setText("Вход не выполнен");
            finishLoading();
        }
        else
        {
            loadInfo->setText("Вход не выполнен. Активация ключей...");
            activatingAll();
        }
    }
    else if(blocks.size() > 0 && isRegistration && blocks[0].compare("Server : registrated") == 0)
    {
        myLogin = newlogin->text();
        myPassword = newpassword->text();
        haveAccount(true);
        newlogin->setText("");
        newpassword->setText("");
        newemail->setText("");
        SaveDatabase();
        activespace = mainspace;
        logining();
        finishLoading();
    }
    else if(blocks.size() > 1 && isRegistration && blocks[0].compare("Server : registration denied") == 0 && head[1].compare("Information") == 0)
    {
        QStringList info = data[1].split("|");
        QStringList mess;
        for(int i=0; i<info.size(); i++)
        {
            if(info[i] == "login used")
                mess << "Логин занят";
            if(info[i] == "login short")
                mess << "Слишком короткий логин";
            if(info[i] == "password short")
                mess << "Слишком короткий пароль";
        }
        for(int i=0; i<mess.size(); i++)
        {
            addNotice("Ошибка регистрации",mess[i]);
        }
        finishLoading();
    }
    else if(blocks.size() > 1 && isLogining && blocks[0].compare("Server : key_connected") == 0 && head[1].compare("Key") == 0)
    {

    }
    else if(blocks.size() > 2 && isLogining && blocks[0].compare("Server : key_connecting denied") == 0 && head[1].compare("Key") == 0 && head[2].compare("Information"))
    {
        QString mess = "";
        if(data[2] == "key already connected")
            mess = "Ключ уже присоединен к другому аккаунту";
        else if(data[2] == "account not found")
            mess = "Аккаунт не найден на сервере";
        else if(data[2] == "account not logined")
            mess = "Ваш аккаунт не авторизован";
        addNotice("Ошибка присоединения", mess);
    }
    else if(blocks.size() > 3 && blocks[0].compare("Server : licensed") == 0 && head[1].compare("Key") == 0 && head[2].compare("Product") == 0 && head[3].compare("License") == 0)
    {
        activespace = mainspace;
        addKey(data[1]);
        editKey(data[1],data[2],data[3]);
        key_activating--;
        haveKey(true);
        if(key_activating < 1 && isLoading) {
            finishLoading();
            key_activating = 0;
        }
    }
    else if(blocks.size() > 2 && blocks[0].compare("Server : licensing denied") == 0 && head[1].compare("Key") == 0 && head[2].compare("Information") == 0)
    {
        QString mess = "";
        QString lic = "";
        for(int i=0; i<myKey.size(); i++)
        {
            if(myKey[i].compare(data[1]) == 0)
                lic = myLicense[i];
        }
        if(data[2] == "license not found")
            mess = "Ключ " + data[1] + " не найден";
        if(data[2] == "license is over"){
            if(lic == "over")
                return;
            mess = "Продукт: " + data[3] + ". Ключ: " + data[1] + ". Лицензия просрочена";
            addKey(data[1]);
            editKey(data[1],data[3],"over");
        }
        if(data[2] == "license using")
            mess = "Продукт: " + data[3] + ". Ключ: " + data[1] + " уже используется";
        addNotice("Ошибка активации", mess);
        key_activating--;
        if(key_activating == 0)
            finishLoading();
    }
    else if(blocks.size() == 1  && blocks[0].compare("Server : synchronization") == 0)
    {
        writing("Client : synchronization");
    }
    else if(blocks.size() == 2 && blocks[0] == "Server : information" && head[1].compare("Information") == 0)
    {
        addNotice("Сообщение сервера",data[1]);
    }
}

void Delphinosyncro::writing(QString command)
{
    if(socket->bytesToWrite()!=0)
        socket->waitForBytesWritten();
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out << quint16(0) << command;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    socket->write(arrBlock);
}

void Delphinosyncro::runAll()
{
    for(int i=0; i<myKeyWidget.size(); i++)
    {
        if(myKeyWidget[i]->isLicensed() && !myKeyWidget[i]->isActive())
        {
            myKeyWidget[i]->activityClicked();
        }
    }
}

void Delphinosyncro::activatingAll()
{
    for(int i=0; i<myKey.size(); i++)
    {
        if(myLicense[i] == "empty" || myLicense[i] == "over")
        {
            if(!isLoading) startLoading("Авторизация ключа...");
            else loadInfo->setText("Авторизация ключа...");
            writing(QString("Client : licensing & Key : ") + myKey[i]);
            key_activating++;
        }
    }
    if(key_activating == 0 && isLoading) finishLoading();
}

void Delphinosyncro::activating()
{
    if(!isLoading) startLoading("Авторизация ключа...");
    else loadInfo->setText("Авторизация ключа...");
    writing(QString("Client : licensing & Key : ") + key->text());
    key_activating++;
}

void Delphinosyncro::logining()
{
    if(!isLoading) startLoading("Авторизация аккаунта...");
    else loadInfo->setText("Авторизация аккаунта...");
    writing(QString("Client : logining & Login : ") + login->text() + QString(" & Password : ") + password->text());
    isLogining = true;
}

void Delphinosyncro::registration()
{
    if(!isLoading) startLoading("Регистрация...");
    else loadInfo->setText("Регистрация...");
    writing(QString("Client : registration & Login : ") + newlogin->text() + QString(" & Password : ") + newpassword->text() + QString(" & Email : ") + newemail->text());
    isRegistration = true;
}

QString Delphinosyncro::createAutorizationMessage()
{
    QString message;
    message += protocol;
    message += " & Client : autorization";
    message += " & Product : ";
    for(int i=0; i<products.size(); i++)
    {
        message += products[i];
        if(i!=products.size()-1) message += "|";
    }
    message += " & Version : ";
    for(int i=0; i<versions.size(); i++)
    {
        message += versions[i];
        if(i!=products.size()-1) message += "|";
    }
    return message;
}

void Delphinosyncro::turnOnProduct(QString name)
{
    BaseSettings settings;

    for(int i=0; i<myKeyWidget.size(); i++)
    {
        if(myKeyWidget[i]->product.compare("CSObserver") == 0 || myKeyWidget[i]->product.compare("CSObserverFree") == 0 && !myKeyWidget[i]->isActive())
        {
            Matches* matches = new Matches(settings.matchesUrl);
            myKeyWidget[i]->object = matches;
            matches->show();
            myKeyWidget[i]->active(true);
            connect(myKeyWidget[i],SIGNAL(destroyProg()),matches,SLOT(deleteLater()));
            connect(matches,SIGNAL(destroyed(QObject*)),myKeyWidget[i],SLOT(productDestroyed()));
            connect(this,SIGNAL(destroyed(QObject*)),matches,SLOT(deleteLater()));
        }
    }
}

void Delphinosyncro::turnOffProduct(QString name)
{
    for(int i=0; i<myKeyWidget.size(); i++)
    {
        if(myKeyWidget[i]->product.compare(name) == 0 && myKeyWidget[i]->isActive())
        {
            emit myKeyWidget[i]->destroyProg();
            myKeyWidget[i]->object = NULL;
            myKeyWidget[i]->active(false);
        }
    }
}

void Delphinosyncro::trayIconClicked(QSystemTrayIcon :: ActivationReason reason)
{
    if(reason == QSystemTrayIcon::Trigger)
    {
        launcherShowHide();
    }
}

void Delphinosyncro::launcherShowHide()
{
    if(isVisible())
    {
        hide();
    }
    else
    {
        show();
    }
}

void Delphinosyncro::closeLauncher()
{
    for(int i=0; i<myKeyWidget.size(); i++)
    {
        if(myKeyWidget[i]->isActive())
            myKeyWidget[i]->activityClicked();
    }
    SaveDatabase();
    trayIcon->hide();
    trayIcon->deleteLater();
    deleteLater();
    QApplication::closeAllWindows();
}
