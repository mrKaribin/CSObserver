#ifndef DELPHINOSYNCRO_H
#define DELPHINOSYNCRO_H

#include <QDebug>
#include <QObject>
#include <QWidget>
#include <QApplication>
#include <QDesktopWidget>
#include <QDate>
#include <QTime>
#include <QTimer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QTcpSocket>
#include <QHostAddress>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QMouseEvent>


class KeyWidget : public QWidget
{
    Q_OBJECT
public:
    KeyWidget(QString _key, QString _product, QString _license);
    bool isActive();
    bool isLicensed();

    QString key = "";
    QString product = "";
    void* object;

private:
    QLabel* key_label = new QLabel();
    QLabel* product_label = new QLabel();
    QPushButton* destroy = new QPushButton("");
    QPushButton* activity = new QPushButton("");

    QString destroyIcon = "delete.png";
    QString activityIcon1 = "play.png";
    QString activityIcon2 = "pause.png";
    int iconSize = 20;
    bool activated = false;
    bool licensed = false;

public slots:
    void productDestroyed();
    void destroyClicked();
    void activityClicked();
    void active(bool is);
    void license(bool is);

signals:
    void destroyedThis(QString product);
    void destroyProg();
    void destroyThis(QString key);
    void turnOn(QString product);
    void turnOff(QString product);

};

class Delphinosyncro : public QWidget
{
    Q_OBJECT
public:
    Delphinosyncro();
    
private:
    void swapToSpace(QWidget* wgt);
    void ConnectDatabase();
    void ReadDatabase();
    void SaveDatabase();
    void reloadKeysLay();
    void haveAccount(bool have);
    void haveKey(bool have);
    void addKey(QString key);
    void editKey(QString key, QString product, QString license);
    void addNotice(QString head, QString body);
    void WriteDate(QString s, QString f);

    QSqlDatabase base;
    QTcpSocket* socket;
    QTimer *timer = new QTimer();
    QTimer *exitTimeout = new QTimer();
    QTimer *closeTimeout = new QTimer();
    QTimer *connectionCheck = new QTimer();
    QWidget* loading = new QWidget(this);
    QWidget* mainspace = new QWidget(this);
    QWidget* keyspace = new QWidget(this);
    QWidget* loginspase = new QWidget(this);
    QWidget* registrationspace = new QWidget(this);
    QWidget* activespace;
    QVector <QWidget*> notice;
    QSystemTrayIcon* trayIcon = new QSystemTrayIcon();
    QMenu* trayMenu = new QMenu();
    QVBoxLayout* keyslay = new QVBoxLayout();
    QLabel* mainsp1head1 = new QLabel("Логин:");
    QLabel* mainsp1data1 = new QLabel();
    QLabel* mainsp1head2 = new QLabel("Пароль:");
    QLabel* mainsp1data2 = new QLabel();
    QLabel* mainsp1head3 = new QLabel("Аккаунт не привязан");
    QLabel* mainsp2head2 = new QLabel("Ключ не привязан");
    QLabel* loadInfo = new QLabel();
    QLabel* loadAlarmInfo = new QLabel();
    QLineEdit* key = new QLineEdit();
    QLineEdit* login = new QLineEdit();
    QLineEdit* password = new QLineEdit();
    QLineEdit* newlogin = new QLineEdit();
    QLineEdit* newpassword = new QLineEdit();
    QLineEdit* newemail = new QLineEdit();
    QPushButton* keyEdit = new QPushButton("Добавить");
    QPushButton* accEdit = new QPushButton("Войти");
    QCheckBox* atrun = new QCheckBox("Запускать автоматически");
    

    QPoint mousePos;
    QString myLogin = "empty";
    QString myPassword = "empty";
    QString logoAdr = "logo.png";
    QString lastSocketError = "";
    QTime lastSocketErrorTime;
    QStringList myKey;
    QStringList myLicense;
    QStringList myProduct;
    QVector <KeyWidget*> myKeyWidget;

    int wx = 0, wy = 0, ww = 500, wh = 300, key_activating = 0, errorsCount = 0;
    quint16 m_nNextBlockSize = 0;
    bool autorun = false;
    bool isInterface = true;
    bool isLoadComplete = false;
    bool isLoading = false;
    bool isAutorization = false;
    bool isActivating = false;
    bool isLogining = false;
    bool isRegistration = false;
    bool isFirstStart = true;
    bool isPressed = false;

// class interface -----------------------------------------------------------------------------------

    int screen_width = 1300,
        screen_height = 750,
        window_x = 0,
        window_y = 0,
        window_width = 500,
        window_height = 300,
        notice_body_size = 9,
        notice_head_size = 12,
        notice_width = 250,
        notice_height = 100,
        iconSize = 15;

    quint16 port = 10351;
    QString host = "delphino.ddnsking.com";
    QString protocol = "Protocol : v1.0";
    QStringList products = {"CSObserver", "CSObserverFree"};
    QStringList versions = {"beta.1.0", "beta.1.0"};
    QString closeIcon = "delete.png";
    QString hideIcon = "hide.png";

    QString createAutorizationMessage();

// ---------------------------------------------------------------------------------------------------

protected:
    virtual void mousePressEvent ( QMouseEvent * event );
    virtual void mouseReleaseEvent ( QMouseEvent * event );
    virtual void mouseMoveEvent ( QMouseEvent * event );

public slots:
    void startLoading(QString mess);
    void finishLoading();
    void openMainSpace();
    void openKeySpace();
    void openLoginSpace();
    void openRegistrationSpace();
    void isAutorun(int ar);
    void exitFromAccount();
    void deleteKey(QString _key);
    void connected();
    void hostFounded();
    void connectingError(QAbstractSocket::SocketError);
    void reconnectTimeout();
    void checkConnection();
    void reading();
    void writing(QString command);
    void activating();
    void activatingAll();
    void runAll();
    void logining();
    void registration();
    void turnOnProduct(QString name);
    void turnOffProduct(QString name);
    void trayIconClicked(QSystemTrayIcon :: ActivationReason reason);
    void launcherShowHide();
    void closeLauncher();
};

#endif // DELPHINOSYNCRO_H
