#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QDir>
#include "hash.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_hashButton_clicked();

    void on_Browse_Button_clicked();

    void on_DeleteButton_clicked();

    void on_StopButton_clicked();

private:

    Hash Q;

    Ui::MainWindow *ui;

    bool flag;

    int files_size();

    void hashing(QString File_name, int row);

    void start(const QDir& dir);
};

#endif // MAINWINDOW_HPP
