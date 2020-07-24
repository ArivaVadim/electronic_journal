#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <clients.h>
#include <masters.h>
#include <yslugi.h>
#include <journal.h>
#include <QSql>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QFileDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Clients clientsWindow;
    Masters mastersWindow;
    Yslugi yslugiWindow;
    Journal journalWindow;
    QSqlQuery query;
    QSqlDatabase database;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool connectToDataBase();
    void errorConnectMessage();
    void connectToServer();

private slots:
    void on_pushButtonCLIENTS_clicked();

    void on_pushButtonMASTERS_clicked();

    void on_pushButtonUSLUGI_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
