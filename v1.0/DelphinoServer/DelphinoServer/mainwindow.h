#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTime>
#include <QDate>
#include <QWidget>
#include <QApplication>
#include <QDesktopWidget>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QTabWidget>
#include <QScrollArea>
#include <QtSql>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTcpServer>
#include <QTcpSocket>

class ServerMainWindow;


class product : QObject
{
    Q_OBJECT
public:
    product();
    product(int code, QString nm, QString sType, QString version, int cost);
    QWidget* getWidget();

    QWidget* myWidget = NULL;

    int code = 0;
    QString name = "";
    QString sellType = "";
    QString version = "";
    int cost;

    bool save();
    bool rewrite();
    bool clean();

private:

public slots:
    void correct();
    void changed();
    void destroy();
};

class ProductManager : public QWidget
{
    Q_OBJECT
public:
    ProductManager();
    ProductManager(product* prod);
    ~ProductManager();

private:
    void init();

    QLineEdit* name;
    QComboBox* sellType;
    QLineEdit* version;
    QSpinBox* cost;
    QPushButton* back;
    QPushButton* ok;

    product* prod;
    bool creation = false;

public slots:
    void operation();
    void setName(QString nm);
    void setSellType(QString type);
    void setVersion(QString vers);
    void setCost(int i);
};

class productKey : QObject
{
    Q_OBJECT
public:
    productKey();
    productKey(int code, product* prod, QString accLog, QString key, int year, int month, int day, int hour, int minute, int second);
    QWidget* getWidget();

    QWidget* myWidget = NULL;

    int code;
    QString accCode = "empty";
    product* productType;
    QString key;
    QTime endTimeLicense;
    QDate endDateLicense;

    bool isActual();
    bool save();
    bool rewrite();
    bool clean();

private:

public slots:
    void correct();
    void destroy();
    void extension();
};

class KeyManager : public QWidget
{
    Q_OBJECT
public:
    KeyManager();
    KeyManager(productKey* key);
    ~KeyManager();

private:
    void init();

    QSpinBox* count;
    QLabel* key;
    QComboBox* prod;
    QComboBox* accLog;
    QPushButton* back;
    QPushButton* ok;

    productKey* myKey;
    QVector <productKey*> myKeys;
    bool creation = true;

public slots:
    void operation();
    void createKey(int i);
    void setProd(int ind);
    void setAcc(QString acc);

};

class account : QObject
{
    Q_OBJECT
public:
    account();
    account(QString name, QString pass, QString eml);
    QWidget* getWidget();

    QWidget* myWidget = NULL;

    QString login = "";
    QString password = "";
    QString email = "";
    QVector <productKey*> keys;

    bool save();
    bool rewrite();
    bool clean();

private:

public slots:
    void correct();
    void changed();
    void destroy();
};

class AccountManager : public QWidget
{
    Q_OBJECT
public:
    AccountManager();
    AccountManager(account* acc);
    ~AccountManager();

private:
    void init();

    QLineEdit* login;
    QLineEdit* password;
    QLineEdit* email;
    QPushButton* back;
    QPushButton* ok;

    account* myAcc;
    bool creation = true;

public slots:
    void operation();
    void setLogin(QString log);
    void setPassword(QString pass);
    void setEmail(QString email);

};

class ClientSocket : public QObject
{
    Q_OBJECT
public:
    ClientSocket(QTcpSocket*);
    ~ClientSocket();

    QTcpSocket* socket;
    QTimer* synchroTimer = new QTimer();
    void addKey(productKey* key);
    bool haveAccount();
    productKey* getKeyForProduct(QString productName);
    QPushButton* getDialogHeader();
    QWidget* getDialogFull();
    
    bool autorizated = false;
    bool logined = false;
    QStringList products;
    QString login = "empty";
    QStringList dialog;
    QLabel* DialogHeaderLabel = new QLabel();
    QLabel* DialogHeaderHeader = new QLabel();
    QLabel* DialogFullHeader = new QLabel();
    QVBoxLayout* DialogFullLayout = new QVBoxLayout();
    QVector <productKey*> myKeys;

private:
    QPushButton* myDialogHeader = 0;
    QWidget* myDialogFull = 0;

    int lastDialogInFull = 0;

//--------------------------------------------------------------------------------------------------------------------

    int DialogFullWidth = 600,
        DialogFullHeight = 400,
        DialogFullSpase = 400,
        DialogHeaderWidth = 600,
        DialogHeaderHeight = 60;

//--------------------------------------------------------------------------------------------------------------------

public slots:
    void reloadDialogs();
    void createFull();

signals:
    void synchronization();
    void connected();
    void readyRead();
    void disconnected();
};

class ServerMainWindow : public QWidget
{
    Q_OBJECT

public:
    ServerMainWindow(int port);
    ~ServerMainWindow();
    bool DatabaseInit();
    bool ReadDatabase();
    void createDialogsArea();
    void createAccountsArea();
    void createKeysArea();
    void createProductsArea();
    void parseMessage(ClientSocket* client, QString message);

    QString createKey();
    int createProductCode();
    int createKeyCode();

    void delProduct(product*);
    void delKey(productKey*);
    void delAccount(account*);
    void addProduct(product*);
    void addKey(productKey*);
    void addAccount(account*);
    product* getProduct(int i);
    productKey* getKey(int i);
    account* getAccount(int i);
    QVector <product*> getProducts();
    QVector <productKey*> getKeys();
    QVector <account*> getAccounts();

private:
    QTcpServer* server;
    QTabWidget* tab;
    QPushButton* add;
    QPushButton* rel;
    QVBoxLayout* dialogsLay;
    QVBoxLayout* accountsLay;
    QVBoxLayout* keysLay;
    QVBoxLayout* productsLay;

    QVector <ClientSocket*> clients;
    QVector <product*> products;
    QVector <productKey*> keys;
    QVector <account*> accounts;
    product* emptyProd = new product(0,"пусто","пусто","пусто",0);
    QTimer* timer;
    int activeTab = 0;
    quint16 m_nNextBlockSize = 0;

    product* findProduct(int code);
    QVector <productKey*> findAccKeys(QString name);

    void sendToClient(ClientSocket* client, QString message);

    //--------------------------------------------------------------------------------------------------------------------

        int _InterfaceUpdateTime = 10000;

    //--------------------------------------------------------------------------------------------------------------------

public slots:
    void newConnection();
    void delConnection();
    void readClient();
    void synchronization();
    void setTab(int i);
    void reload();
    void addNew();

};

#endif // MAINWINDOW_H
