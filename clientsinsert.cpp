#include "clientsinsert.h"
#include "ui_clientsinsert.h"
#include <QDebug>

ClientsInsert::ClientsInsert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientsInsert)
{
    ui->setupUi(this);
    setWindowTitle("Добавление клиентов");
}

ClientsInsert::~ClientsInsert()
{
    delete ui;
}

void ClientsInsert :: setQuery(QSqlQuery &query)
{
    this -> query = query;
}

void ClientsInsert :: setClientsCategories()
{
    QString cat;
    query.exec("SELECT name_category FROM ClientsCategories");
    for (int i=0; query.next(); i++)
    {
        cat = query.value(0).toString();
        ui -> comboBox_Categories -> insertItems(i,QStringList(cat));
    }
}

void ClientsInsert :: on_pushButtonInsertClient_clicked()
{
    category    = ui ->comboBox_Categories      -> currentText();
    phone       = ui ->lineEditcellnumberclient -> text();
    name        = ui ->lineEditnameclient       -> text();
    firstname   = ui ->lineEditfirstnameclient  -> text();
    famname     = ui ->lineEditfamclient        -> text();
    adres       = ui ->lineEditadresclient      -> text();
    birth       = ui ->lineEditbirthclient      -> text();
    card        = ui ->lineEditcardclient       -> text();

    int hexCard;    //uid будет равно значению card в hex
    hexCard = card.toInt();
    UID = QString::number(hexCard, 16);

    if (errorCardNum())
        insertClient();
    else
        errorCardNumWindow();
}

void ClientsInsert :: insertClient()
{
    query.prepare("INSERT INTO Clients (id_cat_client,client_phone,name_client,firstn_client,fam_client,client_adress,client_birth,UID,number_card) VALUES('"+ category+"','"+phone+"','"+name+"','"+firstname+"','"+famname+"','"+adres+"','"+birth+"','"+UID+"','"+card+"')");
    query.exec();
    niceCardNumWindow();
    setClearClientInfo();
    this->close();
}

void ClientsInsert :: errorCardNumWindow()
{
    QMessageBox msbox;
    msbox.setWindowTitle("ОШИБКА!");
    msbox.setText("Данный номер карты уже занят!");
    msbox.exec();
}

void ClientsInsert :: niceCardNumWindow()
{
    QMessageBox msbox;
    msbox.setWindowTitle("УСПЕШНО!");
    msbox.setText("Клиент добавлен в базу данных!");
    msbox.exec();
}

bool ClientsInsert :: errorCardNum()
{
    QString cardDB;
    query.exec("SELECT number_card FROM Clients");
    while(query.next())
    {
         cardDB = query.value(0).toString();
         if (card==cardDB)
             return false;
    }
    return true;
}

void ClientsInsert::on_pushButton_clicked()
{
    setClearClientInfo();
    this->close();
}

void ClientsInsert :: setClearClientInfo()
{
    ui ->comboBox_Categories -> clear();
    ui ->lineEditcellnumberclient -> clear();
    ui ->lineEditnameclient -> clear();
    ui ->lineEditfirstnameclient -> clear();
    ui ->lineEditfamclient -> clear();
    ui ->lineEditadresclient -> clear();
    ui ->lineEditbirthclient -> clear();
    ui ->lineEditcardclient -> clear();
}
