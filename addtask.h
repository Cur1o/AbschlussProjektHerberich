#ifndef ADDTASK_H
#define ADDTASK_H

#include <QDialog>
#include "taskelement.h"

namespace Ui {
class AddTask;
}

class AddTask : public QDialog
{
    Q_OBJECT

public:
    explicit AddTask(TaskElement currentTask, bool adding ,QWidget *parent = nullptr);
    ~AddTask();

    TaskElement getTask() const;

private slots:
    void on_btnApply_clicked();

    void on_btnCancle_clicked();

    void on_leTitle_editingFinished();

    void on_sbDuration_valueChanged(int arg1);

    void on_dateEStart_userDateChanged(const QDate &date);

    void on_dateEEnd_userDateChanged(const QDate &date);

    void on_comBState_currentIndexChanged(int index);

    void on_textEdit_textChanged();

private:
    Ui::AddTask *ui;
    TaskElement task;
};

#endif // ADDTASK_H
