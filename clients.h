#ifndef CLIENTS_H
#define CLIENTS_H

#include <QDialog>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSortFilterProxyModel>
#include <QCompleter>
#include "clientsinsert.h"
#include "clientdelete.h"
#include "clientupdate.h"
#include "clientscategory.h"

namespace Ui {
class Clients;
}

class Clients : public QDialog
{
    Q_OBJECT
    ClientsInsert clientInsWindow;
    ClientDelete clientDelWindow;
    ClientUpdate clientUpdWindow;
    ClientsCategory categorysWindow;
    QSqlQuery query;
    QString selectedPhone;
    QSqlQueryModel *model;
    QSortFilterProxyModel *proxy;
    QCompleter* completer;

public:
    explicit Clients(QWidget *parent = nullptr);
    ~Clients();
    void setQuery(QSqlQuery &query);
    void setTableClients();

private slots:
    void on_pushButtonOpenWindowInsertClient_clicked();

    void on_pushButtonDeleteClient_clicked();

    void on_pushButtonUpdateClient_clicked();

    void on_pushButton_clicked();

    void on_pushButton_Category_clicked();

    void on_lineEditSearch_textChanged(const QString &arg1);

private:
    Ui::Clients *ui;


};

#endif // CLIENTS_H
