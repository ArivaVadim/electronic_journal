#include "yslygiupdate.h"
#include "ui_yslygiupdate.h"

YslygiUpdate::YslygiUpdate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::YslygiUpdate)
{
    ui->setupUi(this);
    setWindowTitle("Обновление услуг");
}

YslygiUpdate::~YslygiUpdate()
{
    delete ui;
}

void YslygiUpdate :: setQuery(QSqlQuery &query)
{
    this -> query = query;
}

void YslygiUpdate :: setYslygiCategories()
{
    QString cat;
    query.exec("SELECT name_category FROM YslygiCategories");
    for (int i=0; query.next(); i++)
    {
        cat = query.value(0).toString();
        ui -> comboBox -> insertItems(i,QStringList(cat));
    }
}

void YslygiUpdate :: getSearch()
{
    ID = ui -> lineEdit ->text();
    query.exec("SELECT id_cat_uslug,name_yslugi,work_time,cost_mat,cost_rabot,cost_yslug "
                           "FROM Yslygi WHERE id_uslugi = "+ID);
    while(query.next())
    {        
        ui->lineEditname        ->setText(query.value(1).toString());
        ui->lineEditworktime    ->setText(query.value(2).toString());
        ui->lineEditmater       ->setText(query.value(3).toString());
        ui->lineEditwork        ->setText(query.value(4).toString());
        ui->lineEditcoastyslygi ->setText(query.value(5).toString());
    }
}

void YslygiUpdate :: setInfo()
{
    category        = ui ->comboBox             -> currentText();
    name            = ui ->lineEditname         -> text();
    worktime        = ui ->lineEditworktime     -> text();
    coast_mat       = ui ->lineEditmater        -> text();
    coast_work      = ui ->lineEditwork         -> text();
    coast_yslygi    = ui ->lineEditcoastyslygi  -> text();
}

void YslygiUpdate :: updateInfo()
{
    setInfo();
    query.prepare("UPDATE Yslygi SET id_cat_uslug = '"+category+"',name_yslugi = '"+name+"',"
                                "work_time = '"+worktime+"',cost_mat = '"+coast_mat+"',cost_rabot = '"+coast_work+"',cost_yslug = '"+coast_yslygi+"' "
                                "WHERE id_uslugi ="+ID);
    query.exec();
    niceWindow();
    setClearInfo();
}

void YslygiUpdate :: niceWindow()
{
    QMessageBox msbox;
    msbox.setWindowTitle("УСПЕШНО!");
    msbox.setText("Данные услуги обновлены!");
    msbox.exec();
}

void YslygiUpdate :: setClearInfo()
{
    ui->comboBox            ->clear();
    ui->lineEditname        ->clear();
    ui->lineEditworktime    ->clear();
    ui->lineEditmater       ->clear();
    ui->lineEditwork        ->clear();
    ui->lineEditcoastyslygi ->clear();
}
void YslygiUpdate::on_pushButtonSearch_clicked()
{
    getSearch();
}

void YslygiUpdate::on_pushButtonUpdateClient_clicked()
{
    updateInfo();
}

void YslygiUpdate::on_pushButtonReturn_clicked()
{
    setClearInfo();
    this -> close();
}
