#include "mainwindow.h"
#include <QtNetwork/QSslSocket>
#include <QNetworkCookie>


MainWindow::MainWindow()
{
    setGeometry(400,400,1030,550);
    resHtml->setGeometry(10,10,500,400);
    resSite->setGeometry(520,10,500,400);
    status->setGeometry(10,420,500,50);
    site->setGeometry(10,480,1010,30);

    connect(resSite,SIGNAL(loadFinished(bool)),this,SLOT(isComplete()));
    connect(resSite,SIGNAL(loadProgress(int)),this,SLOT(loadingStatus(int)));
    connect(site,SIGNAL(returnPressed()),this,SLOT(downloadSite()));
}

void MainWindow::downloadSite()
{
    qDebug() << "Finding content..." << endl;
    status->setText("Finding...");

    resSite->load(QUrl(site->text()));
}

void MainWindow::loadingStatus(int i)
{
    status->setText("Загрузка " + QString::number(i) + "%");
}

void MainWindow::isComplete()
{
    qDebug() << "Content downloaded" << endl;
    status->setText("Complete");

    page = resSite->page();
    site->setText(page->url().toString());
    page->toHtml([this](const QString& result){
        QString data = result;
        resHtml->setPlainText(data);
    });
    resSite->show();
}

MainWindow::~MainWindow()
{

}
