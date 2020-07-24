#include "clientdelete.h"
#include "ui_clientdelete.h"


ClientDelete::ClientDelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientDelete)
{
    ui->setupUi(this);
    setWindowTitle("Удаление клиентов");
}

ClientDelete::~ClientDelete()
{
    delete ui;
}

void ClientDelete :: setQuery(QSqlQuery &query)
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

void ClientDelete::on_pushButtonDELETE_clicked()
{
    phone = ui -> lineEdit -> text();
    query.prepare("DELETE FROM Clients WHERE client_phone = "+ phone);
    query.exec();
    QMessageBox msbox;
    msbox.setWindowTitle("УСПЕШНО!");
    msbox.setText("Клиент удалён из базы данных");
    msbox.exec();
    ui -> lineEdit -> clear();
    this->close();
}

void ClientDelete::on_pushButtonSearch_2_clicked()
{
    this->close();
}
