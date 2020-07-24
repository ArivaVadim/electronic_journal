#ifndef JOURNALADDCLIENT_H
#define JOURNALADDCLIENT_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlField>
#include "clientsinsert.h"

namespace Ui {
class JournalAddClient;
}

class JournalAddClient : public QDialog
{
    Q_OBJECT
    QSqlQuery query;
    ClientsInsert clientInsertWindow;
    QString date;
    QString yslugi, phone, time, master;
    QString columnYslugi, columnPhone;

public:
    explicit JournalAddClient(QWidget *parent = nullptr);
    ~JournalAddClient();
    void setQuery(QSqlQuery &query);
    void setInfo(QString &DATE);
    void getInfo();
    void clearInfo();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_InsertClient_clicked();

private:
    Ui::JournalAddClient *ui;
};

#endif // JOURNALADDCLIENT_H
