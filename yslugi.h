#ifndef YSLUGI_H
#define YSLUGI_H

#include <QDialog>
#include <QSql>
#include <QSqlQuery>
#include "yslygiinsert.h"
#include "yslygiupdate.h"
#include "yslygidelete.h"
#include "clientscategory.h"

namespace Ui {
class Yslugi;
}

class Yslugi : public QDialog
{
    Q_OBJECT
    QSqlQuery queryYslugi;
    YslygiInsert insertWindow;
    YslygiUpdate updateWindow;
    YslygiDelete deleteWindow;
    ClientsCategory categorysWindow;

public:
    explicit Yslugi(QWidget *parent = nullptr);
    ~Yslugi();
    void setQuery(QSqlQuery &query);
    void setTable();


private slots:
    void on_pushButtonOpenWindowInsert_clicked();

    void on_pushButtonUpdate_clicked();

    void on_pushButtonDelete_clicked();

    void on_pushButtonBack_clicked();

    void on_pushButton_Category_clicked();

private:
    Ui::Yslugi *ui;
};

#endif // YSLUGI_H
