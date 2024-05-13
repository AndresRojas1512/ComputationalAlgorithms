#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tableWidget, &QTableWidget::itemChanged, this, &MainWindow::saveTableToCSV);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonGenerateTable_clicked() {
    // Get the number of points to generate
    int nPoints = ui->spinBoxNPoints->value();

    // Prepare a random number generator
    std::random_device rd;  // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_real_distribution<> dis(0, 100);  // range for x, y, z values
    std::uniform_real_distribution<> disWeight(0.1, 10);  // range for weight, no negative weights

    // Clear previous data
    ui->tableWidget->setRowCount(0);

    // Determine if the weight is to be the same for all points
    double weight;
    bool useSameWeight = ui->checkBoxSameWeight->isChecked();
    if (useSameWeight) {
        weight = ui->doubleSpinBoxSameWeight->value();
    }

    if (ui->radioButton_SVFunction->isChecked()) {
        ui->tableWidget->setColumnCount(3); // Set columns for x, y, weight
        QStringList headers = {"X", "Y", "Weight"};
        ui->tableWidget->setHorizontalHeaderLabels(headers);

        for (int i = 0; i < nPoints; ++i) {
            double x = dis(gen);
            double y = dis(gen);  // Generate a Y value as function value

            // Generate weight if not using a uniform weight
            double finalWeight = useSameWeight ? weight : disWeight(gen);

            // Insert new row
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);

            // Set values in the new row
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(x)));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(y)));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(finalWeight)));
        }
    } else if (ui->radioButtonTVFunction->isChecked()) {
        ui->tableWidget->setColumnCount(4); // Set columns for x, y, z, weight
        QStringList headers = {"X", "Y", "Z", "Weight"};
        ui->tableWidget->setHorizontalHeaderLabels(headers);

        for (int i = 0; i < nPoints; ++i) {
            double x = dis(gen);
            double y = dis(gen);
            double z = dis(gen);  // Generate a Z value for the 2-variable function

            // Generate weight if not using a uniform weight
            double finalWeight = useSameWeight ? weight : disWeight(gen);

            // Insert new row
            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);

            // Set values in the new row
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(x)));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(y)));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(z)));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(finalWeight)));
        }
    }
    saveTableToCSV();
}

void MainWindow::on_pushButtonSetAllWeightsSame_clicked()
{
    double weight = ui->doubleSpinBoxSameWeight->value();

    // Check which type of data we're working with: f(x) or z(x, y)
    bool isSingleVariable = ui->radioButton_SVFunction->isChecked();

    // Determine which column index to modify based on the selected data type
    int weightColumn = isSingleVariable ? 2 : 3;

    // Update the weight column for all rows
    int rowCount = ui->tableWidget->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        ui->tableWidget->setItem(i, weightColumn, new QTableWidgetItem(QString::number(weight)));
    }
    saveTableToCSV();
}

void MainWindow::saveTableToCSV() {
    QString filePath = "/home/andres/Desktop/4Semester/CA/ComputationalAlgorithms/Lab_04/data.csv";
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);

        int columnCount = ui->tableWidget->columnCount();
        QString headerLine;

        // Determine the header based on the column count
        if (columnCount == 3) {
            headerLine = "x,y,weight";
        } else if (columnCount == 4) {
            headerLine = "x,y,z,weight";
        } else {
            // Fallback in case an unexpected column count occurs
            headerLine = "unknown";
        }

        // Write the header to the first line
        out << headerLine << "\n";

        int rowCount = ui->tableWidget->rowCount();

        // Write the data rows
        for (int i = 0; i < rowCount; ++i) {
            QStringList rowContents;
            for (int j = 0; j < columnCount; ++j) {
                QTableWidgetItem *item = ui->tableWidget->item(i, j);
                if (!item) {
                    rowContents << "";
                } else {
                    rowContents << item->text();
                }
            }
            out << rowContents.join(",") << "\n";
        }

        file.close();
    } else {
        // Handle file open error if necessary
        qDebug() << "Failed to open file for writing: " << filePath;
    }
}
