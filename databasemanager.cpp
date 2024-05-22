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
        qDebug() << "Zugriff fehlgeschlagen : " << db.lastError();
        return;
    }
    else
        qDebug() << "DB geöffnet";

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
TaskElement DatabaseManager::getTask(int index)
{
    LoadFromDatabase();
    QList<TaskElement> currentsTasks = getTasks();
    TaskElement selectedTask = currentsTasks.at(index);
    return selectedTask;
}

void DatabaseManager::UpdateItem(TaskElement taskToUpadate)
{

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
    localQuery.bindValue(":a_beginn", taskToCreate.getBegin());
    localQuery.bindValue(":a_ende", taskToCreate.getEnd());
    localQuery.bindValue(":a_status", taskToCreate.getState());
    localQuery.bindValue(":a_bemerkung", taskToCreate.getRemark());

    qDebug() << "Success Adding Data";
}

void DatabaseManager::LoadFromDatabase()
{
    QSqlQuery query;
    QString selectStatement = "SELECT * FROM aufgaben WHERE a_status != 2";
    if (!query.exec(selectStatement))
    {
        qDebug() << "Fehler beim Lesen: " << query.lastError();
        return;
    }

    while (query.next())
    {
        int id = query.value("a_id").toInt();
        QString title = query.value("a_aufgabenbezeichnung").toString();
        int duration = query.value("a_dauer").toInt();
        QDate begin = query.value("a_beginn").toDate();
        QDate end = query.value("a_ende").toDate();
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
    qDebug() << tasksTODO->data()->getTitle();
}

void saveToDatabase();
// void Widget::hohle_Daten(){
//     //Abfrage formulieren
//     QString sqlStatement = "select * from mitarbeiter"; //Formulieren der Abfrage
//     query = new QSqlQuery(db);

//     if(!query->exec(sqlStatement))      //Führe die SQL-Anweisung (Abfrage) aus.
//     {
//         qDebug() << "Fehler beim Lesen: " << query->lastError();
//         return;
//     }
//     record_count = query->numRowsAffected();    //Merke die Anzahl der gelesenen Datensätze
//     qDebug() << "Daten gelesen";
// }
