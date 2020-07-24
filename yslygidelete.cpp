#include "yslygidelete.h"
#include "ui_yslygidelete.h"

YslygiDelete::YslygiDelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::YslygiDelete)
{
    ui->setupUi(this);
    setWindowTitle("Удаление услуг");
}

YslygiDelete::~YslygiDelete()
{
    delete ui;
}

void YslygiDelete :: setQuery(QSqlQuery &query)
{
    queryDelete = query;
}

bool YslygiDelete :: getInfo()            //добавить логику для случая, когда услуги не существует
{
    ID = ui ->lineEditID -> text();
    queryDelete.exec("SELECT * FROM Yslygi Where id_uslugi = " + ID);
    QString *line = new QString [7];
    while (queryDelete.next())
    {
        for (int i=0;i<7;i++)
            line[i] = queryDelete.value(i).toString();
    }
    QMessageBox msbox;
    msbox.setWindowTitle("ID = "+ID);
    msbox.setText("Услуга: "+ line[2]);
    msbox.exec();
    infoOpen = true;
    delete [] line;
    return infoOpen;
}

void YslygiDelete::on_pushButtonSearch_clicked()
{
    getInfo();
}

void YslygiDelete::on_pushButtonDELETE_clicked()
{
    if(infoOpen)
    {
        ID = ui ->lineEditID -> text();
        queryDelete.prepare("DELETE FROM Yslygi WHERE id_uslugi = "+ ID);
        queryDelete.exec();
        QMessageBox msbox;
        msbox.setWindowTitle("УСПЕШНО!");
        msbox.setText("Услуга удалёна из базы данных");
        msbox.exec();
        ui ->lineEditID -> clear();
        this->close();
    }
    else
        return;
}

void YslygiDelete::on_pushButtonBack_clicked()
{
    this -> close();
}
