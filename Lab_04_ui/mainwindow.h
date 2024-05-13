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
#include <string>
#include <iostream>
#include <QProcess>
#include <QDebug>
#include <QMessageBox>
#include "mfile.h"
#include "ode.h"
#include "point.h"
#include "polynomial.h"
#include "slae.h"
#include "table.h"

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

    void on_pushButtonSolveFx_clicked();

    void on_pushButtonSolveZxy_clicked();

    void on_pushButtonODE_clicked();

private:
    Ui::MainWindow *ui;
    void *pythonLib;  // Handle for the Python library
};
#endif // MAINWINDOW_H
