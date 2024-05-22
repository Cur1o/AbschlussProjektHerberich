#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QSplashScreen *splash = new QSplashScreen;              //…dann erst den Splash-Screen
    splash->setPixmap(QPixmap(":/img/QtLogo.PNG").scaled(512,512));           //splash picture setzen
    splash->show();
    QTimer::singleShot(2000, splash, SLOT(close()));
    return a.exec();
}
