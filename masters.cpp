#include "masters.h"
#include "ui_masters.h"

Masters::Masters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Masters)
{
    ui->setupUi(this);
    setWindowTitle("Мастера");
}

Masters::~Masters()
{
    delete ui;
}

void Masters :: setQueryMasters(QSqlQuery &query)
{
    queryMasters = query;
}

void Masters :: setTableMasters()
{
    int SIZE=0;

    queryMasters.exec("SELECT * FROM Masters");
    while(queryMasters.next())
        SIZE++;

    ui->tableWidget->setRowCount(SIZE);
    queryMasters.exec("SELECT * FROM Masters");
    int k = 0;
    while (queryMasters.next())
    {
        for (int j=0;j<8;j++)
        {
            QString line = queryMasters.value(j).toString();
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText(line);
            ui->tableWidget->setItem(k,j,item);
            ui->tableWidget->horizontalHeader()->setSectionResizeMode(j, QHeaderView::Stretch);
        }
        k++;
    }
}

void Masters::on_pushButtonBack_clicked()
{
    this -> close();
}

void Masters::on_pushButtonOpenWindowInsert_clicked()
{
    mastersInsWindow.setQuery(queryMasters);
    mastersInsWindow.setMastersCategories();
    mastersInsWindow.setModal(true);
    mastersInsWindow.exec();
    setTableMasters();
}

void Masters::on_pushButtonDelete_clicked()
{
    masterDelWindow.setQuery(queryMasters);
    masterDelWindow.setModal(true);
    masterDelWindow.exec();
    setTableMasters();
}

void Masters::on_pushButtonUpdate_clicked()
{
    masterUpdWindow.setQuery(queryMasters);
    masterUpdWindow.setMastersCategories();
    masterUpdWindow.setModal(true);
    masterUpdWindow.exec();
    setTableMasters();
}

void Masters::on_pushButton_Category_clicked()
{
    categorysWindow.setQuery(queryMasters);
    categorysWindow.openCatTable("MastersCategories");
    categorysWindow.setInfoQW();
    categorysWindow.setModal(true);
    categorysWindow.exec();
    setTableMasters();
}
