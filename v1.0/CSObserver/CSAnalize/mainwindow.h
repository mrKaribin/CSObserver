#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSslSocket>
#include <QtWebEngine>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
    QLineEdit* site = new QLineEdit(this);
    QTextEdit* resHtml = new QTextEdit("Comp. version: " + QSslSocket::sslLibraryBuildVersionString() + " || Real version: " + (QSslSocket::supportsSsl() ? QSslSocket::sslLibraryVersionString() : "Not connected") ,this);
    QWebEngineView* resSite = new QWebEngineView(this);
    QWebEnginePage* page = new QWebEnginePage();
    QLabel* status = new QLabel("Enter site",this);

private:
    bool error=false;

signals:
    void rHtml(QString html);

private slots:
    void downloadSite();
    void loadingStatus(int i);
    void isComplete();

};

#endif // MAINWINDOW_H
