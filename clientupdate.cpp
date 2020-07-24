#include "clientupdate.h"
#include "ui_clientupdate.h"

ClientUpdate::ClientUpdate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientUpdate)
{
    ui->setupUi(this);
    setWindowTitle("Обновление клиентов");
    ui -> lineEdit_UID -> setReadOnly(true);
    ui -> lineEdit_UID -> setToolTip("Уникальный код для каждого клиента, формируется автоматически по номеру карты клиента");
    ui -> label_2 -> setToolTip("Уникальный код для каждого клиента, формируется автоматически по номеру карты клиента");
    ui -> pushButtonReturn -> setToolTip("Нажмите для возвращения к списку клиентов");
    ui -> pushButtonSearch -> setToolTip("Введите номер телефона клиента и нажмите для отображения данных");
    ui -> pushButtonUpdateClient -> setToolTip("Нажмите для записи изменений");
}

ClientUpdate::~ClientUpdate()
{
    delete ui;
}

void ClientUpdate :: setQuery(QSqlQuery &query)
{
    this -> query = query;
    this -> model = new QSqlQueryModel;
    model -> setQuery("SELECT * FROM Clients");
    this -> completer = new QCompleter;
    completer -> setModel(model);
    completer -> setCompletionColumn(2);
    completer -> setModelSorting(QCompleter::CaseSensitivelySortedModel);
    completer -> setCaseSensitivity(Qt::CaseInsensitive);
    ui -> lineEdit -> setCompleter(completer);
}

void ClientUpdate :: setClientsCategories()
{
    QString cat;
    query.exec("SELECT name_category FROM ClientsCategories");
    for (int i=0; query.next(); i++)
    {
        cat = query.value(0).toString();
        ui -> comboBox -> insertItems(i,QStringList(cat));
    }
}

void ClientUpdate :: getSearchClient()
{
    selectedphone = ui -> lineEdit -> text();
    query.exec("SELECT id_cat_client,client_phone,name_client,firstn_client,fam_client,client_adress,client_birth,UID,number_card FROM Clients WHERE client_phone = "+selectedphone);
    while(query.next())
    {
        ui->lineEditcellnumberclient->setText(query.value(1).toString());
        ui->lineEditnameclient->setText(query.value(2).toString());
        ui->lineEditfirstnameclient->setText(query.value(3).toString());
        ui->lineEditfamclient->setText(query.value(4).toString());
        ui->lineEditadresclient->setText(query.value(5).toString());
        ui->lineEditbirthclient->setText(query.value(6).toString());
        ui->lineEditcardclient->setText(query.value(8).toString());
        ui->lineEdit_UID->setText(query.value(7).toString());
    }
}

void ClientUpdate :: getClientInfo()
{
    category = ui ->comboBox -> currentText();
    phone = ui ->lineEditcellnumberclient -> text();
    name = ui ->lineEditnameclient -> text();
    firstname = ui ->lineEditfirstnameclient -> text();
    famname = ui ->lineEditfamclient -> text();
    adres = ui ->lineEditadresclient -> text();
    birth = ui ->lineEditbirthclient -> text();
    card = ui ->lineEditcardclient -> text();
    query.exec("SELECT id_client FROM clients WHERE client_phone = "+selectedphone);
    query.next();
    ID = query.value(0).toString();

    int hexCard;    //uid будет равно значению card в hex
    hexCard = card.toInt();
    UID = QString::number(hexCard, 16);
}

void ClientUpdate :: updateClientInfo()
{
    getClientInfo();
    if (errorCardNum())
    {
        query.prepare("UPDATE Clients SET id_cat_client = '"+category+"',client_phone = '"+phone+"',name_client = '"+name+"',firstn_client = '"+firstname+"',fam_client = '"+famname+"',client_adress = '"+adres+"',client_birth = '"+birth+"',UID = '"+UID+"',number_card = '"+card+"' WHERE id_client = "+ID);
        query.exec();
        niceCardNumWindow();
    }
    else
        errorCardNumWindow();
}

void ClientUpdate::on_pushButtonSearch_clicked()
{
    getSearchClient();
}

void ClientUpdate::on_pushButtonUpdateClient_clicked()
{
    updateClientInfo();
}

void ClientUpdate :: errorCardNumWindow()
{
    QMessageBox msbox;
    msbox.setWindowTitle("ОШИБКА!");
    msbox.setText("Данный номер карты уже занят!");
    msbox.exec();
}

bool ClientUpdate :: errorCardNum()
{
    QString cardDB;
    query.exec("SELECT number_card FROM Clients WHERE id_client != "+ID);
    while(query.next())
    {
         cardDB = query.value(0).toString();
         if (card==cardDB)
             return false;
    }
    return true;
}

void ClientUpdate::on_pushButtonReturn_clicked()
{
    setClearClientInfo();
    this->close();
}

void ClientUpdate :: niceCardNumWindow()
{
    QMessageBox msbox;
    msbox.setWindowTitle("УСПЕШНО!");
    msbox.setText("Данные клиента обновлены!");
    msbox.exec();
}

void ClientUpdate :: setClearClientInfo()
{
    ui->lineEdit->clear();
    ui->comboBox->clear();
    ui->lineEditcellnumberclient->clear();
    ui->lineEditnameclient->clear();
    ui->lineEditfirstnameclient->clear();
    ui->lineEditfamclient->clear();
    ui->lineEditadresclient->clear();
    ui->lineEditbirthclient->clear();
    ui->lineEditcardclient->clear();
}
