#ifndef CLIENTDELETE_H
#define CLIENTDELETE_H

#include <QDialog>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QCompleter>
#include <QSqlQueryModel>

namespace Ui {
class ClientDelete;
}

class ClientDelete : public QDialog
{
    Q_OBJECT
    QSqlQuery query;
    QString phone;
    QCompleter* completer;
    QSqlQueryModel* model;
    bool infoOpen = false;

public:
    explicit ClientDelete(QWidget *parent = nullptr);
    ~ClientDelete();
    void setQuery(QSqlQuery &query);
    bool getClientInfo();

private slots:

    void on_pushButtonDELETE_clicked();

    void on_pushButtonSearch_2_clicked();

private:
    Ui::ClientDelete *ui;
};

#endif // CLIENTDELETE_H
