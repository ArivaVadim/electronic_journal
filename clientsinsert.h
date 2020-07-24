#ifndef CLIENTSINSERT_H
#define CLIENTSINSERT_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>


namespace Ui {
class ClientsInsert;
}

class ClientsInsert : public QDialog
{
    Q_OBJECT
    QSqlQuery query;
    QString ID;
    QString category;
    QString phone;
    QString name;
    QString firstname;
    QString famname;
    QString adres;
    QString birth;
    QString UID;
    QString card;


public:
    explicit ClientsInsert(QWidget *parent = nullptr);
    ~ClientsInsert();
    void setQuery(QSqlQuery &query);
    void insertClient();
    void errorCardNumWindow();
    bool errorCardNum();
    void niceCardNumWindow();
    void setClearClientInfo();
    void setClientsCategories();


private slots:
    void on_pushButtonInsertClient_clicked();

    void on_pushButton_clicked();

private:
    Ui::ClientsInsert *ui;
};

#endif // CLIENTSINSERT_H
