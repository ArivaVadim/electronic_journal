#include "journaladdclient.h"
#include "ui_journaladdclient.h"

JournalAddClient::JournalAddClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JournalAddClient)
{
    ui->setupUi(this);
    setWindowTitle("Распределение клиентов");
}

JournalAddClient::~JournalAddClient()
{
    delete ui;
}

void JournalAddClient :: setQuery(QSqlQuery &query)
{
    this -> query = query;
}

void JournalAddClient :: setInfo(QString &DATE)
{  
    query.exec("SELECT * FROM '"+DATE+"'");
    int count = query.record().count();
    for (int i=1; i<=count; i+=4)
    {
        master = query.record().fieldName(i);
        master.resize(master.size()-1);
        ui -> comboBoxMasters -> insertItems(i,QStringList(master));
    }
    query.exec("SELECT name_yslugi FROM Yslygi");
    for (int i=0; query.next(); i++)
    {
        yslugi = query.value(0).toString();
        ui -> comboBoxYsluga -> insertItems(i,QStringList(yslugi));
    }
    query.exec("SELECT client_phone FROM Clients");
    for (int i=0; query.next(); i++)
    {
        phone = query.value(0).toString();
        ui -> comboBoxClientPhone -> insertItems(i,QStringList(phone));
    }
    query.exec("SELECT time FROM '"+DATE+"'");
    for (int i=0; query.next(); i++)
    {
        time = query.value(0).toString();
        ui -> comboBoxTime -> insertItems(i,QStringList(time));
    }
    date = DATE;
}

void JournalAddClient :: getInfo()
{
    master = ui -> comboBoxMasters ->currentText();
    yslugi = ui -> comboBoxYsluga ->currentText();
    phone = ui -> comboBoxClientPhone ->currentText();
    time = ui -> comboBoxTime ->currentText();
    columnYslugi = master+"1";
    columnPhone = master+"2";
}

void JournalAddClient::on_pushButton_2_clicked()
{
    clearInfo();
    this -> close();
}

void JournalAddClient::on_pushButton_clicked()
{
    getInfo();
    query.prepare("UPDATE '"+date+"' SET '"+columnYslugi+"' = '"+yslugi+"' WHERE time = "+time); query.exec();
    query.prepare("UPDATE '"+date+"' SET '"+columnPhone+"' = '"+phone+"' WHERE time = "+time); query.exec();
    QMessageBox msbox;
    msbox.setWindowTitle("Успешно!");
    msbox.setText("Данные обновлены!");
    msbox.exec();
    this->close();
}

void JournalAddClient::on_pushButton_InsertClient_clicked()
{
    clientInsertWindow.setQuery(query);
    clientInsertWindow.setClientsCategories();
    clientInsertWindow.exec();
    clearInfo();
    setInfo(date);
}

void JournalAddClient :: clearInfo()
{
    ui -> comboBoxMasters ->clear();
    ui -> comboBoxYsluga ->clear();
    ui -> comboBoxClientPhone ->clear();
    ui -> comboBoxTime ->clear();
}
