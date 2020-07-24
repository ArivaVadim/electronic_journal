#ifndef CLIENTUPDATE_H
#define CLIENTUPDATE_H

#include <QDialog>
#include <QSqlQuery>
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QCompleter>
#include <QDebug>

namespace Ui {
class ClientUpdate;
}

class ClientUpdate : public QDialog
{
    Q_OBJECT
    QSqlQuery query;
    QSqlQueryModel* model;
    QCompleter* completer;
    QString ID;
    QString category;
    QString phone, selectedphone;
    QString name;
    QString firstname;
    QString famname;
    QString adres;
    QString birth;
    QString UID;
    QString card;

public:
    explicit ClientUpdate(QWidget *parent = nullptr);
    ~ClientUpdate();
    void setQuery(QSqlQuery &query);
    void getSearchClient();
    void getClientInfo();
    void updateClientInfo();
    void errorCardNumWindow();
    bool errorCardNum();
    void niceCardNumWindow();
    void setClearClientInfo();
    void setClientsCategories();

private slots:
    void on_pushButtonSearch_clicked();

    void on_pushButtonUpdateClient_clicked();

    void on_pushButtonReturn_clicked();

private:
    Ui::ClientUpdate *ui;
};

#endif // CLIENTUPDATE_H
