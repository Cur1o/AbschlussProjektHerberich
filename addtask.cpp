#include "addtask.h"
#include "ui_addtask.h"
#include <QDebug>


AddTask::AddTask(TaskElement currentTask, bool adding, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddTask)
    ,task(currentTask)
{
    ui->setupUi(this);
    ui->leTitle->setText(task.getTitle());
    ui->sbDuration->setValue(task.getDuration());
    ui->dateEStart->setDate(QDate::currentDate());
    qDebug() << task.getBegin();
    qDebug() << task.getDuration();
    ui->dateEEnd->setDate(task.getEnd());

}

AddTask::~AddTask()
{
    delete ui;
}

void AddTask::on_btnApply_clicked()
{
    if(task.getTitle() != ""){
        accept();
    }
}


void AddTask::on_btnCancle_clicked()
{
    // delete ui;
}


void AddTask::on_leTitle_editingFinished()
{
    task.setTitle(ui->leTitle->text());
}

void AddTask::on_sbDuration_valueChanged(int days)
{
    QDate newEndDate = task.getBegin().addDays(days);
    ui->dateEEnd->setDate(newEndDate);
    task.setDuration(days);
}

void AddTask::on_dateEStart_userDateChanged(const QDate &date)
{
    if(date < task.getEnd() && date >= QDate::currentDate()){
        task.setBegin(date);
        qint64 days = task.getBegin().daysTo(task.getEnd());
        ui->sbDuration->setValue(days);
        task.setDuration(days);
    }
    else{
        ui->dateEStart->setDate(QDate::currentDate());
    }
}


void AddTask::on_dateEEnd_userDateChanged(const QDate &date)
{
    if(date > task.getBegin() ){
      task.setEnd(date);
        qint64 days = task.getBegin().daysTo(task.getEnd());
        ui->sbDuration->setValue(days);
        task.setDuration(days);
    }
    else{
        ui->dateEEnd->setDate(task.getBegin().addDays(1));
    }
}

void AddTask::on_comBState_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        task.setState(TODO);
        break;
    case 1:
        task.setState(PROGRESS);

        break;
    case 2:
        task.setState(DONE);
        break;
    default:
        task.setState(TODO);
        break;
    }
}

void AddTask::on_textEdit_textChanged()
{
    task.setRemark(ui->textEdit->toPlainText());
}

TaskElement AddTask::getTask() const {return task;}


