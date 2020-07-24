#ifndef CLIENTSCATEGORY_H
#define CLIENTSCATEGORY_H

#include <QDialog>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QTabWidget>
#include <QStyleOption>
#include <QItemDelegate>

namespace Ui {
class ClientsCategory;
}

class ClientsCategory : public QDialog
{
    Q_OBJECT
    QSqlQuery query;
    QString table_name;


public:
    explicit ClientsCategory(QWidget *parent = nullptr);
    ~ClientsCategory();
    void setQuery(QSqlQuery &query);
    void setInfoQW();
    void getInfoQW();
    void openCatTable(const QString &table_name);
    void creatCatTable();
    void deleteINCatTable();
    void insertINCatTable();

private slots:
    void on_pushButton_Save_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_AddRow_clicked();

    void on_pushButton_DelRow_clicked();

private:
    Ui::ClientsCategory *ui;
};

class NonEditTableColumnDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    NonEditTableColumnDelegate(QObject * parent = 0) : QItemDelegate(parent)
    {

    }

    virtual QWidget * createEditor ( QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const
    {
        return 0;
    }
};

#endif // CLIENTSCATEGORY_H
