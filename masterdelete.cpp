#include "masterdelete.h"
#include "ui_masterdelete.h"

MasterDelete::MasterDelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MasterDelete)
{
    ui->setupUi(this);
    setWindowTitle("Удаление мастеров");
}

MasterDelete::~MasterDelete()
{
    delete ui;
}

void MasterDelete :: setQuery(QSqlQuery &query)
{
    queryDeleteMaster = query;
}

bool MasterDelete :: getMasterInfo()            //добавить логику для случая, когда мастера не существует
{
    ID = ui ->lineEditID -> text();
    queryDeleteMaster.exec("SELECT * FROM Masters Where id_master = " + ID);
    QString *line = new QString [8];
    while (queryDeleteMaster.next())
    {
        for (int i=0;i<8;i++)
            line[i] = queryDeleteMaster.value(i).toString();
    }
    QMessageBox msbox;
    msbox.setWindowTitle("Мастер ID = "+ID);
    msbox.setText("Имя: "+ line[2]+". Фамилия: "+ line[3]+". Отчество: "+line[4]);
    msbox.exec();
    infoOpen = true;
    delete [] line;
    return infoOpen;
}


void MasterDelete::on_pushButtonSearch_clicked()
{
    getMasterInfo();
}

void MasterDelete::on_pushButtonDELETE_clicked()
{
    if(infoOpen)
    {
        ID = ui ->lineEditID -> text();
        queryDeleteMaster.prepare("DELETE FROM Masters WHERE id_master = "+ ID);
        queryDeleteMaster.exec();
        QMessageBox msbox;
        msbox.setWindowTitle("УСПЕШНО!");
        msbox.setText("Мастер удалён из базы данных");
        msbox.exec();
        ui ->lineEditID -> clear();
        this->close();
    }
    else
        return;
}

void MasterDelete::on_pushButtonBack_clicked()
{
    this -> close();
}
