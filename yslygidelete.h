#ifndef YSLYGIDELETE_H
#define YSLYGIDELETE_H

#include <QDialog>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class YslygiDelete;
}

class YslygiDelete : public QDialog
{
    Q_OBJECT
    QSqlQuery   queryDelete;
    QString     ID;
    bool        infoOpen = false;

public:
    explicit YslygiDelete(QWidget *parent = nullptr);
    ~YslygiDelete();
    void setQuery(QSqlQuery &query);
    bool getInfo();

private slots:
    void on_pushButtonSearch_clicked();

    void on_pushButtonDELETE_clicked();

    void on_pushButtonBack_clicked();

private:
    Ui::YslygiDelete *ui;
};

#endif // YSLYGIDELETE_H
