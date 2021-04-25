#include "mainwindow.h"

const QStringList sellTypes = {"Бесплатно", "Покупка", "Подписка (ежемесячная)", "Подписка (еженедельная)"};
QString alph = "1234567890ABCDEFGHIJ";
QSqlDatabase base;
ServerMainWindow* serverWindow;
QString extensionIcon = "extension.jpg";
QString settingsIcon = "settings.png";
QString deleteIcon = "delete.png";

product::product()
{

}

product::product(int cd, QString nm, QString sType, QString vers, int cst)
{
    code = cd;
    name = nm;
    sellType = sType;
    version = vers;
    cost = cst;
}

QWidget* product::getWidget()
{
    myWidget = new QWidget();
    QLabel* nameField = new QLabel(name);
    QLabel* stypeField = new QLabel(sellType);
    QLabel* costField = new QLabel(QString::number(cost) + "$");
    QPushButton* edit = new QPushButton();
    QPushButton* del = new QPushButton();
    int h = 30;

    QHBoxLayout* lay = new QHBoxLayout();
    lay->addWidget(nameField);                          nameField->setFixedSize(150,h);
    lay->addWidget(stypeField);                         stypeField->setFixedSize(180,h);
    lay->addWidget(costField);                          costField->setFixedSize(40,h);
    lay->addStretch(1);
    lay->addWidget(edit);                               edit->setFixedSize(h,h);
    lay->addWidget(del);                                del->setFixedSize(h,h);
    myWidget->setLayout(lay);                           myWidget->setFixedSize(600,h+10);

    connect(edit,SIGNAL(clicked()),this,SLOT(correct()));
    connect(del,SIGNAL(clicked()),this,SLOT(destroy()));
    return myWidget;
}

void product::correct()
{
    ProductManager* manager = new ProductManager(this);
}

void product::changed()
{

}

void product::destroy()
{
    serverWindow->delProduct(this);
    if(!clean())
        QMessageBox::critical(0,"Database error","Can not delete key: " + base.lastError().text());
    myWidget->deleteLater();
    deleteLater();
}

bool product::save()
{
    QSqlQuery query;
    QString str = "INSERT INTO PRODUCTS (code, name, version, selltype, cost) "
                  "VALUES ('%1', '%2', '%3', '%4', '%5');";
    QString res = str.arg(code)
                     .arg(name)
                     .arg(version)
                     .arg(sellType)
                     .arg(cost);
    if(!query.exec(res))
        return false;
    return true;
}

bool product::rewrite()
{
    if(!clean())
        return false;
    else if(!save())
        return false;
    return true;
}

bool product::clean()
{
    QSqlQuery query;
    QString str = "DELETE FROM PRODUCTS WHERE code = '%1' ;";
    QString res = str.arg(code);
    if(!query.exec(res))
        return false;
    return true;
}

ProductManager::ProductManager()
{
    setWindowTitle("Создание продукта");
    creation = true;
    prod = new product;
    init();
    name->setText("Название");
    version->setText("Версия");
    sellType->setCurrentIndex(1);
    sellType->setCurrentIndex(0);
    cost->setValue(1);
    cost->setValue(0);
}

ProductManager::ProductManager(class product* pr)
{
    setWindowTitle("Редактирование продукта");
    creation = false;
    prod = pr;
    init();
    name->setText(pr->name);
    version->setText(pr->version);
    for(int i=0; i<sellTypes.size(); i++)
    {
        if(pr->sellType == sellTypes[i])
            sellType->setCurrentIndex(i);
    }
    cost->setValue(pr->cost);
}

ProductManager::~ProductManager()
{

}

void ProductManager::init()
{
    QVBoxLayout* lay = new QVBoxLayout();
    QHBoxLayout* lay1 = new QHBoxLayout();
    name = new QLineEdit();
    sellType = new QComboBox();
    version = new QLineEdit();
    cost = new QSpinBox();
    back = new QPushButton("Отмена");
    ok = new QPushButton("Выполнить");

    sellType->addItems(sellTypes);

    lay->addWidget(name);
    lay->addWidget(version);
    lay->addWidget(sellType);
    lay->addWidget(cost);
    lay1->addWidget(back);
    lay1->addWidget(ok);
    lay->addLayout(lay1);
    setLayout(lay);
    show();

    connect(name,SIGNAL(textEdited(QString)),this,SLOT(setName(QString)));
    connect(version,SIGNAL(textEdited(QString)),this,SLOT(setVersion(QString)));
    connect(sellType,SIGNAL(currentTextChanged(QString)),this,SLOT(setSellType(QString)));
    connect(cost,SIGNAL(valueChanged(int)),this,SLOT(setCost(int)));
    connect(back,SIGNAL(clicked()),this,SLOT(deleteLater()));
    connect(ok,SIGNAL(clicked()),this,SLOT(operation()));
}

void ProductManager::operation()
{
    prod->name = name->text();
    prod->version = version->text();
    if(creation)
    {
        serverWindow->addProduct(prod);
        deleteLater();
    }
    else
    {
        if(!prod->rewrite())
            QMessageBox::critical(0,"Database error","Can not rewrite product: " + base.lastError().text());
        deleteLater();
    }
}

void ProductManager::setName(QString name)
{

}

void ProductManager::setVersion(QString vers)
{

}

void ProductManager::setSellType(QString stype)
{
    prod->sellType = stype;
}

void ProductManager::setCost(int i)
{
    prod->cost = i;
}

productKey::productKey()
{

}

productKey::productKey(int cd, product* prod, QString accLog, QString ky, int year, int month, int day, int hour, int minute, int second)
{
    code = cd;
    productType = prod;
    accCode = accLog;
    key = ky;
    endDateLicense = QDate(year, month, day);
    endTimeLicense = QTime(hour, minute, second);
}

QWidget* productKey::getWidget()
{
    myWidget = new QWidget();
    QLabel* nameField = new QLabel(key);
    QLabel* productField = new QLabel(productType->name);
    QLabel* loginField = new QLabel(accCode);
    QPushButton* ext = new QPushButton();
    QPushButton* edit = new QPushButton();
    QPushButton* del = new QPushButton();
    int h = 30, r = h-5;

    ext->setIcon(QIcon(extensionIcon));
    ext->setIconSize(QSize(r,r));
    edit->setIcon(QIcon(settingsIcon));
    edit->setIconSize(QSize(r,r));
    del->setIcon(QIcon(deleteIcon));
    del->setIconSize(QSize(r,r));

    QHBoxLayout* lay = new QHBoxLayout();
    lay->addWidget(nameField);                          nameField->setFixedSize(150,h);
    lay->addWidget(productField);                       productField->setFixedSize(150,h);
    lay->addWidget(loginField);                         loginField->setFixedSize(80,h);
    lay->addStretch(1);
    lay->addWidget(ext);                                ext->setFixedSize(h,h);
    lay->addWidget(edit);                               edit->setFixedSize(h,h);
    lay->addWidget(del);                                del->setFixedSize(h,h);
    myWidget->setLayout(lay);                           myWidget->setFixedSize(600,h+10);

    connect(edit,SIGNAL(clicked()),this,SLOT(correct()));
    connect(del,SIGNAL(clicked()),this,SLOT(destroy()));
    connect(ext,SIGNAL(clicked()),this,SLOT(extension()));
    return myWidget;
}

void productKey::correct()
{
    KeyManager* manager = new KeyManager(this);
}

void productKey::destroy()
{
    serverWindow->delKey(this);
    if(!clean())
        QMessageBox::critical(0,"Database error","Can not delete key: " + base.lastError().text());
    myWidget->deleteLater();
    deleteLater();
}

void productKey::extension()
{
    QTime time;
    QDate date;
    if(isActual())
    {
        time = endTimeLicense;
        date = endDateLicense;
    }
    else
    {
        time = QTime::currentTime();
        date = QDate::currentDate();
    }
    if(productType->sellType.compare(sellTypes[3]) == 0)
    {
        date = date.addDays(7);
        endTimeLicense = time;
        endDateLicense = date;
    }
    rewrite();
}

bool productKey::isActual()
{
    if(endDateLicense > QDate::currentDate() || (endDateLicense == QDate::currentDate() && endTimeLicense > QTime::currentTime()))
        return true;
    else
        return false;
}

bool productKey::save()
{
    bool nullDate = false;
    QSqlQuery query;
    QString str = "INSERT INTO KEYS (code, productcode, accountcode, key, year, month, day, hour, minute, second)"
                  "VALUES('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10');";
    if(productType->sellType == sellTypes[0] ||
            productType->sellType == sellTypes[1] ||
            !isActual())
        nullDate = true;
    if(accCode == "") accCode = "empty";
    QString res = str.arg(code)
                     .arg(productType->code)
                     .arg(accCode)
                     .arg(key)
                     .arg(nullDate ? 0 : endDateLicense.year())
                     .arg(nullDate ? 0 : endDateLicense.month())
                     .arg(nullDate ? 0 : endDateLicense.day())
                     .arg(nullDate ? 0 : endTimeLicense.hour())
                     .arg(nullDate ? 0 : endTimeLicense.minute())
                     .arg(nullDate ? 0 : endTimeLicense.second());
    if(!query.exec(res))
        return false;
    return true;
}

bool productKey::rewrite()
{
    if(!clean())
        return false;
    else if(!save())
        return false;
    return true;
}

bool productKey::clean()
{
    QSqlQuery query;
    QString str = "DELETE FROM KEYS WHERE code = '%1' ;";
    QString res = str.arg(code);
    if(!query.exec(res))
        return false;
    return true;
}

KeyManager::KeyManager()
{
    setWindowTitle("Создание ключа");
    creation = true;
    init();
    myKey = new productKey;

    QVector <product*> prds = serverWindow->getProducts();
    for(int i=0; i<prds.size(); i++)
    {
        prod->addItem(prds[i]->name);
    }
    count->setValue(1);
    accLog->hide(); accLog->setEditable(false);
    key->hide();
    setFixedSize(300,200);
}

KeyManager::KeyManager(productKey* k)
{
    setWindowTitle("Редактирование ключа");
    creation = false;
    init();
    myKey = k;

    QVector <product*> prds = serverWindow->getProducts(); int pci = 0;
    for(int i=0; i<prds.size(); i++)
    {
        prod->addItem(prds[i]->name);
        if(prds[i]->code == k->productType->code)
            pci = i;
    }
    QVector <account*> accs = serverWindow->getAccounts(); int aci = 0;
    accLog->addItem("");
    for(int i=0; i<accs.size(); i++)
    {
        accLog->addItem(accs[i]->login);
        if(accs[i]->login.compare(k->accCode))
            aci = i+1;
    }
    key->setText(k->key);
    prod->setCurrentIndex(pci);
    accLog->setCurrentIndex(aci);
    count->hide();
    setFixedSize(400,200);
}

KeyManager::~KeyManager()
{

}

void KeyManager::init()
{
    QVBoxLayout* lay = new QVBoxLayout();
    QHBoxLayout* lay1 = new QHBoxLayout();
    QHBoxLayout* lay2 = new QHBoxLayout();
    prod = new QComboBox();
    key = new QLabel();
    accLog = new QComboBox();
    count = new QSpinBox();
    back = new QPushButton("Отмена");
    ok = new QPushButton("Выполнить");

    lay1->addWidget(prod);
    lay1->addWidget(accLog);
    lay1->addWidget(key);
    lay1->addWidget(count);
    lay2->addWidget(back);
    lay2->addStretch(1);
    lay2->addWidget(ok);
    lay->addLayout(lay1);
    lay->addLayout(lay2);
    setLayout(lay);
    show();

    connect(prod,SIGNAL(currentIndexChanged(int)),this,SLOT(setProd(int)));
    connect(accLog,SIGNAL(currentTextChanged(QString)),this,SLOT(setAcc(QString)));
    connect(back,SIGNAL(clicked()),this,SLOT(deleteLater()));
    connect(ok,SIGNAL(clicked()),this,SLOT(operation()));
}

void KeyManager::operation()
{
    if(creation)
    {
        createKey(count->value());
        deleteLater();
    }
    else
    {
        if(!myKey->rewrite())
            QMessageBox::critical(0,"Database error","Can not rewrite key: " + base.lastError().text());
        deleteLater();;
    }
}

void KeyManager::createKey(int i)
{
    while(i>0)
    {
        productKey* newKey = new productKey;
        newKey->key = serverWindow->createKey();
        newKey->productType = myKey->productType;
        newKey->endDateLicense = QDate();
        newKey->endTimeLicense = QTime();
        serverWindow->addKey(newKey);
        i--;
    }
}

void KeyManager::setProd(int ind)
{
    myKey->productType = serverWindow->getProduct(ind);
}

void KeyManager::setAcc(QString acc)
{
    myKey->accCode = acc;
}


account::account()
{

}

account::account(QString name, QString pass, QString eml)
{
    login = name;
    password = pass;
    email = eml;
}

QWidget* account::getWidget()
{
    myWidget = new QWidget();
    QLabel* loginField = new QLabel(login);
    QLabel* passwordField = new QLabel(password);
    QLabel* emailField = new QLabel(email);
    QPushButton* edit = new QPushButton();
    QPushButton* del = new QPushButton();
    int h = 30;

    QHBoxLayout* lay = new QHBoxLayout();
    lay->addWidget(loginField);                         loginField->setFixedSize(100,h);
    lay->addWidget(passwordField);                      passwordField->setFixedSize(100,h);
    lay->addWidget(emailField);                         emailField->setFixedSize(200,h);
    lay->addStretch(1);
    lay->addWidget(edit);                               edit->setFixedSize(h,h);
    lay->addWidget(del);                                del->setFixedSize(h,h);
    myWidget->setLayout(lay);                           myWidget->setFixedSize(600,h+10);

    connect(edit,SIGNAL(clicked()),this,SLOT(correct()));
    connect(del,SIGNAL(clicked()),this,SLOT(destroy()));
    return myWidget;
}

void account::correct()
{
    AccountManager* manager = new AccountManager(this);
}

void account::changed()
{

}

void account::destroy()
{
    serverWindow->delAccount(this);
    clean();
    myWidget->deleteLater();
    deleteLater();
}

bool account::save()
{
    QSqlQuery query;
    QString str = "INSERT INTO ACCOUNTS (login, password, email) "
                  "VALUES ('%1', '%2', '%3');";
    QString res = str.arg(login)
                     .arg(password)
                     .arg(email);
    if(!query.exec(res))
        return false;
    return true;
}

bool account::rewrite()
{
    if(!clean())
        return false;
    else if(!save())
        return false;
    return true;
}

bool account::clean()
{
    QSqlQuery query;
    QString str = "DELETE FROM ACCOUNTS WHERE login = '%1' ;";
    QString res = str.arg(login);
    if(!query.exec(res))
        return false;
    return true;
}

AccountManager::AccountManager()
{
    setWindowTitle("Создание аккаунта");
    creation = true;
    init();
    myAcc = new account;
    login->setText("логин");
    password->setText("пароль");
    email->setText("email");

    setFixedSize(300,300);
}

AccountManager::AccountManager(account* k)
{
    setWindowTitle("Редактирование аккаунта");
    creation = false;
    init();
    myAcc = k;
    login->setText(k->login);
    password->setText(k->password);
    email->setText(k->email);

    setFixedSize(400,300);
}

AccountManager::~AccountManager()
{

}

void AccountManager::init()
{
    QVBoxLayout* lay = new QVBoxLayout();
    QHBoxLayout* lay1 = new QHBoxLayout();
    login = new QLineEdit();
    password = new QLineEdit();
    email = new QLineEdit();
    back = new QPushButton("Отмена");
    ok = new QPushButton("Выполнить");

    lay->addWidget(login);
    lay->addWidget(password);
    lay->addWidget(email);
    lay1->addWidget(back);
    lay1->addWidget(ok);
    lay->addLayout(lay1);
    setLayout(lay);
    show();

    connect(back,SIGNAL(clicked()),this,SLOT(deleteLater()));
    connect(ok,SIGNAL(clicked()),this,SLOT(operation()));
}

void AccountManager::operation()
{
    myAcc->login = login->text();
    myAcc->password = password->text();
    myAcc->email = email->text();

    if(creation)
    {
        serverWindow->addAccount(myAcc);
        deleteLater();
    }
    else
    {
        if(!myAcc->rewrite())
            QMessageBox::critical(0,"Database error","Can not rewrite key: " + base.lastError().text());
        deleteLater();
    }
}

void AccountManager::setLogin(QString log)
{

}

void AccountManager::setPassword(QString pass)
{

}

void AccountManager::setEmail(QString eml)
{

}


ClientSocket::ClientSocket(QTcpSocket* sock)
{
    socket = sock;
    connect(synchroTimer,SIGNAL(timeout()),this,SIGNAL(synchronization()));
    connect(socket,SIGNAL(connected()),this,SIGNAL(connected()));
    connect(socket,SIGNAL(disconnected()),this,SIGNAL(disconnected()));
    connect(socket,SIGNAL(readyRead()),this,SIGNAL(readyRead()));
}

ClientSocket::~ClientSocket()
{
    DialogHeaderLabel->deleteLater();
    DialogFullLayout->deleteLater();
}

void ClientSocket::addKey(productKey *key)
{
    myKeys << key;
}

bool ClientSocket::haveAccount()
{
    if(login.compare("empty") == 0)
        return false;
    else
        return true;
}

productKey* ClientSocket::getKeyForProduct(QString productName)
{
    for(int i=0; i<myKeys.size(); i++)
    {
        if(productName == myKeys[i]->productType->name)
            return myKeys[i];
    }
}

QPushButton* ClientSocket::getDialogHeader()
{
    myDialogHeader = new QPushButton();
    DialogHeaderLabel = new QLabel();
    DialogHeaderHeader = new QLabel();

    DialogHeaderLabel->setText(dialog.isEmpty() ? "Сообщений еще нет" : dialog.last());
    DialogHeaderHeader->setText(socket->peerAddress().toString() + " : " + (!logined ? "NoName" : login));
    QHBoxLayout* lay = new QHBoxLayout();
    lay->addWidget(DialogHeaderHeader);
    lay->addWidget(DialogHeaderLabel);
    lay->setSpacing(15);
    myDialogHeader->setLayout(lay);
    myDialogHeader->setFixedSize(DialogHeaderWidth,DialogHeaderHeight);

    connect(myDialogHeader,SIGNAL(clicked()),this,SLOT(createFull()));
    return myDialogHeader;
}

QWidget* ClientSocket::getDialogFull()
{
    myDialogFull = new QWidget();
    DialogFullHeader = new QLabel();
    QVBoxLayout* lay = new QVBoxLayout();
    QScrollArea* DialogArea = new QScrollArea();

    QWidget* wgt = new QWidget();
    DialogFullLayout = new QVBoxLayout();
    QWidget* productsWgt = new QWidget();
    DialogFullLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    wgt->setLayout(DialogFullLayout);
    wgt->setMaximumSize(DialogFullWidth-30,100000);
    //productsWgt->setMaximumSize(DialogFullWidth-30,100000);
    DialogArea->setWidget(wgt);
    DialogFullLayout->setSpacing(15);

    lay->addWidget(DialogFullHeader);
    lay->addWidget(DialogArea);
    myDialogFull->setLayout(lay);
    myDialogFull->setFixedSize(DialogFullWidth,DialogFullHeight);
    lastDialogInFull = 0;
    reloadDialogs();
    return myDialogFull;
}

void ClientSocket::reloadDialogs()
{
    if(DialogHeaderLabel != NULL) DialogHeaderLabel->setText(dialog.last());
    if(DialogFullHeader != NULL) DialogFullHeader->setText(socket->peerAddress().toString() + " : " + (!logined ? "NoName" : login));
    if(DialogFullHeader != NULL) DialogHeaderHeader->setText(socket->peerAddress().toString() + " : " + (!logined ? "NoName" : login));
    if(DialogFullLayout != NULL) for(int i=lastDialogInFull; i<dialog.size(); i++)
    {
        QString str = dialog[i].mid(0,dialog[i].indexOf(" : "));
        QHBoxLayout* lay = new QHBoxLayout();
        lay->setAlignment(str == "Server" ? Qt::AlignRight : Qt::AlignLeft);
        QLabel* lbl = new QLabel(dialog[i]);
        lbl->setMaximumSize(DialogFullSpase, 10000);
        if(str == "Server") lay->addStretch(1);
        lay->addWidget(lbl);
        if(str == "Client") lay->addStretch(1);
        DialogFullLayout->addLayout(lay);
        lastDialogInFull = i + 1;
    }
}

void ClientSocket::createFull()
{
    QWidget* w = getDialogFull();
    w->show();
}

ServerMainWindow::ServerMainWindow(int port)
{
    server = new QTcpServer(this);
    timer = new QTimer();

    if (!server->listen(QHostAddress("delphino.ddnsking.com"), 10351)) { //QHostAddress::Any
        QMessageBox::critical(0,
                              "Server Error",
                              "Unable to start the server:"
                              + server->errorString()
                             );
        server->close();
        return;
    }


    if(!DatabaseInit())
        QMessageBox::critical(0,"Ошибка базы данных","Ошибка открытия базы данных: " + base.lastError().text());
    if(!ReadDatabase())
        QMessageBox::critical(0,"Ошибка базы данных","Ошибка чтения данных: " + base.lastError().text());

    QScrollArea* DialogsArea = new QScrollArea();
    dialogsLay = new QVBoxLayout();
    QWidget* dialogsWgt = new QWidget();
    dialogsLay->setSizeConstraint(QLayout::SetMinAndMaxSize);
    dialogsWgt->setLayout(dialogsLay);
    dialogsWgt->setMaximumSize(610,100000);
    DialogsArea->setWidget(dialogsWgt);

    QScrollArea* AccountsArea = new QScrollArea();
    accountsLay = new QVBoxLayout();
    QWidget* accountsWgt = new QWidget();
    accountsLay->setSizeConstraint(QLayout::SetMinAndMaxSize);
    accountsWgt->setLayout(accountsLay);
    accountsWgt->setMaximumSize(610,100000);
    AccountsArea->setWidget(accountsWgt);

    QScrollArea* KeysArea = new QScrollArea();
    keysLay = new QVBoxLayout();
    QWidget* keysWgt = new QWidget();
    keysLay->setSizeConstraint(QLayout::SetMinAndMaxSize);
    keysWgt->setLayout(keysLay);
    keysWgt->setMaximumSize(610,100000);
    KeysArea->setWidget(keysWgt);

    QScrollArea* ProductsArea = new QScrollArea();
    productsLay = new QVBoxLayout();
    QWidget* productsWgt = new QWidget();
    productsLay->setSizeConstraint(QLayout::SetMinAndMaxSize);
    productsWgt->setLayout(productsLay);
    productsWgt->setMaximumSize(610,100000);
    ProductsArea->setWidget(productsWgt);

    createDialogsArea();
    createAccountsArea();
    createKeysArea();
    createProductsArea();

    tab = new QTabWidget(this);
    tab->addTab(DialogsArea,"Диалоги");
    tab->addTab(AccountsArea,"Аккаунты");
    tab->addTab(KeysArea,"Ключи");
    tab->addTab(ProductsArea,"Продукты");

    QLabel* text = new QLabel("Сервер работает");
    add = new QPushButton("Добавить");
    rel = new QPushButton("Обновить");
    QVBoxLayout* lay = new QVBoxLayout();
    QHBoxLayout* lay1 = new QHBoxLayout();
    lay->addWidget(tab);
    lay->addWidget(text);
    lay1->addWidget(rel);
    lay1->addWidget(add);
    lay->addLayout(lay1);
    setLayout(lay);

    setFixedSize(650,(QApplication::desktop()->screenGeometry().height() < 650) ? QApplication::desktop()->screenGeometry().height() - 50 : 600);
    show();
    setTab(0);
    timer->start(_InterfaceUpdateTime);

    connect(rel,SIGNAL(clicked()),this,SLOT(reload()));
    connect(timer,SIGNAL(timeout()),this,SLOT(reload()));
    connect(add,SIGNAL(clicked()),this,SLOT(addNew()));
    connect(tab,SIGNAL(currentChanged(int)),this,SLOT(setTab(int)));
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));
}

void ServerMainWindow::createDialogsArea()
{
    QLayoutItem* item;
    while(item = dialogsLay->itemAt(0))
    {
        dialogsLay->removeItem(item);
        dialogsLay->removeWidget(item->widget());
        item->widget()->deleteLater();
        delete item;
        dialogsLay->update();
    }
    for(int i=0; i<clients.size(); i++)
    {
        QPushButton* wgt = clients[i]->getDialogHeader();
        dialogsLay->addWidget(wgt);
        dialogsLay->update();
    }
}

void ServerMainWindow::createAccountsArea()
{
    QLayoutItem* item;
    while(item = accountsLay->itemAt(0))
    {
        accountsLay->removeItem(item);
        accountsLay->removeWidget(item->widget());
        item->widget()->deleteLater();
        delete item;
        layout()->update();
    }
    for(int i=0; i<accounts.size(); i++)
    {
        accountsLay->addWidget(accounts[i]->getWidget());
    }
}

void ServerMainWindow::createKeysArea()
{
    QLayoutItem* item;
    while(item = keysLay->itemAt(0))
    {
        keysLay->removeItem(item);
        keysLay->removeWidget(item->widget());
        item->widget()->deleteLater();
        delete item;
        layout()->update();
    }
    for(int i=0; i<keys.size(); i++)
    {
        keysLay->addWidget(keys[i]->getWidget());
    }
}

void ServerMainWindow::createProductsArea()
{
    QLayoutItem* item;
    while(item = productsLay->itemAt(0))
    {
        productsLay->removeItem(item);
        productsLay->removeWidget(item->widget());
        item->widget()->deleteLater();
        delete item;
        layout()->update();
    }
    for(int i=0; i<products.size(); i++)
    {
        productsLay->addWidget(products[i]->getWidget());
    }
}

ServerMainWindow::~ServerMainWindow()
{

}

QString ServerMainWindow::createKey()
{
    QString res;
    bool correct;
    while(true)
    {
        srand(QTime::currentTime().msecsSinceStartOfDay());
        res = ""; correct = true;
        for(int i=0; i<16; i++)
        {
            int r = rand()%20;
            res += alph[r];
        }
        QVector <productKey*> allKeys = serverWindow->getKeys();
        for(int i=0; i<allKeys.size(); i++)
        {
            if(res == allKeys[i]->key)
                correct = false;
        }
        if(correct) break;
        else continue;
    }
    return res;
}

int ServerMainWindow::createProductCode()
{
    int res = 0;
    bool correct;
    while(true)
    {
        res++; correct = true;
        for(int i=0; i<products.size(); i++)
        {
            if(products[i]->code == res)
                correct = false;
        }
        if(correct) break;
        else continue;
    }
    return res;
}

int ServerMainWindow::createKeyCode()
{
    int res = 0;
    bool correct;
    while(true)
    {
        res++; correct = true;
        for(int i=0; i<keys.size(); i++)
        {
            if(keys[i]->code == res)
                correct = false;
        }
        if(correct) break;
        else continue;
    }
    return res;
}

void ServerMainWindow::delProduct(product * p)
{
    products.remove(products.indexOf(p));
}

void ServerMainWindow::delKey(productKey * k)
{
    keys.remove(keys.indexOf(k));
}

void ServerMainWindow::delAccount(account * a)
{
    accounts.remove(accounts.indexOf(a));
}

void ServerMainWindow::addProduct(product * p)
{
    p->code = createProductCode();
    products << p;
    if(!p->save())
        QMessageBox::critical(0,"Database error","Can not save product: " + base.lastError().text());
    createProductsArea();
}

void ServerMainWindow::addKey(productKey * k)
{
    k->code = createKeyCode();
    keys << k;
    if(!k->save())
        QMessageBox::critical(0,"Database error","Can not save key: " + base.lastError().text());
    createKeysArea();
}

void ServerMainWindow::addAccount(account * a)
{
    accounts << a;
    if(!a->save())
        QMessageBox::critical(0,"Database error","Can not save account: " + base.lastError().text());
    createAccountsArea();
}

product* ServerMainWindow::getProduct(int i)
{
    return products[i];
}

productKey* ServerMainWindow::getKey(int i)
{
    return keys[i];
}

account* ServerMainWindow::getAccount(int i)
{
    return accounts[i];
}

QVector <product*> ServerMainWindow::getProducts()
{
    QVector <product*> res = products;
    return res;
}

QVector <productKey*> ServerMainWindow::getKeys()
{
    QVector <productKey*> res = keys;
    return res;
}

QVector <account*> ServerMainWindow::getAccounts()
{
    QVector <account*> res = accounts;
    return res;
}

bool ServerMainWindow::DatabaseInit()
{
    base = QSqlDatabase::addDatabase("QSQLITE");
    base.setDatabaseName("delphinobase");
    base.setUserName("server");
    //base.setDatabaseName("server");
    base.setPassword("topsecretpasswordjajajalefrut");
    if(!base.open()) return false;

    QStringList lst = base.tables();
    bool bd1 = false, bd2 = false, bd3 = false;
    for(int i=0; i<lst.size(); i++)
    {
        if(lst[i] == "PRODUCTS") bd1 = true;
        if(lst[i] == "KEYS") bd2 = true;
        if(lst[i] == "ACCOUNTS") bd3 = true;
    }

    QSqlQuery query;
    if(!bd1)
    {
        QString str = "CREATE TABLE PRODUCTS (code INTEGER, name VARCHAR(40), version VARCHAR(40), selltype VARCHAR(40), cost INTEGER);";
        if(!query.exec(str)) return false;
    }
    if(!bd2)
    {
        QString str = "CREATE TABLE KEYS (code INTEGER, productcode INTEGER, accountcode VARCHAR(40), key VARCHAR(20), year INTEGER, month INTEGER, day INTEGER, hour IMTEGER, minute INTEGER, second INTEGER);";
        if(!query.exec(str)) return false;
    }
    if(!bd3)
    {
        QString str = "CREATE TABLE ACCOUNTS (login VARCHAR(40), password VARCHAR(40), email VARCHAR(100));";
        if(!query.exec(str)) return false;
    }

    return true;
}

bool ServerMainWindow::ReadDatabase()
{
    QSqlQuery query;
    QSqlRecord rec;

    if(!query.exec("SELECT * FROM PRODUCTS;")){
         return false;}
    rec = query.record();
    while(query.next())
    {
        product *prod = new product;
        prod->code = query.value(rec.indexOf("code")).toInt();
        prod->name = query.value(rec.indexOf("name")).toString();
        prod->version = query.value(rec.indexOf("version")).toString();
        prod->sellType = query.value(rec.indexOf("selltype")).toString();
        prod->cost = query.value(rec.indexOf("cost")).toInt();
        products << prod;
    }

    if(!query.exec("SELECT * FROM KEYS;"))
        return false;
    rec = query.record();
    while(query.next())
    {
        productKey* key = new productKey;
        key->code = query.value(rec.indexOf("code")).toInt();
        product* test = findProduct(query.value(rec.indexOf("productcode")).toInt());
        key->productType = (test == NULL) ? emptyProd : test;
        key->accCode = query.value(rec.indexOf("accountcode")).toString();
        key->key = query.value(rec.indexOf("key")).toString();
        key->endDateLicense = QDate(query.value(rec.indexOf("year")).toInt(),query.value(rec.indexOf("month")).toInt(),query.value(rec.indexOf("day")).toInt());
        key->endTimeLicense = QTime(query.value(rec.indexOf("hour")).toInt(),query.value(rec.indexOf("minute")).toInt(),query.value(rec.indexOf("second")).toInt());
        keys << key;
    }

    if(!query.exec("SELECT * FROM ACCOUNTS;"))
        return false;
    rec = query.record();
    while(query.next())
    {
        account* acc = new account;
        acc->login = query.value(rec.indexOf("login")).toString();
        acc->password = query.value(rec.indexOf("password")).toString();
        acc->email = query.value(rec.indexOf("email")).toString();
        acc->keys = findAccKeys(acc->login);
        accounts << acc;
    }
    return true;
}

void ServerMainWindow::setTab(int i)
{
    if(i == 0) add->hide();
    else add->show();
    activeTab = i;
}

void ServerMainWindow::reload()
{
    if(activeTab == 0)
        createDialogsArea();
    else if(activeTab == 1)
        createAccountsArea();
    else if(activeTab == 2)
        createKeysArea();
    else if(activeTab == 3)
        createProductsArea();
}

void ServerMainWindow::addNew()
{
    if(activeTab == 0)
    {
        timer->setInterval(_InterfaceUpdateTime);
        timer->start();
    }
    else if(activeTab == 1)
    {
        timer->setInterval(_InterfaceUpdateTime);
        timer->start();
        AccountManager* manager = new AccountManager();
        connect(manager,SIGNAL(destroyed(QObject*)),this,SLOT(reload()));
    }
    else if(activeTab == 2)
    {
        timer->setInterval(_InterfaceUpdateTime);
        timer->start();
        KeyManager* manager = new KeyManager();
        connect(manager,SIGNAL(destroyed(QObject*)),this,SLOT(reload()));
    }
    else if(activeTab == 3)
    {
        timer->setInterval(_InterfaceUpdateTime);
        timer->start();
        ProductManager* manager = new ProductManager();
        connect(manager,SIGNAL(destroyed(QObject*)),this,SLOT(reload()));
    }
}

product* ServerMainWindow::findProduct(int code)
{
    for(int i=0; i<products.size(); i++)
    {
        if(products[i]->code == code)
            return products[i];
    }
    return NULL;
}

QVector <productKey*> ServerMainWindow::findAccKeys(QString name)
{
    QVector <productKey*> resKeys;
    for(int i=0; i<keys.size(); i++)
    {
        if(keys[i]->accCode == name) resKeys << keys[i];
    }
    return resKeys;
}

void ServerMainWindow::newConnection()
{
    ClientSocket* client = new ClientSocket(server->nextPendingConnection());
    connect(client,SIGNAL(disconnected()),this,SLOT(delConnection()));
    connect(client,SIGNAL(readyRead()),this,SLOT(readClient()));
    connect(client,SIGNAL(synchronization()),this,SLOT(synchronization()));
    clients << client;
    client->synchroTimer->start(60000);
    //sendToClient(client, "System: connected");
    createDialogsArea();
}

void ServerMainWindow::delConnection()
{
    ClientSocket* client = (ClientSocket*)sender();
    clients.removeOne(client);
    client->deleteLater();
    createDialogsArea();
}

void ServerMainWindow::parseMessage(ClientSocket *client, QString message)
{
    QStringList commands = message.split(" & ");
    QStringList heads;
    QStringList phrases;
    for(int i=0; i<commands.size(); i++)
    {
        int j = commands[i].indexOf(" : ");
        heads << commands[i].mid(0,j);
        phrases << commands[i].mid(j+3,commands[i].size()-1);
    }
    
    if(heads.size() == 4 && commands[0] == "Protocol : v1.0" && commands[1] == "Client : autorization" && heads[2] == "Product" && heads[3] == "Version")
    {
        bool allright = false;
        QStringList problems;
        QStringList client_products = phrases[2].split("|");
        QStringList client_versions = phrases[3].split("|");
        if(client_products.size() != client_versions.size())
        {
            sendToClient(client,"Server : autorization denied & Information : incorrect data");
            return;
        }
        for(int k=0; k<client_products.size(); k++)
        {
            bool founded = false;
            for(int i=0; i<products.size(); i++)
            {
                if(products[i]->name.compare(client_products[k]) == 0)
                {
                    if(products[i]->version.compare(client_versions[k]) != 0){
                        sendToClient(client,"Server : autorization denied & Information : update needed & Product : " + client_products[k]);
                    }
                    else
                    {
                        client->products << client_products[k];
                        founded = true;
                        allright = true;
                        break;
                    }
                }
            }
            if(!founded)
                problems << "Server : autorization problem & Information : unknown product & Product : " + client_products[k];
        }
        if(allright)
        {
            for(int i=0; i<problems.size(); i++)
            {
                sendToClient(client,problems[i]);
            }
            client->autorizated = true;
            sendToClient(client,"Server : autorizated");
            return;
        }
        else
            sendToClient(client,"Server : autorization denied & Information : unknown products");
    }
    else if(heads.size() == 3 && commands[0] == "Client : key_connecting" && heads[1] == "Key" && heads[2] == "Login")
    {
        if(!(client->logined && client->login.compare(phrases[2]) == 0))
        {
            sendToClient(client,"Server : key_connecting denied & Key : " + phrases[1] + " & Information : account not logined");
            return;
        }
        for(int i=0; i<keys.size(); i++)
        {
            if(keys[i]->key == phrases[1])
            {
                if(keys[i]->accCode == "empty")
                {
                    for(int j=0; j<accounts.size(); j++)
                    {
                        if(accounts[j]->login.compare(phrases[2]) == 0)
                        {
                            client->addKey(keys[i]);
                            keys[i]->accCode = accounts[j]->login;
                            keys[i]->rewrite();
                            sendToClient(client,"Server : key_connected & Key : " + keys[i]->key);
                            return;
                        }
                    }
                    sendToClient(client,"Server : key_connecting denied & Key : " + keys[i]->key + " & Information : account not found");
                }
                else if(keys[i]->accCode.compare(phrases[2]) == 0)
                    sendToClient(client,"Server : key_connected & Key : " + keys[i]->key);
                else
                    sendToClient(client,"Server : key_connecting denied & Key : " + keys[i]->key + " & Information : key already connected");
                return;
            }
        }
        sendToClient(client,"Server : key_connecting denied & Key : " + phrases[1] + " & Information : key not found");
    }
    else if(heads.size() == 2 && commands[0] == "Client : key_disconnecting" && heads[1] == "Key")
    {
        for(int i=0; i<client->myKeys.size(); i++)
        {
            if(client->myKeys[i]->key.compare(phrases[1]) == 0)
                client->myKeys.remove(i);
        }
    }
    else if(heads.size()==4 && commands[0] == "Client : registration" && heads[1] == "Login" && heads[2] == "Password" && heads[3] == "Email")
    {
        QStringList problems;
        for(int i=0; i<accounts.size(); i++)
        {
            if(accounts[i]->login.compare(phrases[1]) == 0)
                problems << "login used";
        }
        if(phrases[1].size() < 4)
            problems << "login short";
        if(phrases[2].size() < 6)
            problems << "password short";
        if(problems.isEmpty())
        {
            sendToClient(client,"Server : registrated");
            account* newAccount = new account(phrases[1],phrases[2],phrases[3]);
            accounts << newAccount;
            newAccount->save();
            reload();
        }
        else {
            QString mess = "";
            for(int i=0; i<problems.size(); i++)
            {
                mess += problems[i];
                if(i!=problems.size()-1) mess += "|";
            }
            sendToClient(client,"Server : registration denied & Information : " + mess);
        }
    }
    else if(commands.size() == 3 && commands[0] == "Client : logining" && heads[1] == "Login" && heads[2] == "Password")
    {
        for(int i=0; i<accounts.size(); i++)
        {
            if(accounts[i]->login.compare(phrases[1]) == 0 && accounts[i]->password.compare(phrases[2]) == 0)
            {
                QString mess = "Server : logined";
                client->login = phrases[1];
                client->logined = true;
                if(client->autorizated) for(int j=0; j<keys.size(); j++)
                {
                    for(int k=0; k<client->products.size(); k++)
                    {
                        if(keys[j]->accCode.compare(phrases[1]) == 0 && keys[j]->productType->name.compare(client->products[k]) == 0)
                        {
                            mess += " & Key : " + keys[j]->key;
                        }
                    }
                }
                client->reloadDialogs();
                sendToClient(client,mess);
                return;
            }
        }
        sendToClient(client,"Server : logining denied & Information : account not found");
    }
    else if(commands.size() == 1 && commands[0] == "Client : unlogining")
    {
        client->login = "empty";
        client->logined = false;
        client->myKeys.clear();
        client->reloadDialogs();
    }
    else if(heads.size() == 2 && commands[0] == "Client : licensing" && heads[1] == "Key")
    {
        QVector <productKey*> key;
        bool ok = false;
        QStringList client_keys = phrases[1].split("|");
        for(int k=0; k<client_keys.size(); k++)
        {
            ok = false;
            for(int i=0; i<keys.size(); i++)
            {
            if(keys[i]->key.compare(client_keys[k]) == 0)
                {
                    for(int j=0; j<client->products.size(); j++)
                    {
                        if(keys[i]->productType->name.compare(client->products[j]) == 0)
                        {
                            key << keys[i];
                            ok = true;
                            client->addKey(keys[i]);
                        }
                    }
                }
            }
            if(!ok)
                sendToClient(client,"Server : licensing denied & Key : " + client_keys[k] + " & Information : license not found");
        }
        for(int i=0; i<key.size(); i++)
        {
            if(key[i]->productType->sellType.compare(sellTypes[0]) == 0 || key[i]->productType->sellType.compare(sellTypes[1]) == 0)
                sendToClient(client,"Server : licensed & Key : " + key[i]->key + " & Product : " + key[i]->productType->name + " & License : unlimited");
            else if(key[i]->isActual())
            {
                QString str = "Server : licensed & Key : " + key[i]->key + " & Product : " + key[i]->productType->name + " & License : limited & Date : %1.%2.%3.%4.%5.%6";
                QString mess = str.arg(key[i]->endDateLicense.year())
                                  .arg(key[i]->endDateLicense.month())
                                  .arg(key[i]->endDateLicense.day())
                                  .arg(key[i]->endTimeLicense.hour())
                                  .arg(key[i]->endTimeLicense.minute())
                                  .arg(key[i]->endTimeLicense.second());
                sendToClient(client,mess);
            }
            else
                sendToClient(client,"Server : licensing denied & Key : " + key[i]->key + " & Information : license is over & Product : " + key[i]->productType->name);
        }
    }
    else if(heads.size() == 1 && client->autorizated && commands[0] == "Client : synchronization")
    {
        for(int i=0; i<keys.size(); i++)
            for(int j=0; j<client->myKeys.size(); j++)
            {
                if(keys[i]->key.compare(client->myKeys[j]->key) == 0)
                {
                    if(keys[i]->productType->sellType == sellTypes[0] || keys[i]->productType->sellType == sellTypes[1])
                        sendToClient(client,"Server : licensed & Key : " + keys[i]->key + " & Product : " + keys[i]->productType->name + " & License : unlimited");
                    else if(keys[i]->isActual())
                    {
                        QString str = "Server : licensed & Key : " + keys[i]->key + " & Product : " + keys[i]->productType->name + " & License : limited & Date : %1.%2.%3.%4.%5.%6";
                        QString mess = str.arg(keys[i]->endDateLicense.year())
                                          .arg(keys[i]->endDateLicense.month())
                                          .arg(keys[i]->endDateLicense.day())
                                          .arg(keys[i]->endTimeLicense.hour())
                                          .arg(keys[i]->endTimeLicense.minute())
                                          .arg(keys[i]->endTimeLicense.second());
                        sendToClient(client,mess);
                    }
                    else
                        sendToClient(client,"Server : licensing denied & Key : " + keys[i]->key + " & Information : license is over & Product : " + keys[i]->productType->name);
                }
            }
    }
    else if(heads.size() == 2 && client->autorizated && commands[0] == "Client : information")
    {

    }
}

void ServerMainWindow::readClient()
{
    QString message;
    ClientSocket* client = (ClientSocket*)sender();
    QDataStream in(client->socket);
    in.setVersion(QDataStream::Qt_4_2);

    for (;;) {
            if (!m_nNextBlockSize) {
                if (client->socket->bytesAvailable() < sizeof(quint16)) {
                    break;
                }
                in >> m_nNextBlockSize;
            }

            if (client->socket->bytesAvailable() < m_nNextBlockSize) {
                break;
            }
            in >> message;
            m_nNextBlockSize = 0;

        }

    client->dialog << message;
    client->reloadDialogs();
    parseMessage(client,message);
}

void ServerMainWindow::sendToClient(ClientSocket *client, QString message)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);

    out << quint16(0) << message;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    client->socket->write(arrBlock);
    client->dialog << message;
    client->reloadDialogs();
}

void ServerMainWindow::synchronization()
{
    ClientSocket* client = (ClientSocket*)sender();
    sendToClient(client, "Server : synchronization");
}
