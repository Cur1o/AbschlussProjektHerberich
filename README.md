# AbschlussProjektHerberich

The objective of this Project was to create a Task managment system with database interactions. 
Where you can create and Edit Tasks. The tasks have 3 states ToDo, Pending and Done. 

The used Database

```sql
create database scheduler;
go
use scheduler;
create table aufgaben
(
a_id int identity(1,1) primary key not null,
a_aufgabenbezeichnung varchar(50) not null,
a_dauer int, --in Stunden
a_beginn datetime, --Datum und/oder Zeit
a_ende datetime, --dito
a_status int not null, --0=unerledigt, 1=inArbeit, 2=erledigt
a_bemerkung varchar(255) --Ein Versuch von Erklärungen ☺
);
```
Custom TaskElement
```C++
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
}

```
Programm Structure
Headers:
    addtask.h: inplementation of the Methods.
    databasemanager.h: inplementation of the Methods.
    enums.h: Here all the enums of Task element. enum State{TODO, PROGRESS, DONE};
    mainwindow.h: inplementation of the Methods.
    taskelement.h: inplementation of the TaskElement CLass.

Sources:
    addtask.cpp: Ths is a Class which manages the user input for the task creation and edeting.
    databasemanager.cpp: Here all the database commands are proccesed and it is responsible for data handlinjg and storing.
    main.cpp: The main of the Application. A custom  Splash Screen is implemented and schown for 5 sec at the start. the main window is executed afther this 5 sec.
    mainwindow.cpp: Here all the main UI is handeld like opening the Edit or Add window. Or changing the language from German to English and updating the UI.
    taskelement.cpp: This is the TaskElement Class. Here all the Data from 1 row of the database is stored.

Forms:
    addtask.ui: The UI of the Add or Edit window.
    mainwindow.ui: The UI of the Main Application.

Resources:
    data.qrc: The resource file where all the external data is stored.
        /img
            logos and icons are stored here.
        /language
            the language files for German and English are stored here.

If you have any questions feel free to contact me at: Saherberich12@gmail.com

All images and logos are drawn by me. 
CheckList.jpg is generated with the help of DALL-E 3.



