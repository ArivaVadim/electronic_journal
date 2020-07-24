#ifndef MASTERSINSERT_H
#define MASTERSINSERT_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class MastersInsert;
}

class MastersInsert : public QDialog
{
    Q_OBJECT
    QSqlQuery query;
    QString category;
    QString phone;
    QString name;
    QString firstname;
    QString famname;
    QString birth;


public:
    explicit MastersInsert(QWidget *parent = nullptr);
    ~MastersInsert();
    void setQuery(QSqlQuery &query);
    void getInfoMasterInsert();
    void insertMaster();
    void niceCardNumWindow();
    void setClearMasterInfo();
    void setMastersCategories();

private slots:
    void on_pushButton_clicked();

    void on_pushButtonInsert_clicked();

private:
    Ui::MastersInsert *ui;
};

#endif // MASTERSINSERT_H
