#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QSettings>

class CustomSplashScreen : public QSplashScreen {
public:
    CustomSplashScreen(const QPixmap &pixmap, const QString &topMessage, const QString &bottomMessage, QWidget *parent = nullptr)
        : QSplashScreen(pixmap, Qt::WindowStaysOnTopHint) {
        QLabel *topMessageLabel = new QLabel(topMessage, this);
        topMessageLabel->setAlignment(Qt::AlignCenter);
        topMessageLabel->setStyleSheet("QLabel { color : white; font-size: 24px; }");

        QLabel *bottomMessageLabel = new QLabel(bottomMessage, this);
        bottomMessageLabel->setAlignment(Qt::AlignCenter);
        bottomMessageLabel->setStyleSheet("QLabel { color : white; font-size: 24px; }");

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(topMessageLabel);
        layout->addStretch();  // Adds space between the labels
        layout->addWidget(bottomMessageLabel);
        layout->setAlignment(topMessageLabel, Qt::AlignTop);
        layout->setAlignment(bottomMessageLabel, Qt::AlignBottom);
        setLayout(layout);
    }
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QTranslator translator;
    QSettings registry("HKEY_LOCAL_MACHINE\\SOFTWARE\\MYEDITOR", QSettings::IniFormat);

    QString lang = registry.value("lang").toString(); //Reading Registry
    lang = "en";

    if(lang == "en") // dicision which translation to take
    { //translate to english
        QVariant var = translator.load(":/lang/translate_en.qm");//load translator file...
        a.installTranslator(&translator); //... and install
    }
    else if(lang == "de")
    {
        //translate to german
        QVariant var = translator.load(""); //Don't load, then standard language
        a.installTranslator(&translator);
    }

    // Erstellen des Splash-Screens mit einem oberen und einem unteren Label
    QPixmap pixmap(":/img/QtLogo.PNG");
    CustomSplashScreen *splash = new CustomSplashScreen(pixmap.scaled(512, 512), "Herberich Sandro", "Starting Application...");
    splash->show();

    // Warten für 5 Sekunden bevor das Hauptfenster angezeigt wird
    QTimer::singleShot(5000, splash, SLOT(close()));

    MainWindow w;

    // Zeigt das Hauptfenster nach dem Schließen des Splash-Screens
    QTimer::singleShot(5000, &w, SLOT(show()));

    return a.exec();
}


