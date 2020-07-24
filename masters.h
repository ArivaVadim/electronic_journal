#ifndef MASTERS_H
#define MASTERS_H

#include <QDialog>
#include <QSql>
#include <QSqlQuery>
#include "mastersinsert.h"
#include "masterdelete.h"
#include "mastersupdate.h"
#include "clientscategory.h"

namespace Ui {
class Masters;
}

class Masters : public QDialog
{
    Q_OBJECT
    QSqlQuery queryMasters;
    MastersInsert mastersInsWindow;
    MasterDelete masterDelWindow;
    MastersUpdate masterUpdWindow;
    ClientsCategory categorysWindow;

public:
    explicit Masters(QWidget *parent = nullptr);
    ~Masters();
    void setQueryMasters(QSqlQuery &query);
    void setTableMasters();

private slots:
    void on_pushButtonBack_clicked();

    void on_pushButtonOpenWindowInsert_clicked();

    void on_pushButtonDelete_clicked();

    void on_pushButtonUpdate_clicked();

    void on_pushButton_Category_clicked();

private:
    Ui::Masters *ui;
};

#endif // MASTERS_H
