#ifndef MASTERSUPDATE_H
#define MASTERSUPDATE_H

#include <QDialog>
#include <QSqlQuery>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class MastersUpdate;
}

class MastersUpdate : public QDialog
{
    Q_OBJECT
    QSqlQuery query;
    QString ID;
    QString category;
    QString phone;
    QString name;
    QString firstname;
    QString famname;
    QString birth;
    QString UID;

public:
    explicit MastersUpdate(QWidget *parent = nullptr);
    ~MastersUpdate();
    void setQuery(QSqlQuery &query);
    void getSearchMaster();
    void setUpdateMasterInfo();
    void updateMasterInfo();
    void niceCardNumWindow();
    void setClearMasterInfo();
    void setMastersCategories();

private slots:
    void on_pushButtonUpdateClient_clicked();

    void on_pushButtonReturn_clicked();

    void on_pushButtonSearch_clicked();

private:
    Ui::MastersUpdate *ui;
};

#endif // MASTERSUPDATE_H
