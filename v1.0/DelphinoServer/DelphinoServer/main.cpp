#include "mainwindow.h"
#include <QApplication>
#include <QStringList>
#include <QSqlDatabase>

extern ServerMainWindow* serverWindow;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QMessageBox::critical(0,"Database error","Can not save info: " + base.lastError().text());
    serverWindow = new ServerMainWindow(8181);
    serverWindow->show();

    return a.exec();
}
