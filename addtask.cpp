#include "addtask.h"
#include "ui_addtask.h"
#include <QDebug>

AddTask::AddTask(TaskElement currentTask, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddTask)
    ,task(currentTask)
{
    ui->setupUi(this);
    ui->leTitle->setText(task.getTitle());
    ui->sbDuration->setValue(task.getDuration());
    ui->dateEStart->setDateTime(QDateTime::currentDateTime());
    task.setBegin(QDateTime::currentDateTime());
    ui->dateEEnd->setDateTime(task.getEnd());
    ui->comBState->setCurrentIndex(task.getState());
}

AddTask::~AddTask()
{
    delete ui;
}

//The window is closed with accept signal
void AddTask::on_btnApply_clicked()
{
    if(task.getTitle() != ""){
        accept();
    }
}


void AddTask::on_btnCancle_clicked()
{
    reject();
}

//The title of the task is updated
void AddTask::on_leTitle_editingFinished()
{
    task.setTitle(ui->leTitle->text());
}

//The Duration is updated and changes the hours from 1 up to 8677
void AddTask::on_sbDuration_valueChanged(int hours)
{
    QDateTime newEndDate = task.getBegin().addSecs(hours * 3600);
    ui->dateEEnd->setDateTime(newEndDate);
    task.setEnd(newEndDate);
    task.setDuration(hours);
}

//The begin is changed
void AddTask::on_dateEStart_dateTimeChanged(const QDateTime &dateTime)
{
    QDateTime newDateTime = dateTime;
    if (dateTime.date() == QDateTime::currentDateTime().date()) {
        // Wenn das Startdatum das aktuelle Datum ist, fügen Sie 30 Minuten hinzu
        newDateTime = dateTime.addSecs(1800);
    }

    if (newDateTime < task.getEnd()) {
        task.setBegin(newDateTime);
        qint64 hours = task.getBegin().secsTo(task.getEnd()) / 3600; // Umrechnung in Stunden
        ui->sbDuration->setValue(hours);
        task.setDuration(hours);
    } else {
        ui->dateEStart->setDateTime(task.getEnd().addSecs(-1800));
    }
}

//The end is changed
void AddTask::on_dateEEnd_dateTimeChanged(const QDateTime &dateTime)
{
    QDateTime newDateTime = dateTime;
    if (dateTime.date() == task.getBegin().date() && dateTime < task.getBegin().addSecs(1800)) {
        // Wenn das Enddatum auf denselben Tag wie der Startdatum fällt und weniger als 30 Minuten später ist
        newDateTime = task.getBegin().addSecs(1800);
    }

    if (newDateTime > task.getBegin()) {
        task.setEnd(newDateTime);
        qint64 hours = task.getBegin().secsTo(task.getEnd()) / 3600; // Umrechnung in Stunden
        ui->sbDuration->setValue(hours);
        task.setDuration(hours);
    } else {
        ui->dateEEnd->setDateTime(task.getBegin().addSecs(1800));
    }
}

//The state is changed
void AddTask::on_comBState_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        task.setState(TODO);
        break;
    case 1:
        task.setState(PROGRESS);
        break;
    default:
        task.setState(TODO);
        break;
    }
}

//The remark is changed
void AddTask::on_textEdit_textChanged()
{
    task.setRemark(ui->textEdit->toPlainText());
}

//The Task is returned when called
TaskElement AddTask::getTask() const {return task;}








