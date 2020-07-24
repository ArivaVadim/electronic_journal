#ifndef YSLYGIUPDATE_H
#define YSLYGIUPDATE_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class YslygiUpdate;
}

class YslygiUpdate : public QDialog
{
    Q_OBJECT
    QSqlQuery query;
    QString category;
    QString name;
    QString worktime;
    QString coast_mat;
    QString coast_work;
    QString coast_yslygi;
    QString ID;

public:
    explicit YslygiUpdate(QWidget *parent = nullptr);
    ~YslygiUpdate();
    void setQuery(QSqlQuery &query);
    void getSearch();
    void setInfo();
    void updateInfo();
    void niceWindow();
    void setClearInfo();
    void setYslygiCategories();

private slots:
    void on_pushButtonSearch_clicked();

    void on_pushButtonUpdateClient_clicked();

    void on_pushButtonReturn_clicked();

private:
    Ui::YslygiUpdate *ui;
};

#endif // YSLYGIUPDATE_H
