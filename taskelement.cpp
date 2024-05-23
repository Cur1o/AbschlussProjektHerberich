#include "taskelement.h"

TaskElement::TaskElement(int id, QString title, int duration, QDateTime begin, QDateTime end, State state, QString remark){
    this->_id = id;
    this->_title = title;
    this->_duration = duration;
    this->setEnd(end);
    this->setBegin(begin);
    this->setState(state);
    this->_remark = remark;
}

TaskElement::TaskElement(QString title, int duration, QString remark){
    this->_title = title;
    this->_duration = duration;
    this->_remark = remark;
    this->_begin = QDateTime::currentDateTime();
    this->_end = QDateTime::currentDateTime();
    this->_end = _end.addDays(1);
}
bool TaskElement::setID(int id){
    if(id > 0){
        this->_id = id;
        return true;
    }
    return false;
}

bool TaskElement::setTitle(QString title){
    if(title != ""){
        this->_title = title;
        return true;
    }
    return false;
}

bool TaskElement::setDuration(int duration){
    if(duration > 0 && duration < 365){
        this->_duration = duration;
        return true;
    }
    return false;
}

bool TaskElement::setBegin(QDateTime begin){
    if(begin < this->_end)
    {
        this->_begin = begin;
        return true;
    }
    return false;
}

bool TaskElement::setEnd(QDateTime end){
    if(end > this->_begin){
        this->_end = end;
        return true;
    }
    return false;
}

bool TaskElement::setState(State state){
    switch (state) {
    case TODO:
        this->_state = state;
        return true;
        break;
    case PROGRESS:
        this->_state = state;
        return true;
        break;
    case DONE:
        this->_state = state;
        return true;
        break;
    default:
        return false;
        break;
    }
}

bool TaskElement::setRemark(QString remark){
    if (remark != "" &&  remark != " "){
        this->_remark = remark;
        return true;
    }
    return false;
}
