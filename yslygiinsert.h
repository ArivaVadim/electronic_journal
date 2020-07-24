#ifndef YSLYGIINSERT_H
#define YSLYGIINSERT_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class YslygiInsert;
}

class YslygiInsert : public QDialog
{
    Q_OBJECT
    QSqlQuery query;
    QString category;
    QString name;
    QString worktime;
    QString coast_mat;
    QString coast_work;
    QString coast_yslygi;

public:
    explicit YslygiInsert(QWidget *parent = nullptr);
    ~YslygiInsert();
    void setQuery(QSqlQuery &query);
    void getInfo();
    void insert();
    void niceinsertWindow();
    void setClearInfo();
    void setYslygiCategories();

private slots:
    void on_pushButtonInsert_clicked();

    void on_pushButton_clicked();

private:
    Ui::YslygiInsert *ui;
};

#endif // YSLYGIINSERT_H
