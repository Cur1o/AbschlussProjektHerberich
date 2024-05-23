#include "databasemanager.h"

DatabaseManager::DatabaseManager()
{
    tasks = new QList<TaskElement>;
    tasksTODO = new QList<TaskElement>;
    tasksPROGRESS = new QList<TaskElement>;
    tasksDONE = new QList<TaskElement>;

    db = QSqlDatabase::addDatabase("QODBC");
    db.setConnectOptions();
    QString connectionString = "Driver={Sql Server};Server=SANDRORECHNER\\SQLEXPRESS;database=scheduler;trusted_connection=yes";
    db.setDatabaseName(connectionString);

    if(!db.open())
    {
        qDebug() << "Access Denied : " << db.lastError();
        return;
    }
    else
        qDebug() << "DB Opened";

    LoadFromDatabase();
}

QList<TaskElement> DatabaseManager::getTasks(int tasknumber)
{
    switch (tasknumber) {
    case 1:
        return *tasksTODO;
        break;
    case 2:
        return *tasksPROGRESS;
        break;
    case 3:
        return *tasksDONE;
        break;
    default:
        return *tasks;
        break;
    }
}
TaskElement DatabaseManager::getTask(int tasknumber,  int index)
{
    LoadFromDatabase();
    QList<TaskElement> currentTasks = getTasks(tasknumber);
    TaskElement selectedTask = currentTasks.at(index);
    return selectedTask;
}

void DatabaseManager::UpdateItem(TaskElement taskToUpdate)
{
    QSqlQuery localQuery;
    localQuery.prepare("UPDATE aufgaben "
                       "SET "
                       "a_aufgabenbezeichnung = :a_aufgabenbezeichnung, "
                       "a_dauer = :a_dauer, "
                       "a_beginn = :a_beginn, "
                       "a_ende = :a_ende, "
                       "a_status = :a_status, "
                       "a_bemerkung = :a_bemerkung "
                       "WHERE a_id = :a_id");

    localQuery.bindValue(":a_aufgabenbezeichnung", taskToUpdate.getTitle());
    localQuery.bindValue(":a_dauer", taskToUpdate.getDuration());
    localQuery.bindValue(":a_beginn", taskToUpdate.getBegin().toString(Qt::ISODate));
    localQuery.bindValue(":a_ende", taskToUpdate.getEnd().toString(Qt::ISODate));
    localQuery.bindValue(":a_status", taskToUpdate.getState());
    localQuery.bindValue(":a_bemerkung", taskToUpdate.getRemark());
    localQuery.bindValue(":a_id", taskToUpdate.getID());

    if (!localQuery.exec()) {
        qDebug() << "Error while writing: " << localQuery.lastError();
        return;
    }
    qDebug() << "Success Updating Data";
    LoadFromDatabase();
}

void DatabaseManager::ADDItemToDatabase(TaskElement taskToCreate)
{
    QSqlQuery localQuery;
    localQuery.prepare("insert into aufgaben values("
                       ":a_aufgabenbezeichnung,"
                       ":a_dauer,"
                       ":a_beginn,"
                       ":a_ende,"
                       ":a_status,"
                       ":a_bemerkung)");

    localQuery.bindValue(":a_aufgabenbezeichnung", taskToCreate.getTitle());
    localQuery.bindValue(":a_dauer", taskToCreate.getDuration());
    localQuery.bindValue(":a_beginn", taskToCreate.getBegin().toString(Qt::ISODate));
    localQuery.bindValue(":a_ende", taskToCreate.getEnd().toString(Qt::ISODate));
    localQuery.bindValue(":a_status", taskToCreate.getState());
    localQuery.bindValue(":a_bemerkung", taskToCreate.getRemark());

    if(!localQuery.exec()){
        qDebug()<< "Error while writing: " << query->lastError();
        return;
    }
    LoadFromDatabase();
    qDebug() << "Success Adding Data";
}

void DatabaseManager::LoadFromDatabase()
{
    QSqlQuery query;
    QString selectStatement = "SELECT * FROM aufgaben WHERE a_status != 2";
    if (!query.exec(selectStatement))
    {
        qDebug() << "Error while reading: " << query.lastError();
        return;
    }
    tasksTODO->clear();
    tasksPROGRESS->clear();
    while (query.next())
    {
        int id = query.value("a_id").toInt();
        QString title = query.value("a_aufgabenbezeichnung").toString();
        int duration = query.value("a_dauer").toInt();
        QDateTime begin = query.value("a_beginn").toDateTime();
        QDateTime end = query.value("a_ende").toDateTime();
        int stateInt = query.value("a_status").toInt();
        State state = TODO;
        if(stateInt == 1)state = PROGRESS;
        QString remark = query.value("a_bemerkung").toString();

        // Erstelle ein TaskElement und füge es zur Liste hinzu
        TaskElement newTask(id,title, duration, begin, end, state, remark);
        if(stateInt == 0)this->tasksTODO->append(newTask);
        if(stateInt == 1)this->tasksPROGRESS->append(newTask);
        this->tasks->append(newTask);
    }
    qDebug() << "Success Loading Data";

}

void DatabaseManager::ChangeValueInListToList(int list1, int list2, int index)
{
    // qDebug() << "Before operation:";
    // qDebug() << "TODO count:" << tasksTODO->count();
    // qDebug() << "PROGRESS count:" << tasksPROGRESS->count();
    // qDebug() << "DONE count:" << tasksDONE->count();

    TaskElement taskToMove;
    bool validOperation = false;

    switch (list1) {
    case 1:
        if (index >= 0 && index < tasksTODO->size()) {
            taskToMove = tasksTODO->at(index);
            tasksTODO->removeAt(index);
            validOperation = true;
        }
        break;
    case 2:
        if (index >= 0 && index < tasksPROGRESS->size()) {
            taskToMove = tasksPROGRESS->at(index);
            tasksPROGRESS->removeAt(index);
            validOperation = true;
        }
        break;
    case 3:
        if (index >= 0 && index < tasksDONE->size()) {
            taskToMove = tasksDONE->at(index);
            tasksDONE->removeAt(index);
            validOperation = true;
        }
        break;
    default:
        qDebug() << "Invalid list1 value";
        return;
    }

    if (validOperation) {
        if (list2 == 1) taskToMove.setState(TODO);
        if (list2 == 2) taskToMove.setState(PROGRESS);
        if (list2 == 3) taskToMove.setState(DONE);

        switch (list2) {
        case 1:
            tasksTODO->append(taskToMove);
            break;
        case 2:
            tasksPROGRESS->append(taskToMove);
            break;
        case 3:
            tasksDONE->append(taskToMove);
            break;
        default:
            qDebug() << "Invalid list2 value";
            break;
        }
        UpdateItem(taskToMove);
    } else {
        qDebug() << "Invalid operation: The element could not be moved";
    }

    // qDebug() << "After operation:";
    // qDebug() << "TODO count:" << tasksTODO->count();
    // qDebug() << "PROGRESS count:" << tasksPROGRESS->count();
    // qDebug() << "DONE count:" << tasksDONE->count();
}
