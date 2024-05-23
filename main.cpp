#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>

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

    QPixmap pixmap(":/img/QtLogo.PNG");
    CustomSplashScreen *splash = new CustomSplashScreen(pixmap.scaled(512, 512), "Herberich Sandro", "Starting Application...");
    splash->show();

    QTimer::singleShot(5000, splash, SLOT(close()));

    MainWindow w;

    QTimer::singleShot(5000, &w, SLOT(show()));

    return a.exec();
}


