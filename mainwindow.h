#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "taskelement.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include "databasemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadLanguage(const QString &language);

    void on_actionDeutsch_toggled(bool arg1);

    void on_actionEnglisch_toggled(bool arg1);

    void on_btnFirstToSecond_clicked();

    void on_btnSecondToFirst_clicked();

    void on_btnSecondToThird_clicked();

    void on_btnThirdToSecond_clicked();

    void on_btnAdd_clicked();

    void on_btnDetails_clicked();

    void on_btnEnd_clicked();

    void BuildListView();

    void AddItemToList(TaskElement element);
    void AddItem(QStandardItemModel *model, int id, const QString &name);

    void on_lvw1ToDo_clicked(const QModelIndex &index);

    void on_lvw2Progress_clicked(const QModelIndex &index);

    void on_lvw3Done_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *ModelTODO;
    QStandardItemModel *ModelPROGRESS;
    QStandardItemModel *ModelDONE;
    int currentID = 1;
    TaskElement *currentTask;
    DatabaseManager *dbManager;


};
#endif // MAINWINDOW_H
