#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
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
    QString filePath = "/home/andres/Desktop/4Semester/CA/ComputationalAlgorithms/Lab_04_ui/data.csv";
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

void MainWindow::on_pushButtonSolveFx_clicked()
{
    std::string filename = "data.csv";
    int rows = 0;
    int columns = 0;
    Table table;
    std::vector<Point> grid;
    int exit_code = EXIT_SUCCESS;

    // Count rows and columns
    exit_code = file_count_rows(rows, filename.c_str());
    if (exit_code)
        return;
    exit_code = file_count_columns(columns, filename.c_str());
    if (exit_code)
        return;

    table = Table(rows, columns);
    exit_code = file_parse_1v(table, filename.c_str());
    if (exit_code)
        return;
    points_1v_load(grid, table);

    // Validate the degree
    int max_degree = rows - 1;

    // Collect checked degrees
    std::vector<int> checked_degrees;
    if (ui->checkBox_1->isChecked()) checked_degrees.push_back(1);
    if (ui->checkBox_2->isChecked()) checked_degrees.push_back(2);
    if (ui->checkBox_3->isChecked()) checked_degrees.push_back(3);
    if (ui->checkBox_4->isChecked()) checked_degrees.push_back(4);
    if (ui->checkBox_5->isChecked()) checked_degrees.push_back(5);
    if (ui->checkBox_6->isChecked()) checked_degrees.push_back(6);
    if (ui->checkBox_7->isChecked()) checked_degrees.push_back(7);
    if (ui->checkBox_8->isChecked()) checked_degrees.push_back(8);
    if (ui->checkBox_9->isChecked()) checked_degrees.push_back(9);
    if (ui->checkBox_10->isChecked()) checked_degrees.push_back(10);

    if (checked_degrees.empty()) {
        QMessageBox::warning(this, "Validation Error", "No degrees selected.");
        return;
    }

    for (int degree : checked_degrees) {
        if (degree >= rows) {
            QMessageBox::warning(this, "Validation Error", "Degree must be less than the number of data points.");
            return;
        }
    }

    QStringList solutionFiles;
    for (int degree : checked_degrees) {
        int nodes = degree + 1;
        Slae slae(nodes, nodes + 1);
        slae.compute_init_1v(grid);
        slae.lin_solve();
        QString solutionFile = QString("/home/andres/Desktop/4Semester/CA/ComputationalAlgorithms/Lab_04_ui/solution_%1d.csv").arg(degree);
        slae.write_solution_csv(solutionFile.toStdString());
        solutionFiles << solutionFile;
    }

    // Create the QProcess object
    QProcess *process = new QProcess(this);

    connect(process, &QProcess::finished, this, [this, process](int exitCode, QProcess::ExitStatus exitStatus) {
        qDebug() << "Process finished with exit code" << exitCode << "and status" << exitStatus;
        qDebug() << "Output:" << process->readAllStandardOutput();
        process->deleteLater();  // Clean up the QProcess object once done
    });

    connect(process, &QProcess::errorOccurred, this, [this, process](QProcess::ProcessError error) {
        qDebug() << "Process error:" << error << process->errorString();
        process->deleteLater();  // Clean up the QProcess object on error
    });

    // Path to the Python interpreter and the script
    QString pythonInterpreter = "python3";
    QString pythonScript = "/home/andres/Desktop/4Semester/CA/ComputationalAlgorithms/Lab_04_ui/Fxplot.py";

    // Start the process
    QStringList arguments;
    arguments << "/home/andres/Desktop/4Semester/CA/ComputationalAlgorithms/Lab_04_ui/data.csv" << solutionFiles;
    process->start(pythonInterpreter, QStringList() << pythonScript << arguments);

    // No need to wait for the process to finish
    qDebug() << "Started Python script for plotting solutions.";
}


void MainWindow::on_pushButtonSolveZxy_clicked()
{
    // todo
}

// ODE SOLUTION

double f0(double x) { return 1 - x; }
double f1(double x) { return x * (1 - x); }
double f2(double x) { return std::pow(x, 2) * (1 - x); }
double f3(double x) { return std::pow(x, 3) * (1 - x); }
double f4(double x) { return std::pow(x, 4) * (1 - x); }

double c0(double x) { return 1 - (4 * x); }
double c1(double x) { return -2 + 2 * x - 3 * std::pow(x, 2); }
double c2(double x) { return 2 - 6 * x + 3 * std::pow(x, 2) - 4 * std::pow(x, 3); }
double c3(double x) { return 6 * x - 12 * std::pow(x, 2) + 4 * std::pow(x, 3) - 5 * std::pow(x, 4); }
double c4(double x) { return 12 * std::pow(x, 2) - 20 * std::pow(x, 3) + 5 * std::pow(x, 4) + 6 * std::pow(x, 5); }

void MainWindow::on_pushButtonODE_clicked()
{
    std::vector<double> x_points = {0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1};
    std::vector<Func> funcs_2degree = {f0, f1, f2};
    std::vector<Func> coeffFuncs_2degree = {c0, c1, c2};

    std::vector<Func> funcs_3degree = {f0, f1, f2, f3};
    std::vector<Func> coeffFuncs_3degree = {c0, c1, c2, c3};

    std::vector<Func> funcs_4degree = {f0, f1, f2, f3, f4};
    std::vector<Func> coeffFuncs_4degree = {c0, c1, c2, c3, c4};

    Slae slae_ode_2degree(2, 2 + 1);
    Slae slae_ode_3degree(3, 3 + 1);
    Slae slae_ode_4degree(4, 4 + 1);

    GetApproximateODE(slae_ode_2degree, x_points, 2, funcs_2degree, coeffFuncs_2degree);
    slae_ode_2degree.lin_solve();
    std::cout << "ODE system 2 solution: " << std::endl;
    std::cout << slae_ode_2degree.get_system_solution() << std::endl;
    slae_ode_2degree.write_solution_csv("solution_2m.csv");

    GetApproximateODE(slae_ode_3degree, x_points, 3, funcs_3degree, coeffFuncs_3degree);
    slae_ode_3degree.lin_solve();
    std::cout << "Slae 3m: " << std::endl;
    std::cout << slae_ode_3degree;
    std::cout << "ODE system 3 solution: " << std::endl;
    std::cout << slae_ode_3degree.get_system_solution() << std::endl;
    slae_ode_3degree.write_solution_csv("solution_3m.csv");

    GetApproximateODE(slae_ode_4degree, x_points, 4, funcs_4degree, coeffFuncs_4degree);
    slae_ode_4degree.lin_solve();
    std::cout << "ODE system 4 solution: " << std::endl;
    std::cout << slae_ode_4degree.get_system_solution() << std::endl;
    slae_ode_4degree.write_solution_csv("solution_4m.csv");

    QString solution2Path = "solution_2m.csv";
    QString solution3Path = "solution_3m.csv";
    QString solution4Path = "solution_4m.csv";

    QProcess *process = new QProcess(this);

    connect(process, &QProcess::finished, this, [this, process](int exitCode, QProcess::ExitStatus exitStatus) {
        qDebug() << "Process finished with exit code" << exitCode << "and status" << exitStatus;
        qDebug() << "Output:" << process->readAllStandardOutput();
        process->deleteLater();  // Clean up the QProcess object once done
    });

    connect(process, &QProcess::errorOccurred, this, [this, process](QProcess::ProcessError error) {
        qDebug() << "Process error:" << error << process->errorString();
        process->deleteLater();  // Clean up the QProcess object on error
    });

    // Path to the Python interpreter and the script
    QString pythonInterpreter = "python3";
    QString pythonScript = "/home/andres/Desktop/4Semester/CA/ComputationalAlgorithms/Lab_04_ui/odeplot.py";

    // Arguments to pass to the script
    QStringList arguments;
    arguments << "solution_2m.csv" << "solution_3m.csv" << "solution_4m.csv";

    // Start the process
    process->start(pythonInterpreter, QStringList() << pythonScript << arguments);

    // No need to wait for the process to finish
    qDebug() << "Started Python script for plotting ODE solutions.";
}

