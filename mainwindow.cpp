#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <gcrypt.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <QFileDialog>
#include <QMessageBox>
#include <vector>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Table_name->setColumnWidth(0,250);
    ui->Table_name->setColumnWidth(1,750);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::files_size(){
    int sum = 0;

    for(int i = 0; i < ui->Table_name->rowCount(); ++i){
        sum += QFile(ui->Table_name->item(i,0)->text()).size();
    }
    return sum;
}


void MainWindow::on_hashButton_clicked()
{
    ui->Browse_Button->setEnabled(false);
    ui->DeleteButton->setEnabled(false);

    if (!Q.Open()){
        QMessageBox::critical(this,"Error 1","Discriptor Error");
        return;
    }

    for(int i = 0; i < ui->Table_name->rowCount(); ++i){
        QTableWidgetItem *item = new QTableWidgetItem("");
        ui->Table_name->setItem(i, 1, item);
    }
    ui->Table_name->resizeRowsToContents();
    ui->Table_name->repaint();

    flag = true;

    int total = files_size();
    ui->loadingBar->setMaximum(total);
    ui->loadingBar->setValue(0);

    for (int i = 0; i < ui->Table_name->rowCount() && flag; ++i){

        QString str = Q.hashing(ui->Table_name->item(i,0)->text(), ui->loadingBar);
        if (str == "")
            QMessageBox::critical(this,"Error 23", "Error 23");


        QTableWidgetItem *item = new QTableWidgetItem(str);
        ui->Table_name->setItem(i, 1, item);
        ui->Table_name->resizeRowToContents(i);
        ui->Table_name->repaint();
        QApplication::processEvents();

    }
    Q.Close();

    ui->loadingBar->setValue(total);

    ui->Browse_Button->setEnabled(true);
    ui->DeleteButton->setEnabled(true);
}

void MainWindow::start(const QDir& dir)
{
    QStringList listFiles = dir.entryList(QDir::Files);

    foreach (QString file, listFiles) {

        QTableWidgetItem *item = new QTableWidgetItem(dir.absoluteFilePath(file));
        item->setTextAlignment(Qt::AlignTop);
        ui->Table_name->insertRow(ui->Table_name->rowCount());
        ui->Table_name->setItem(ui->Table_name->rowCount()-1,0,item);

    }

    QStringList listDir = dir.entryList(QDir::Dirs);
    foreach (QString subdir, listDir) {
        if (subdir == "." || subdir == "..") {
            continue;
        }
        start(QDir(dir.absoluteFilePath(subdir)));
    }
}

void MainWindow::on_Browse_Button_clicked()
{
    QString Dname = QFileDialog::getExistingDirectory(this, "Open File", "/home");
    if (Dname != ""){
        ui->Outfiles->setText(Dname);
        ui->Table_name->setRowCount(0);
        start(QDir(Dname));
    }
}



void MainWindow::on_DeleteButton_clicked()
{
    ui->Table_name->removeRow(ui->Table_name->currentRow());
}

void MainWindow::on_StopButton_clicked()
{
    flag = false;
}
