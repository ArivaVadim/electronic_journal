#include "yslugi.h"
#include "ui_yslugi.h"

Yslugi::Yslugi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Yslugi)
{
    ui->setupUi(this);
    setWindowTitle("Услуги");
}

Yslugi::~Yslugi()
{
    delete ui;
}

void Yslugi :: setQuery(QSqlQuery &query)
{
    queryYslugi = query;
}

void Yslugi :: setTable()
{
    int SIZE=0;

    queryYslugi.exec("SELECT * FROM Yslygi");
    while(queryYslugi.next())
        SIZE++;

    ui->tableWidget->setRowCount(SIZE);
    queryYslugi.exec("SELECT * FROM Yslygi");
    int k = 0;
    while (queryYslugi.next())
    {
        for (int j=0;j<7;j++)
        {
            QString line = queryYslugi.value(j).toString();
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText(line);
            ui->tableWidget->setItem(k,j,item);
            if(j==2)
                ui->tableWidget->horizontalHeader()->setSectionResizeMode(j, QHeaderView::Stretch);
            else
                ui->tableWidget->horizontalHeader()->setSectionResizeMode(j, QHeaderView::ResizeToContents);
        }
        k++;
    }
}

void Yslugi::on_pushButtonOpenWindowInsert_clicked()
{
    insertWindow.setQuery(queryYslugi);
    insertWindow.setYslygiCategories();
    insertWindow.setModal(true);
    insertWindow.exec();
    setTable();
}

void Yslugi::on_pushButtonUpdate_clicked()
{
    updateWindow.setQuery(queryYslugi);
    updateWindow.setYslygiCategories();
    updateWindow.setModal(true);
    updateWindow.exec();
    setTable();
}

void Yslugi::on_pushButtonDelete_clicked()
{
    deleteWindow.setQuery(queryYslugi);
    deleteWindow.setModal(true);
    deleteWindow.exec();
    setTable();
}

void Yslugi::on_pushButtonBack_clicked()
{
    this -> close();
}

void Yslugi::on_pushButton_Category_clicked()
{
    categorysWindow.setQuery(queryYslugi);
    categorysWindow.openCatTable("YslygiCategories");
    categorysWindow.setInfoQW();
    categorysWindow.setModal(true);
    categorysWindow.exec();
    setTable();
}
