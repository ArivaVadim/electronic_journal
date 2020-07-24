#include "clientscategory.h"
#include "ui_clientscategory.h"

ClientsCategory::ClientsCategory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientsCategory)
{
    ui->setupUi(this);
    setWindowTitle("Добавление и редактирование категорий");
    ui->pushButton_Save->setToolTip("Нажмите для сохранения измененных значений");
    ui->pushButton_2->setToolTip("Вернуться к списку Клиентов");
    ui->pushButton_AddRow->setToolTip("Нажмите для добавления новой строки(поля)");
    ui->pushButton_DelRow->setToolTip("Нажмите для удаления крайней строки(поля)");
}

ClientsCategory::~ClientsCategory()
{
    ui -> tableWidget_Category -> clear();
    ui->tableWidget_Category->setRowCount(0);
    ui->tableWidget_Category->setColumnCount(0);
    delete ui;
}

void ClientsCategory :: setQuery(QSqlQuery &query)
{
    this -> query = query;
}

void ClientsCategory :: openCatTable(const QString &table_name)
{
    this -> table_name = table_name;
    if(!query.exec("SELECT * FROM "+table_name))
        creatCatTable();
    setInfoQW();
}

void ClientsCategory :: creatCatTable()
{
    query.exec("CREATE TABLE '"+table_name+"' (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, name_category TEXT NOT NULL)");
}

void ClientsCategory :: setInfoQW()
{
    ui -> tableWidget_Category -> clear();
    ui->tableWidget_Category->setRowCount(0);
    ui->tableWidget_Category->setColumnCount(0);

    ui->tableWidget_Category->setColumnCount(2);                                             // Указываем число колонок
    ui->tableWidget_Category->setShowGrid(true);                                             // Включаем сетку
    ui->tableWidget_Category->setSelectionMode(QAbstractItemView::SingleSelection);          // Разрешаем выделение только одного элемента
    ui->tableWidget_Category->setSelectionBehavior(QAbstractItemView::SelectRows);           // Разрешаем выделение построчно
    ui->tableWidget_Category->setHorizontalHeaderLabels(QStringList ("ID")<<("Значение"));
    ui->tableWidget_Category->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableWidget_Category->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget_Category->setItemDelegateForColumn(0,new NonEditTableColumnDelegate);

    int rows = 0;
    query.exec("SELECT * FROM "+table_name);
    while(query.next())
        rows++;
    ui->tableWidget_Category->setRowCount(rows);
    query.exec("SELECT * FROM "+table_name);
    int k = 0;
    while (query.next())
    {
        for (int j=0;j<2;j++)
        {
            QString line = query.value(j).toString();
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setText(line);
            ui->tableWidget_Category->setItem(k,j,item);
        }
        k++;
    }
}

void ClientsCategory :: getInfoQW()
{
    QString text, ID;
    QSqlRecord name;
    name = query.record();
    for (int i =0; i < ui -> tableWidget_Category -> rowCount(); i++)
    {
        ID = ui -> tableWidget_Category -> item(i,0) -> text();
        text = ui -> tableWidget_Category -> item(i,1) -> text();
        query.prepare("UPDATE '"+table_name+"' SET name_category = '"+text+"' WHERE id = "+ID);
        query.exec();
    }
}

void ClientsCategory :: deleteINCatTable()
{
    int rows = 0;
    query.exec("SELECT * FROM "+table_name);
    while(query.next())
        rows++;
    QString LAST;
    LAST.setNum(rows);
    query.exec("DELETE FROM '"+table_name+"' WHERE id = "+LAST);
}

void ClientsCategory :: insertINCatTable()
{
    query.prepare("INSERT INTO '"+table_name+"' (name_category) VALUES(' ')");query.exec();
}

void ClientsCategory::on_pushButton_Save_clicked()
{
    getInfoQW();
    setInfoQW();
}

void ClientsCategory::on_pushButton_2_clicked()
{
    this -> close();
}

void ClientsCategory::on_pushButton_AddRow_clicked()
{
    insertINCatTable();
    getInfoQW();
    setInfoQW();
}

void ClientsCategory::on_pushButton_DelRow_clicked()
{
    deleteINCatTable();
    setInfoQW();
}
