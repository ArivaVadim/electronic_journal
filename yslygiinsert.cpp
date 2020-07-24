#include "yslygiinsert.h"
#include "ui_yslygiinsert.h"

YslygiInsert::YslygiInsert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::YslygiInsert)
{
    ui->setupUi(this);
    setWindowTitle("Добавление услуг");
}

YslygiInsert::~YslygiInsert()
{
    delete ui;
}

void YslygiInsert :: setQuery(QSqlQuery &query)
{
    this -> query = query;
}

void YslygiInsert :: setYslygiCategories()
{
    QString cat;
    query.exec("SELECT name_category FROM YslygiCategories");
    for (int i=0; query.next(); i++)
    {
        cat = query.value(0).toString();
        ui -> comboBox -> insertItems(i,QStringList(cat));
    }
}

void YslygiInsert :: getInfo()
{
    category    = ui ->comboBox             -> currentText();
    name        = ui ->lineEditcellname     -> text();
    worktime    = ui ->lineEditworktime     -> text();
    coast_mat   = ui ->lineEditcoastmat     -> text();
    coast_work  = ui ->lineEditcoastwork    -> text();
    coast_yslygi= ui ->lineEditbcoastyslygi -> text();
}

void YslygiInsert :: insert()
{
    query.prepare("INSERT INTO Yslygi (id_cat_uslug,name_yslugi,work_time,cost_mat,cost_rabot,cost_yslug) "
                               "VALUES('"+ category+"','"+name+"','"+worktime+"','"+coast_mat+"','"+coast_work+"','"+coast_yslygi+"')");
    query.exec();
    niceinsertWindow();
    setClearInfo();
    this->close();
}

void YslygiInsert :: niceinsertWindow()
{
    QMessageBox msbox;
    msbox.setWindowTitle("УСПЕШНО!");
    msbox.setText("Новая услуга добавлена в базу данных!");
    msbox.exec();
}

void YslygiInsert :: setClearInfo()
{
    ui ->comboBox            -> clear();
    ui ->lineEditcellname       -> clear();
    ui ->lineEditworktime       -> clear();
    ui ->lineEditcoastmat       -> clear();
    ui ->lineEditcoastwork      -> clear();
    ui ->lineEditbcoastyslygi   -> clear();
}

void YslygiInsert::on_pushButtonInsert_clicked()
{
    getInfo();
    insert();
    setClearInfo();
    this -> close();
}

void YslygiInsert::on_pushButton_clicked()
{
    setClearInfo();
    this -> close();
}
