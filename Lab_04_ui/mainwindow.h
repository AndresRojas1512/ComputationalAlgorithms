#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Python.h>
#include <QMainWindow>
#include <random>
#include <QTableWidget>
#include <QRadioButton>
#include <QSpinBox>
#include <QPushButton>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void saveTableToCSV();

private slots:
    void on_pushButtonGenerateTable_clicked();

    void on_pushButtonSetAllWeightsSame_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
