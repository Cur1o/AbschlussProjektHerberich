#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addtask.h"
#include <QStringListModel>
#include <QTranslator>
#include <QToolTip>

QTranslator translator;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ModelTODO = new QStandardItemModel(0,2,this);
    ModelPROGRESS = new QStandardItemModel(0,2,this);
    ModelDONE = new QStandardItemModel(0,2,this);

    ModelTODO->setHorizontalHeaderLabels({"ID", "Bezeichnung"});
    ModelPROGRESS->setHorizontalHeaderLabels({"ID", "Bezeichnung"});
    ModelDONE->setHorizontalHeaderLabels({"ID", "Bezeichnung"});

    ui->lvw1ToDo->setModel(ModelTODO);
    ui->lvw2Progress->setModel(ModelPROGRESS);
    ui->lvw3Done->setModel(ModelDONE);

    ui->lvw1ToDo->setStyleSheet("QListView::Item{background-color: #d4748b}");
    ui->lvw2Progress->setStyleSheet("QListView::Item{background-color: #fca644}");
    ui->lvw3Done->setStyleSheet("QListView::Item{background-color: #70e043}");

    dbManager = new DatabaseManager();
    BuildListView();
    currentTask = new TaskElement();

    ui->actionDeutsch->setChecked(true);
    loadLanguage("de");
}

MainWindow::~MainWindow()
{
    delete ui;
}

//This switches the language in real time witout restarting the programm
void MainWindow::loadLanguage(const QString &language)
{
    if (!translator.load(":/language/translate_" + language + ".qm")) {
        qWarning() << "Could not load translation file for" << language;
        return;
    }

    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
}

//If the German menu is toggeld the Language is switched To German
void MainWindow::on_actionDeutsch_toggled(bool checked)
{
    if (checked) {
        loadLanguage("de");
        ui->actionEnglisch->setChecked(false);
    }
}

//If the Englisch menu is toggeld the language is switched to Englisch
void MainWindow::on_actionEnglisch_toggled(bool checked)
{
    if (checked) {
        loadLanguage("en");
        ui->actionDeutsch->setChecked(false);
    }
}
//Moves Item from List 1 to 2
void MainWindow::on_btnFirstToSecond_clicked()
{
    int index = ui->lvw1ToDo->currentIndex().row();
    dbManager->ChangeValueInListToList(1, 2, index);
    BuildListView();
}

//Moves Item from List 2 to 1
void MainWindow::on_btnSecondToFirst_clicked()
{
    int index = ui->lvw2Progress->currentIndex().row();
    dbManager->ChangeValueInListToList(2, 1, index);
    BuildListView();
}

//Moves Item from List 2 to 3
void MainWindow::on_btnSecondToThird_clicked()
{
    int index = ui->lvw2Progress->currentIndex().row();
    dbManager->ChangeValueInListToList(2, 3, index);
    BuildListView();
}

//Moves Item from List 3 to 2
void MainWindow::on_btnThirdToSecond_clicked()
{
    int index = ui->lvw3Done->currentIndex().row();
    dbManager->ChangeValueInListToList(3, 2, index);
    BuildListView();
}

//Creates a Net TaskElement
void MainWindow::on_btnAdd_clicked()
{
    TaskElement newTask;
    AddTask *taskDialog = new AddTask(newTask, this);

    if (taskDialog->exec() == QDialog::Accepted) {
        TaskElement resultTask = taskDialog->getTask();
        dbManager->ADDItemToDatabase(resultTask);
        BuildListView();
    }
    delete taskDialog;
}

//Edits a existing TaskElement
void MainWindow::on_btnDetails_clicked()
{
    //The Way Before the clobaly saved variable
    // int row = ui->lvw1ToDo->currentIndex().row();
    // TaskElement newTask = dbManager->getTask(1, row);
    // AddTask *taskDialog = new AddTask(newTask, this);

    AddTask *taskDialog = new AddTask(*currentTask, this);

    if (taskDialog->exec() == QDialog::Accepted) {
        TaskElement resultTask = taskDialog->getTask();
        dbManager->UpdateItem(resultTask);
        BuildListView();
    }
    delete taskDialog;
}

//Closes the programm no saving needed
void MainWindow::on_btnEnd_clicked()
{
    close();
}

//Extra Methods -------------------------------------------------------------------------

//Here the items for the ListView are sorted with the state
void MainWindow::BuildListView(){
    ui->lvw1ToDo->model()->removeRows(0, ui->lvw1ToDo->model()->rowCount());
    ui->lvw2Progress->model()->removeRows(0, ui->lvw2Progress->model()->rowCount());
    ui->lvw3Done->model()->removeRows(0, ui->lvw3Done->model()->rowCount());
    foreach (auto item, dbManager->getTasks(1)) {
        AddItemToList(item);
    }
    foreach (auto item, dbManager->getTasks(2)) {
        AddItemToList(item);
    }
    foreach (auto item, dbManager->getTasks(3)) {
        AddItemToList(item);
    }
}

//The UI gets created
void MainWindow::AddItemToList(TaskElement element){
    State currentState = element.getState();
    if(currentState+1 == 1)AddItem(ModelTODO, element.getID(),element.getTitle());
    if(currentState+1 == 2)AddItem(ModelPROGRESS, element.getID(),element.getTitle());
    if(currentState+1 == 3)AddItem(ModelDONE, element.getID(),element.getTitle());
}

//The formating of the List Element
void MainWindow::AddItem(QStandardItemModel *model, int id, const QString &name)
{
    QStandardItem *item = new QStandardItem(QString("%1 - %2").arg(id).arg(name));
    item->setData(id, Qt::UserRole +1);
    model->appendRow(item);
}

//The building of the tooltip
QString getTaskDetails(TaskElement &task) {
    return QString("ID: %1\nTitle: %2\nHours: %3\nBegin:  %4\nEnd: %5")
        .arg(task.getID())
        .arg(task.getTitle())
        .arg(task.getDuration())
        .arg(task.getBegin().toString())
        .arg(task.getEnd().toString());
}

//Managment of the tooltip cration and sets the last clicked object to current Task
void MainWindow::showTaskTooltip(const QModelIndex &index, int listType) {
    TaskElement selectedTask = dbManager->getTask(listType, index.row());
    *currentTask = selectedTask;

    QString tooltipText = getTaskDetails(selectedTask);
    QToolTip::showText(QCursor::pos(), tooltipText);
}

//calls tooltip creation with the current model 1
void MainWindow::on_lvw1ToDo_clicked(const QModelIndex &index)
{
    showTaskTooltip(index, 1);
}

//calls tooltip creation with the current model 2
void MainWindow::on_lvw2Progress_clicked(const QModelIndex &index)
{
    showTaskTooltip(index, 2);
}

//calls tooltip creation with the current model 3
void MainWindow::on_lvw3Done_clicked(const QModelIndex &index)
{
    showTaskTooltip(index, 3);
}

