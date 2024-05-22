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

    ui->lvw1ToDo->setDragEnabled(true);
    ui->lvw2Progress->setDragEnabled(true);
    ui->lvw3Done->setDragEnabled(true);

    ui->lvw1ToDo->setAcceptDrops(true);
    ui->lvw2Progress->setAcceptDrops(true);
    ui->lvw3Done->setAcceptDrops(true);

    ui->lvw1ToDo->setDropIndicatorShown(true);
    ui->lvw2Progress->setDropIndicatorShown(true);
    ui->lvw3Done->setDropIndicatorShown(true);

    ui->lvw1ToDo->setDefaultDropAction(Qt::MoveAction);
    ui->lvw2Progress->setDefaultDropAction(Qt::MoveAction);
    ui->lvw3Done->setDefaultDropAction(Qt::MoveAction);

    ui->lvw1ToDo->setModel(ModelTODO);
    ui->lvw2Progress->setModel(ModelPROGRESS);
    ui->lvw3Done->setModel(ModelDONE);

    ui->lvw1ToDo->setStyleSheet("QListView::Item{background-color: #d4748b}");
    ui->lvw2Progress->setStyleSheet("QListView::Item{background-color: #fca644}");
    ui->lvw3Done->setStyleSheet("QListView::Item{background-color: #70e043}");

    dbManager = new DatabaseManager();
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
    ModelPROGRESS->appendRow(ModelTODO->item(ui->lvw1ToDo->currentIndex().row()));
    ModelTODO->removeRow(ui->lvw1ToDo->currentIndex().row());

    qDebug() << ModelTODO->item(ui->lvw1ToDo->currentIndex().row());
    // QModelIndex sourceIndex = ui->lvw1ToDo->currentIndex();
    // QModelIndex targetIndex = ui->lvw2Progress->currentIndex();

    // // Sicherstellen, dass beide Indizes gültig sind
    // if (sourceIndex.isValid() && targetIndex.isValid()) {
    //     // Dateninhalt des ausgewählten Elements im Quellmodell abrufen
    //     QVariant data = ui->lvw1ToDo->model()->data(sourceIndex);

    //     // Element aus dem Quellmodell entfernen
    //     ui->lvw1ToDo->model()->removeRow(sourceIndex.row());

    //     // Element zum Zielmodell hinzufügen
    //     ui->lvw2Progress->model()->insertRow(targetIndex.row(), QModelIndex()); // Neue Zeile im Zielmodell einfügen
    //     QModelIndex newIndex = ui->lvw2Progress->model()->index(targetIndex.row(), 0); // Index der neuen Zeile abrufen
    //     ui->lvw2Progress->model()->setData(newIndex, data); // Daten in die neue Zeile einfügen
    // }
    // ui->lvw1ToDo->model()->moveRow(ui->lvw1ToDo->model()->index(ui->lvw1ToDo->model()->rowCount(),1),
    //                                ui->lvw1ToDo->currentIndex().row(),
    //                                ui->lvw2Progress->model()->index(ui->lvw1ToDo->model()->rowCount(),1),
    //                                ui->lvw1ToDo->currentIndex().row());
    //Move Current element to the 2 List View and change status
}


void MainWindow::on_btnSecondToFirst_clicked()
{
    //Move Current element to the 1 List View and change status
}


void MainWindow::on_btnSecondToThird_clicked()
{
    //Move Current element to the 3 List View and change status
}


void MainWindow::on_btnThirdToSecond_clicked()
{
    //Move Current element to the 2 List View and change status
}


void MainWindow::on_btnAdd_clicked()
{
    TaskElement newTask;
    AddTask *taskDialog = new AddTask(newTask, false, this);

    if (taskDialog->exec() == QDialog::Accepted) {
        TaskElement resultTask = taskDialog->getTask();
        qDebug() << resultTask.getTitle();
        qDebug() << resultTask.getBegin();
        qDebug() << resultTask.getEnd();
        qDebug() << resultTask.getDuration();
        qDebug() << resultTask.getState();
        qDebug() << resultTask.getRemark();
        resultTask.setID(currentID);
        qDebug() << resultTask.getID();
        AddItemToList(resultTask);
        // dbManager->getTasks()->append(resultTask);
        currentID += 1;
    }
    delete taskDialog;
}


void MainWindow::on_btnDetails_clicked()
{

    //Method get current selected to get the current ID from the View true the idex of the view an then the id in a Seperate List
    // AddTask *task = new AddTask(*new TaskElement(), false);
    // task->exec();
}


void MainWindow::on_btnEnd_clicked()
{
    //TODO: Save All
    //TODO: End Programm
}

//Extra Methods
void MainWindow::AddItemToList(TaskElement element){
    State currentState = element.getState();
    if(currentState+1 == 1)AddItem(ModelTODO, element.getID(),element.getTitle());
    if(currentState+1 == 2)AddItem(ModelPROGRESS, element.getID(),element.getTitle());
}

void MainWindow::AddItem(QStandardItemModel *model, int id, const QString &name)
{
    QStandardItem *item = new QStandardItem(QString("%1 - %2").arg(id).arg(name));
    item->setData(id, Qt::UserRole +1);
    model->appendRow(item);
}

void MainWindow::RemoveItemFromList(QStandardItemModel *model, int id) {
    for (int row = 0; row < model->rowCount(); ++row) {
        QStandardItem *item = model->item(row);
        if (item->data(Qt::UserRole + 1).toInt() == id) {
            model->removeRow(row);
            break;
        }
    }
}

void MainWindow::UpdateTaskState(int id, State newState) {
    for (TaskElement &task : dbManager->getTasks()) {
        if (task.getID() == id) {
            task.setState(newState);
            break;
        }
    }
}

void MainWindow::dropEvent(QDropEvent *event) {
    QListView *source = qobject_cast<QListView*>(event->source());
    if (source) {
        QModelIndex index = source->currentIndex();
        int id = index.data(Qt::UserRole + 1).toInt();
        QString title = index.data(Qt::DisplayRole).toString();

        QStandardItemModel *sourceModel = qobject_cast<QStandardItemModel*>(source->model());
        QStandardItemModel *targetModel = nullptr;

        if (sourceModel) {
            // Ermittle das Zielmodell basierend auf dem Zielobjekt
            if (ui->lvw1ToDo->underMouse())
                targetModel = ModelTODO;
            else if (ui->lvw2Progress->underMouse())
                targetModel = ModelPROGRESS;
            else if (ui->lvw3Done->underMouse())
                targetModel = ModelDONE;

            if (targetModel) {
                // Entferne das Element aus dem Quellmodell
                RemoveItemFromList(sourceModel, id);

                // Füge das Element zum Zielmodell hinzu
                AddItem(targetModel, id, title);

                // Aktualisiere den Zustand des Elements
                State newState = TODO;
                if (targetModel == ModelPROGRESS)
                    newState = PROGRESS;
                else if (targetModel == ModelDONE)
                    newState = DONE;
                UpdateTaskState(id, newState);

                event->accept();
            }
        }
    }
}

