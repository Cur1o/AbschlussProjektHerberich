#ifndef TASKELEMENT_H
#define TASKELEMENT_H
#include <QString>
#include <QDateTime>
#include "enums.h"

class TaskElement
{
private:
    int _id;
    QString _title;
    int _duration;
    QDateTime _begin;
    QDateTime _end;
    State _state = TODO;
    QString _remark;
public:
    TaskElement(int id, QString title, int duration, QDateTime begin, QDateTime end, State state, QString remark);
    TaskElement(QString title = "Task", int duration = 1, QString remark = "");

    int getID(){return _id;}
    QString getTitle(){return _title;}
    int getDuration(){return _duration;}
    QDateTime getBegin(){return _begin;}
    QDateTime getEnd(){return _end;}
    State getState(){return _state;}
    QString getRemark(){return _remark;}

    bool setID(int id);
    bool setTitle(QString title);
    bool setDuration(int duration);
    bool setBegin(QDateTime date);
    bool setEnd(QDateTime date);
    bool setState(State state);
    bool setRemark(QString remark);

};

#endif // TASKELEMENT_H
