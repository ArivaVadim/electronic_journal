#ifndef MASTERDELETE_H
#define MASTERDELETE_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class MasterDelete;
}

class MasterDelete : public QDialog
{
    Q_OBJECT
    QSqlQuery   queryDeleteMaster;
    QString     ID;
    bool        infoOpen = false;

public:
    explicit MasterDelete(QWidget *parent = nullptr);
    ~MasterDelete();
    void setQuery(QSqlQuery &query);
    bool getMasterInfo();


private slots:
    void on_pushButtonSearch_clicked();

    void on_pushButtonDELETE_clicked();

    void on_pushButtonBack_clicked();

private:
    Ui::MasterDelete *ui;
};

#endif // MASTERDELETE_H
