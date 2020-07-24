#include "mastersupdate.h"
#include "ui_mastersupdate.h"

MastersUpdate::MastersUpdate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MastersUpdate)
{
    ui->setupUi(this);
    setWindowTitle("Обновление мастеров");
}

MastersUpdate::~MastersUpdate()
{
    delete ui;
}

void MastersUpdate :: setQuery(QSqlQuery &query)
{
    this -> query = query;
}

void MastersUpdate :: setMastersCategories()
{
    QString cat;
    query.exec("SELECT name_category FROM MastersCategories");
    for (int i=0; query.next(); i++)
    {
        cat = query.value(0).toString();
        ui -> comboBox -> insertItems(i,QStringList(cat));
    }
}

void MastersUpdate :: getSearchMaster()
{
    ID = ui -> lineEdit ->text();
    query.exec("SELECT id_cat_master,name_master,fam_master,firstname_master,birth_master,phone_master "
                           "FROM Masters WHERE id_master = "+ID);
    while(query.next())
    {       
        ui->lineEditcellnumber  ->setText(query.value(5).toString());
        ui->lineEditname        ->setText(query.value(1).toString());
        ui->lineEditfirstname   ->setText(query.value(3).toString());
        ui->lineEditfam         ->setText(query.value(2).toString());
        ui->lineEditbirth       ->setText(query.value(4).toString());
    }

}

void MastersUpdate :: setUpdateMasterInfo()
{
    category    = ui ->comboBox             -> currentText();
    phone       = ui ->lineEditcellnumber   -> text();
    name        = ui ->lineEditname         -> text();
    firstname   = ui ->lineEditfirstname    -> text();
    famname     = ui ->lineEditfam          -> text();
    birth       = ui ->lineEditbirth        -> text();
}

void MastersUpdate :: updateMasterInfo()
{
    setUpdateMasterInfo();
    query.prepare("UPDATE Masters SET id_cat_master = '"+category+"',phone_master = '"+phone+"',"
                                "name_master = '"+name+"',firstname_master = '"+firstname+"',fam_master = '"+famname+"',birth_master = '"+birth+"' "
                                "WHERE id_master ="+ID);
    query.exec();
    niceCardNumWindow();
}

void MastersUpdate :: niceCardNumWindow()
{
    QMessageBox msbox;
    msbox.setWindowTitle("УСПЕШНО!");
    msbox.setText("Данные мастера обновлены!");
    msbox.exec();
}

void MastersUpdate :: setClearMasterInfo()
{
    ui->lineEdit            ->clear();
    ui->comboBox            ->clear();
    ui->lineEditcellnumber  ->clear();
    ui->lineEditname        ->clear();
    ui->lineEditfirstname   ->clear();
    ui->lineEditfam         ->clear();
    ui->lineEditbirth       ->clear();
}

void MastersUpdate::on_pushButtonUpdateClient_clicked()
{
    updateMasterInfo();
}

void MastersUpdate::on_pushButtonReturn_clicked()
{
    setClearMasterInfo();
    this->close();
}

void MastersUpdate::on_pushButtonSearch_clicked()
{
    getSearchMaster();
}
