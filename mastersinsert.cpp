#include "mastersinsert.h"
#include "ui_mastersinsert.h"
#include <QDebug>

MastersInsert::MastersInsert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MastersInsert)
{
    ui->setupUi(this);
    setWindowTitle("Добавление мастеров");
}

MastersInsert::~MastersInsert()
{
    delete ui;
}

void MastersInsert :: setQuery(QSqlQuery &query)
{
    this -> query = query;
}

void MastersInsert :: setMastersCategories()
{
    QString cat;
    query.exec("SELECT name_category FROM MastersCategories");
    for (int i=0; query.next(); i++)
    {
        cat = query.value(0).toString();
        ui -> comboBox -> insertItems(i,QStringList(cat));
    }
}

void MastersInsert :: getInfoMasterInsert()
{
    category    = ui ->comboBox             -> currentText();
    phone       = ui ->lineEditcellnumber   -> text();
    name        = ui ->lineEditname         -> text();
    firstname   = ui ->lineEditfirstname    -> text();
    famname     = ui ->lineEditfam          -> text();
    birth       = ui ->lineEditbirth        -> text();
}

void MastersInsert :: insertMaster()
{
    query.prepare("INSERT INTO Masters (id_cat_master,name_master,fam_master,firstname_master,birth_master,phone_master) "
                               "VALUES('"+ category+"','"+name+"','"+famname+"','"+firstname+"','"+birth+"','"+phone+"')");
    query.exec();
    niceCardNumWindow();
}

void MastersInsert :: niceCardNumWindow()
{
    QMessageBox msbox;
    msbox.setWindowTitle("УСПЕШНО!");
    msbox.setText("Мастер добавлен в базу данных!");
    msbox.exec();
}

void MastersInsert :: setClearMasterInfo()
{
    ui ->comboBox           -> clear();
    ui ->lineEditcellnumber -> clear();
    ui ->lineEditname       -> clear();
    ui ->lineEditfirstname  -> clear();
    ui ->lineEditfam        -> clear();
    ui ->lineEditbirth      -> clear();
}
void MastersInsert::on_pushButton_clicked()
{
    setClearMasterInfo();
    this -> close();
}

void MastersInsert::on_pushButtonInsert_clicked()
{
    getInfoMasterInsert();
    insertMaster();
    setClearMasterInfo();
    this->close();
}
