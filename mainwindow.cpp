#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addtask.h"
#include <QStringListModel>
#include <QDropEvent>


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

    // ui->lvw1ToDo->setDragEnabled(true);
    // ui->lvw2Progress->setDragEnabled(true);
    // ui->lvw3Done->setDragEnabled(true);

    // ui->lvw1ToDo->setAcceptDrops(true);
    // ui->lvw2Progress->setAcceptDrops(true);
    // ui->lvw3Done->setAcceptDrops(true);

    // ui->lvw1ToDo->setDropIndicatorShown(true);
    // ui->lvw2Progress->setDropIndicatorShown(true);
    // ui->lvw3Done->setDropIndicatorShown(true);

    // ui->lvw1ToDo->setDefaultDropAction(Qt::MoveAction);
    // ui->lvw2Progress->setDefaultDropAction(Qt::MoveAction);
    // ui->lvw3Done->setDefaultDropAction(Qt::MoveAction);

    ui->lvw1ToDo->setModel(ModelTODO);
    ui->lvw2Progress->setModel(ModelPROGRESS);
    ui->lvw3Done->setModel(ModelDONE);

    ui->lvw1ToDo->setStyleSheet("QListView::Item{background-color: #d4748b}");
    ui->lvw2Progress->setStyleSheet("QListView::Item{background-color: #fca644}");
    ui->lvw3Done->setStyleSheet("QListView::Item{background-color: #70e043}");

    dbManager = new DatabaseManager();
    BuildListView();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAutoSpeichern_toggled(bool arg1)
{
    //Evt Speichet Alle 5 Min or so
}

void MainWindow::on_actionSpeichern_2_triggered()
{

}

void MainWindow::on_actionDeutsch_toggled(bool arg1)
{
 // Change Language to German
    // ui->actionDeutsch->setChecked(arg1);

}

void MainWindow::on_actionEnglisch_toggled(bool arg1)
{
 //Change Language to Englisch

    // ui->actionEnglisch->setChecked(arg1);
}

void MainWindow::on_btnFirstToSecond_clicked()
{
    int index = ui->lvw1ToDo->currentIndex().row();
    dbManager->ChangeValueInListToList(1, 2, index);
    BuildListView();
}


void MainWindow::on_btnSecondToFirst_clicked()
{
    int index = ui->lvw2Progress->currentIndex().row();
    dbManager->ChangeValueInListToList(2, 1, index);
    BuildListView();
}


void MainWindow::on_btnSecondToThird_clicked()
{
    int index = ui->lvw2Progress->currentIndex().row();
    dbManager->ChangeValueInListToList(2, 3, index);
    BuildListView();
}


void MainWindow::on_btnThirdToSecond_clicked()
{
    int index = ui->lvw3Done->currentIndex().row();
    dbManager->ChangeValueInListToList(3, 2, index);
    BuildListView();
}


void MainWindow::on_btnAdd_clicked()
{
    TaskElement newTask;
    AddTask *taskDialog = new AddTask(newTask, false, this);

    if (taskDialog->exec() == QDialog::Accepted) {
        TaskElement resultTask = taskDialog->getTask();
        dbManager->ADDItemToDatabase(resultTask);
        BuildListView();
    }
    delete taskDialog;
}


void MainWindow::on_btnDetails_clicked()
{
    int row = ui->lvw1ToDo->currentIndex().row();
    TaskElement newTask = dbManager->getTask(1, row);
    AddTask *taskDialog = new AddTask(newTask, true, this);

    if (taskDialog->exec() == QDialog::Accepted) {
        TaskElement resultTask = taskDialog->getTask();
        // qDebug() << resultTask.getTitle();
        // qDebug() << resultTask.getBegin();
        // qDebug() << resultTask.getEnd();
        // qDebug() << resultTask.getDuration();
        // qDebug() << resultTask.getState();
        // qDebug() << resultTask.getRemark();
        qDebug() << resultTask.getID();
        dbManager->UpdateItem(resultTask);
    }
    delete taskDialog;

}


void MainWindow::on_btnEnd_clicked()
{
    //TODO: Save All
    //TODO: End Programm
}

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

//Extra Methods
void MainWindow::AddItemToList(TaskElement element){
    State currentState = element.getState();
    if(currentState+1 == 1)AddItem(ModelTODO, element.getID(),element.getTitle());
    if(currentState+1 == 2)AddItem(ModelPROGRESS, element.getID(),element.getTitle());
    if(currentState+1 == 3)AddItem(ModelDONE, element.getID(),element.getTitle());
}

void MainWindow::AddItem(QStandardItemModel *model, int id, const QString &name)
{
    QStandardItem *item = new QStandardItem(QString("%1 - %2").arg(id).arg(name));
    item->setData(id, Qt::UserRole +1);
    model->appendRow(item);
}

// void MainWindow::RemoveItemFromList(QStandardItemModel *model, int id) {
//     for (int row = 0; row < model->rowCount(); ++row) {
//         QStandardItem *item = model->item(row);
//         if (item->data(Qt::UserRole + 1).toInt() == id) {
//             model->removeRow(row);
//             break;
//         }
//     }
// }

// void MainWindow::UpdateTaskState(int id, State newState) {
//     for (TaskElement &task : dbManager->getTasks()) {
//         if (task.getID() == id) {
//             task.setState(newState);
//             break;
//         }
//     }
// }

// void MainWindow::dropEvent(QDropEvent *event) {
//     QListView *source = qobject_cast<QListView*>(event->source());
//     if (source) {
//         QModelIndex index = source->currentIndex();
//         int id = index.data(Qt::UserRole + 1).toInt();
//         QString title = index.data(Qt::DisplayRole).toString();

//         QStandardItemModel *sourceModel = qobject_cast<QStandardItemModel*>(source->model());
//         QStandardItemModel *targetModel = nullptr;

//         if (sourceModel) {
//             // Ermittle das Zielmodell basierend auf dem Zielobjekt
//             if (ui->lvw1ToDo->underMouse())
//                 targetModel = ModelTODO;
//             else if (ui->lvw2Progress->underMouse())
//                 targetModel = ModelPROGRESS;
//             else if (ui->lvw3Done->underMouse())
//                 targetModel = ModelDONE;

//             if (targetModel) {
//                 // Entferne das Element aus dem Quellmodell
//                 RemoveItemFromList(sourceModel, id);

//                 // Füge das Element zum Zielmodell hinzu
//                 AddItem(targetModel, id, title);

//                 // Aktualisiere den Zustand des Elements
//                 State newState = TODO;
//                 if (targetModel == ModelPROGRESS)
//                     newState = PROGRESS;
//                 else if (targetModel == ModelDONE)
//                     newState = DONE;
//                 UpdateTaskState(id, newState);

//                 event->accept();
//             }
//         }
//     }
// }

