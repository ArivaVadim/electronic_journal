#ifndef JOURNAL_H
#define JOURNAL_H

#include <QDialog>
#include <QSqlQuery>
#include <QTableWidget>
#include <QDebug>
#include <QMessageBox>
#include <QSqlRecord>
#include <QDate>
#include <QToolTip>
#include <QItemDelegate>
#include <QApplication>
#include <QSqlQueryModel>
#include "journaladdclient.h"

namespace Ui {
class Journal;
}

class Journal : public QDialog
{
    Q_OBJECT
    JournalAddClient window;
    QSqlQuery queryJournal;
    QString DATE;
    QString text;
    QString time;
    QString selectedMaster;
    QString columnNumber;
    QString *selectedMasterArray = new QString [4];


public:
    explicit Journal(QWidget *parent = nullptr);
    ~Journal();
    void setQuery(QSqlQuery &query);
    void createTable();
    void setTableInfo();
    bool deleteTable();
    void createQWTable();
    void getTableChanges();
    void setMasters();
    void openTable();
    void addMaster();
    void getSelectedMasterInfo();
    void deleteQWTable();
    void sizeOfTable();
    void setDate();
    void getDate();
    void deleteMasters();

signals:
    void cellClicked(int row, int column);

private slots:
    void on_pushButtonBack_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_dateEdit_userDateChanged(const QDate &date);

    void infoTW();

private:
    Ui::Journal *ui;

};


#endif // JOURNAL_H
