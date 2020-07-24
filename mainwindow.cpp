#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Electronic Journal");
    ui -> statusbar -> showMessage("v.1.9.4");
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow :: connectToDataBase()
{
    database = QSqlDatabase :: addDatabase("QSQLITE");
    database.setDatabaseName("E:/DOCUMENTS/QT/electronic_journal/database_electronic_journal.sqlite");  // проверить путь
    query = QSqlQuery(database);
    if (database.open())
        return true;
    else
        return false;
}

void MainWindow::on_pushButtonCLIENTS_clicked()
{
    if (connectToDataBase())
    {
        clientsWindow.setQuery(query);
        clientsWindow.setTableClients();
        clientsWindow.setModal(true);
        clientsWindow.exec();
    }
    else
        errorConnectMessage();
}

void MainWindow::on_pushButtonMASTERS_clicked()
{
    if (connectToDataBase())
    {
        mastersWindow.setQueryMasters(query);
        mastersWindow.setTableMasters();
        mastersWindow.setModal(true);
        mastersWindow.exec();
    }
    else
        errorConnectMessage();
}

void MainWindow::on_pushButtonUSLUGI_clicked()
{
    if (connectToDataBase())
    {
        yslugiWindow.setQuery(query);
        yslugiWindow.setTable();
        yslugiWindow.setModal(true);
        yslugiWindow.exec();
    }
    else
        errorConnectMessage();
}

void MainWindow::on_pushButton_4_clicked()
{
    if (connectToDataBase())
    {
        journalWindow.setQuery(query);
        journalWindow.setDate();
        journalWindow.getDate();
        journalWindow.createTable();
        journalWindow.setMasters();
        journalWindow.setTableInfo();
        journalWindow.setModal(true);
        journalWindow.exec();
        journalWindow.deleteQWTable();
    }
    else
        errorConnectMessage();
}

void MainWindow :: errorConnectMessage()
{
    QMessageBox msbox;
    msbox.setWindowTitle("ОШИБКА!");
    msbox.setText("Не удалось открыть базу данных.");
    msbox.exec();
}
