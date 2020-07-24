#include "clients.h"
#include "ui_clients.h"

Clients::Clients(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Clients)
{
    ui->setupUi(this);
    setWindowTitle("Клиенты");

}

Clients::~Clients()
{
    delete ui;
}

void Clients :: setQuery(QSqlQuery &query)
{
    this -> query = query;

}

void Clients :: setTableClients()
{
    this -> model = new QSqlQueryModel;
    model -> setQuery("SELECT * FROM Clients");
    model -> setHeaderData(0, Qt::Horizontal, "ID");
    model -> setHeaderData(1, Qt::Horizontal, "Категория");
    model -> setHeaderData(2, Qt::Horizontal, "Номер телефона");
    model -> setHeaderData(3, Qt::Horizontal, "Имя");
    model -> setHeaderData(4, Qt::Horizontal, "Отчество");
    model -> setHeaderData(5, Qt::Horizontal, "Фамилия");
    model -> setHeaderData(6, Qt::Horizontal, "Адрес");
    model -> setHeaderData(7, Qt::Horizontal, "Дата рождения");
    model -> setHeaderData(8, Qt::Horizontal, "UID");
    model -> setHeaderData(9, Qt::Horizontal, "Номер карты");

    this -> proxy = new QSortFilterProxyModel;
    proxy -> setSourceModel(model);

    this -> completer = new QCompleter;
    completer -> setModel(proxy);
    completer -> setCompletionColumn(2);
    completer -> setModelSorting(QCompleter::CaseSensitivelySortedModel);
    completer -> setCaseSensitivity(Qt::CaseInsensitive);
    ui -> lineEditSearch -> setCompleter(completer);

    ui -> tableView -> setModel(proxy);
    ui -> tableView -> setEditTriggers(QAbstractItemView::NoEditTriggers);
    for (int i =0;i<ui->tableView->model()->columnCount();i++)
    {
        if(i==9)
            ui->tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        else
            ui->tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }
    ui -> tableView -> setSortingEnabled(true);

}

void Clients::on_pushButtonOpenWindowInsertClient_clicked()
{
    clientInsWindow.setQuery(query);
    clientInsWindow.setClientsCategories();
    clientInsWindow.setModal(true);
    clientInsWindow.exec();
    setTableClients();
}

void Clients::on_pushButtonDeleteClient_clicked()
{
    clientDelWindow.setQuery(query);
    clientDelWindow.setModal(true);
    clientDelWindow.exec();
    setTableClients();
}

void Clients::on_pushButtonUpdateClient_clicked()
{
    clientUpdWindow.setQuery(query);
    clientUpdWindow.setClientsCategories();
    clientUpdWindow.setModal(true);
    clientUpdWindow.exec();
    setTableClients();
}

void Clients::on_pushButton_Category_clicked()
{
    categorysWindow.setQuery(query);
    categorysWindow.openCatTable("ClientsCategories");
    categorysWindow.setInfoQW();
    categorysWindow.setModal(true);
    categorysWindow.exec();
    setTableClients();
}

void Clients::on_pushButton_clicked()
{
    this->close();
}

void Clients::on_lineEditSearch_textChanged(const QString &arg1)
{
    proxy->setFilterKeyColumn(2);
    proxy->setFilterRegExp(arg1);
}
