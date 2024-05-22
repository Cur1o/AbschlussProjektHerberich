#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "taskelement.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "enums.h"

class DatabaseManager
{
private:
    QList<TaskElement> *tasks;
    QList<TaskElement> *tasksTODO;
    QList<TaskElement> *tasksPROGRESS;
    QList<TaskElement> *tasksDONE;
    QSqlDatabase db;
    QSqlQuery *query;
    State _taskState;
    int totalDatabaseID;
public:
    DatabaseManager();
    int getTotalDatabaseID(){return totalDatabaseID;}
    QList<TaskElement> getTasks(int tasknumber = 0);

    void UpdateItem(TaskElement taskToUpadate);
    void ADDItemToDatabase(TaskElement taskToCreate);
    void LoadFromDatabase();
    void saveToDatabase();




};

#endif // DATABASEMANAGER_H
