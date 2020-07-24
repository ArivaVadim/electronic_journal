#include "journal.h"
#include "ui_journal.h"

Journal::Journal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Journal)
{
    ui->setupUi(this);
    connect(ui->tableWidget,&QTableWidget::cellClicked,this,&Journal::infoTW);
    setWindowTitle("Журнал");
    setDate();
    ui->pushButton->setToolTip("Введите(удалите) значение в(из) таблицу(ы) и нажмите для сохранения");
    ui->pushButton_2->setToolTip("Нажмите для удаления данной таблицы");
    ui->pushButton_3->setToolTip("Нажмите для добавления мастера на выбранную дату");
    ui->pushButton_5->setToolTip("Нажмите чтобы записать клиента к мастеру");
}

Journal::~Journal()
{
    delete [] selectedMasterArray;
    delete ui;
}

void Journal :: setDate()
{
    QDate date = QDate::currentDate();
    ui -> dateEdit -> setDate(date);
}

void Journal :: getDate()
{
    QDate date = ui -> dateEdit -> date();
    DATE = date.toString();
}

void Journal :: setQuery(QSqlQuery &query)
{
    queryJournal = query;
}

void Journal :: createTable()
{
    if(!queryJournal.exec("SELECT * FROM '"+DATE+"'"))
    {
        queryJournal.exec("CREATE TABLE '"+DATE+"' (time INTEGER, '"+selectedMasterArray[1]+"' TEXT,'"+selectedMasterArray[2]+"' TEXT,'"+selectedMasterArray[3]+"' TEXT)");
        queryJournal.prepare("INSERT INTO '"+DATE+"' (time) VALUES(1000)");queryJournal.exec();
        queryJournal.prepare("INSERT INTO '"+DATE+"' (time) VALUES(1030)");queryJournal.exec();
        queryJournal.prepare("INSERT INTO '"+DATE+"' (time) VALUES(1100)");queryJournal.exec();
        queryJournal.prepare("INSERT INTO '"+DATE+"' (time) VALUES(1130)");queryJournal.exec();
        queryJournal.prepare("INSERT INTO '"+DATE+"' (time) VALUES(1200)");queryJournal.exec();
        queryJournal.prepare("INSERT INTO '"+DATE+"' (time) VALUES(1230)");queryJournal.exec();
        queryJournal.prepare("INSERT INTO '"+DATE+"' (time) VALUES(1300)");queryJournal.exec();
        queryJournal.prepare("INSERT INTO '"+DATE+"' (time) VALUES(1330)");queryJournal.exec();
        queryJournal.prepare("INSERT INTO '"+DATE+"' (time) VALUES(1400)");queryJournal.exec();
        queryJournal.prepare("INSERT INTO '"+DATE+"' (time) VALUES(1430)");queryJournal.exec();
        queryJournal.prepare("INSERT INTO '"+DATE+"' (time) VALUES(1500)");queryJournal.exec();
        queryJournal.prepare("INSERT INTO '"+DATE+"' (time) VALUES(1530)");queryJournal.exec();
        queryJournal.prepare("INSERT INTO '"+DATE+"' (time) VALUES(1600)");queryJournal.exec();
        queryJournal.prepare("INSERT INTO '"+DATE+"' (time) VALUES(1630)");queryJournal.exec();
        queryJournal.prepare("INSERT INTO '"+DATE+"' (time) VALUES(1700)");queryJournal.exec();
        queryJournal.prepare("INSERT INTO '"+DATE+"' (time) VALUES(1730)");queryJournal.exec();
        queryJournal.prepare("INSERT INTO '"+DATE+"' (time) VALUES(1800)");queryJournal.exec();
        queryJournal.prepare("INSERT INTO '"+DATE+"' (time) VALUES(1830)");queryJournal.exec();
        queryJournal.prepare("INSERT INTO '"+DATE+"' (time) VALUES(1900)");queryJournal.exec();
        queryJournal.prepare("INSERT INTO '"+DATE+"' (time) VALUES(1930)");queryJournal.exec();
        queryJournal.prepare("INSERT INTO '"+DATE+"' (time) VALUES(2000)");queryJournal.exec();
        queryJournal.prepare("INSERT INTO '"+DATE+"' (time) VALUES(2030)");queryJournal.exec();
        queryJournal.prepare("INSERT INTO '"+DATE+"' (time) VALUES(2100)");queryJournal.exec();
    }
}

void Journal :: createQWTable() //создание виджета
{
    queryJournal.exec("SELECT * FROM '"+DATE+"'");
    int count = queryJournal.record().count();
    QString columnName;

    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setRowCount(24);

    for (int k = 0; k < count; k += 4)
    {
        for (int i = 0; i < 4; i++)
        {
            switch (i)
            {
            case 0:
                columnName = "Время";
                break;
            case 1:
                columnName = "Название \nуслуги";
                break;
            case 2:
                columnName = "Номер \nтелефона \nклиента";
                break;
            case 3:
                columnName = "Стоимость";
                break;
            }
            ui->tableWidget->setColumnCount(ui->tableWidget->columnCount() + 1);
            ui->tableWidget->setHorizontalHeaderItem(k+i,new QTableWidgetItem(columnName));
            ui->tableWidget->horizontalHeader()->setSectionResizeMode(k+i, QHeaderView::ResizeToContents);
        }
        ui->tableWidget->setSpan(0,k,1,4); //объединяем ячейки под имя мастера
    }

}

void Journal :: setTableInfo()      //считывание таблицы из БД
{
    deleteQWTable();
    createQWTable();
    queryJournal.exec("SELECT * FROM '"+DATE+"'");
    int count = queryJournal.record().count();
    QString nameMaster;
    for (int i=1;i<count;i+=4)      //имя мастера беерм из названия столбца в таблице БД и записываем в 0 строку
    {
        nameMaster = queryJournal.record().fieldName(i);
        nameMaster.resize(nameMaster.size()-1);         //убираем последний символ
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setText(nameMaster);
        ui->tableWidget->setItem(0,0+i-1,item);
    }

    queryJournal.exec("SELECT * FROM '"+DATE+"'");
    int k = 1;                              //начинаем заполнение с 1 строки, т.к. 0 занята под имя мастера
    while (queryJournal.next())
    {
        for (int j=0;j<count;j++)
        {
            QString line = queryJournal.value(j).toString();
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText(line);
            ui->tableWidget->setItem(k,j,item);

        }
        k++;
    }
}

void Journal::infoTW() //слот назначен под один клик по ячейке виджета
{
    int COLUMN, ROW;
    QString TEXT;
    COLUMN = ui->tableWidget->currentColumn();
    ROW = ui->tableWidget->currentRow();
    TEXT = ui->tableWidget->item(ROW,COLUMN)->text();
    QString name, famName, costYslugi;
    qDebug()<<COLUMN%4;
    if(queryJournal.exec("SELECT cost_yslug FROM Yslygi WHERE name_yslugi = '"+TEXT+"'")&&COLUMN % 4==1)
    {
        queryJournal.next();
        costYslugi = queryJournal.value(0).toString();
        QMessageBox msbox1;
        msbox1.setWindowTitle("Услуга");
        msbox1.setText("Услуга: "+TEXT+". Стоимость: "+costYslugi+" руб.");
        msbox1.exec();
    }
    else if(queryJournal.exec("SELECT name_client,fam_client FROM Clients WHERE client_phone = "+TEXT)&&COLUMN % 4==2)
    {
        while(queryJournal.next())
        {
            name = queryJournal.value(0).toString();
            famName = queryJournal.value(1).toString();
        }
        QMessageBox msbox2;
        msbox2.setWindowTitle("Клиент");
        msbox2.setText("Номер телефона: "+TEXT+". "+name+" "+famName);
        msbox2.exec();
    }
}

bool Journal :: deleteTable()   //delete table
{
    if(queryJournal.exec("DROP TABLE '"+DATE+"'"))
        return true;
    else
        return false;
}

void Journal :: getTableChanges()   //добавить стоимость
{
    QString row_name;
    queryJournal.exec("SELECT * FROM '"+DATE+"'");
    int count = queryJournal.record().count();
    QSqlRecord name = queryJournal.record();
    for (int i =1; i < 24; i++)
    {
        for (int j=1; j < count; j++)
        {
            row_name = name.fieldName(j);
            time = ui -> tableWidget -> item(i,0) -> text();
            text = ui -> tableWidget -> item(i,j) -> text();
            queryJournal.prepare("UPDATE '"+DATE+"' SET '"+row_name+"' = '"+text+"' WHERE time = "+time);
            queryJournal.exec();
        }
    }
}

void Journal :: on_pushButtonBack_clicked()   //close
{
    deleteQWTable();
    deleteMasters();
    this -> close();
}

void Journal :: on_pushButton_clicked()   //добавить стоимость кнопка
{
    getTableChanges();
    QMessageBox msbox;
    msbox.setWindowTitle("Успешно!");
    msbox.setText("Данные обновлены!");
    msbox.exec();
}

void Journal :: on_pushButton_2_clicked()  //delete table кнопка
{
    if(deleteTable())
    {
        QMessageBox msbox;
        msbox.setWindowTitle("Успешно");
        msbox.setText("Таблица "+DATE+" удалена!");
        msbox.exec();
    }
    else
    {
        QMessageBox msbox;
        msbox.setWindowTitle("Ошибка!");
        msbox.setText("Таблица "+DATE+" не удалена!");
        msbox.exec();
    }
    setTableInfo();
}

void Journal :: setMasters()    //мастера в виджет
{
    QString name_master;
    queryJournal.exec("SELECT fam_master FROM Masters");
    for (int i=0; queryJournal.next(); i++)
    {
        name_master = queryJournal.value(0).toString();
        ui -> comboBoxMasters -> insertItems(i,QStringList(name_master));
    }
}

void Journal :: deleteMasters()
{
    ui -> comboBoxMasters -> clear();
}

void Journal :: on_pushButton_3_clicked()     //добавить мастера
{
    getDate();
    getSelectedMasterInfo();
    addMaster();
    setTableInfo();
}

void Journal :: on_pushButton_5_clicked()     //кнопка добавления услуги и клиента
{
    window.setQuery(queryJournal);
    window.setInfo(DATE);
    window.setModal(true);
    window.exec();
    window.clearInfo();
    setTableInfo();
}

void Journal :: addMaster()
{
    if(!queryJournal.exec("SELECT * FROM '"+DATE+"'"))
        createTable();
    else
    {
        queryJournal.prepare("ALTER TABLE '"+DATE+"' ADD '"+selectedMasterArray[0]+"' INTEGER"); queryJournal.exec();
        queryJournal.prepare("ALTER TABLE '"+DATE+"' ADD '"+selectedMasterArray[1]+"' TEXT"); queryJournal.exec();
        queryJournal.prepare("ALTER TABLE '"+DATE+"' ADD '"+selectedMasterArray[2]+"' TEXT"); queryJournal.exec();
        queryJournal.prepare("ALTER TABLE '"+DATE+"' ADD '"+selectedMasterArray[3]+"' TEXT"); queryJournal.exec();
        queryJournal.prepare("UPDATE '"+DATE+"' SET '"+selectedMasterArray[0]+"' = 1000 WHERE time = 1000");queryJournal.exec();
        queryJournal.prepare("UPDATE '"+DATE+"' SET '"+selectedMasterArray[0]+"' = 1030 WHERE time = 1030");queryJournal.exec();
        queryJournal.prepare("UPDATE '"+DATE+"' SET '"+selectedMasterArray[0]+"' = 1100 WHERE time = 1100");queryJournal.exec();
        queryJournal.prepare("UPDATE '"+DATE+"' SET '"+selectedMasterArray[0]+"' = 1130 WHERE time = 1130");queryJournal.exec();
        queryJournal.prepare("UPDATE '"+DATE+"' SET '"+selectedMasterArray[0]+"' = 1200 WHERE time = 1200");queryJournal.exec();
        queryJournal.prepare("UPDATE '"+DATE+"' SET '"+selectedMasterArray[0]+"' = 1230 WHERE time = 1230");queryJournal.exec();
        queryJournal.prepare("UPDATE '"+DATE+"' SET '"+selectedMasterArray[0]+"' = 1300 WHERE time = 1300");queryJournal.exec();
        queryJournal.prepare("UPDATE '"+DATE+"' SET '"+selectedMasterArray[0]+"' = 1330 WHERE time = 1330");queryJournal.exec();
        queryJournal.prepare("UPDATE '"+DATE+"' SET '"+selectedMasterArray[0]+"' = 1400 WHERE time = 1400");queryJournal.exec();
        queryJournal.prepare("UPDATE '"+DATE+"' SET '"+selectedMasterArray[0]+"' = 1430 WHERE time = 1430");queryJournal.exec();
        queryJournal.prepare("UPDATE '"+DATE+"' SET '"+selectedMasterArray[0]+"' = 1500 WHERE time = 1500");queryJournal.exec();
        queryJournal.prepare("UPDATE '"+DATE+"' SET '"+selectedMasterArray[0]+"' = 1530 WHERE time = 1530");queryJournal.exec();
        queryJournal.prepare("UPDATE '"+DATE+"' SET '"+selectedMasterArray[0]+"' = 1600 WHERE time = 1600");queryJournal.exec();
        queryJournal.prepare("UPDATE '"+DATE+"' SET '"+selectedMasterArray[0]+"' = 1630 WHERE time = 1630");queryJournal.exec();
        queryJournal.prepare("UPDATE '"+DATE+"' SET '"+selectedMasterArray[0]+"' = 1700 WHERE time = 1700");queryJournal.exec();
        queryJournal.prepare("UPDATE '"+DATE+"' SET '"+selectedMasterArray[0]+"' = 1730 WHERE time = 1730");queryJournal.exec();
        queryJournal.prepare("UPDATE '"+DATE+"' SET '"+selectedMasterArray[0]+"' = 1800 WHERE time = 1800");queryJournal.exec();
        queryJournal.prepare("UPDATE '"+DATE+"' SET '"+selectedMasterArray[0]+"' = 1830 WHERE time = 1830");queryJournal.exec();
        queryJournal.prepare("UPDATE '"+DATE+"' SET '"+selectedMasterArray[0]+"' = 1900 WHERE time = 1900");queryJournal.exec();
        queryJournal.prepare("UPDATE '"+DATE+"' SET '"+selectedMasterArray[0]+"' = 1930 WHERE time = 1930");queryJournal.exec();
        queryJournal.prepare("UPDATE '"+DATE+"' SET '"+selectedMasterArray[0]+"' = 2000 WHERE time = 2000");queryJournal.exec();
        queryJournal.prepare("UPDATE '"+DATE+"' SET '"+selectedMasterArray[0]+"' = 2030 WHERE time = 2030");queryJournal.exec();
        queryJournal.prepare("UPDATE '"+DATE+"' SET '"+selectedMasterArray[0]+"' = 2100 WHERE time = 2100");queryJournal.exec();
    }
}

void Journal :: getSelectedMasterInfo()
{
    selectedMaster = ui -> comboBoxMasters ->currentText();
    for (int i =0;i<4;i++)
    {
        columnNumber.setNum(i);
        selectedMasterArray[i] = selectedMaster+columnNumber;
    }
}

void Journal :: deleteQWTable()
{
    ui -> tableWidget -> clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
}

void Journal::on_dateEdit_userDateChanged(const QDate &date)
{
    DATE=date.toString();
    createTable();
    setTableInfo();
}
