#ifndef SPLASCHSCREEN_H
#define SPLASCHSCREEN_H

#include <QWidget>

namespace Ui {
class SplaschScreen;
}

class SplaschScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SplaschScreen(QWidget *parent = nullptr);
    ~SplaschScreen();

private:
    Ui::SplaschScreen *ui;
};

#endif // SPLASCHSCREEN_H
