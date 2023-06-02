#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QRegularExpression>

double current_value = 0.0;
bool division_trigger = false,
     multiplication_trigger = false,
     addition_trigger = false,
     substraction_trigger = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->display->setText(QString::number(current_value));

    // Tie the number buttons to the appropriate function
    QPushButton *number_buttons[10];
    for (int i {}; i < 10; i++) {
        QString button_name = QString("button_" + QString::number(i));
        number_buttons[i] = MainWindow::findChild<QPushButton *>(button_name);
        connect(number_buttons[i], SIGNAL(released()), this, SLOT(numPressed()));
    }

    // Tie the operator buttons to the appropriate function
    QPushButton *operator_buttons[4];
    operator_buttons[0] = MainWindow::findChild<QPushButton *>("button_add");
    operator_buttons[1] = MainWindow::findChild<QPushButton *>("button_substract");
    operator_buttons[2] = MainWindow::findChild<QPushButton *>("button_divide");
    operator_buttons[3] = MainWindow::findChild<QPushButton *>("button_times");

    for (int i {}; i < 4; i++) {
        connect(operator_buttons[i], SIGNAL(released()), this, SLOT(operatorPressed()));
    }

    // Tie the equals button to the appropriate function
    QPushButton *equals_button = MainWindow::findChild<QPushButton *>("button_equals");
    connect(equals_button, SIGNAL(released()), this, SLOT(equalsPressed()));

    // Tie the sign change button to the appropriate function
    QPushButton *sign_change_button = MainWindow::findChild<QPushButton *>("button_sign");
    connect(sign_change_button, SIGNAL(released()), this, SLOT(changeSign()));

    // Tie the clear button to the appropriate function
    QPushButton *clear_button = MainWindow::findChild<QPushButton *>("button_clear");
    connect(clear_button, SIGNAL(released()), this, SLOT(clearPressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::numPressed() {

    QPushButton *pressed_button = (QPushButton *)sender();
    QString button_value = pressed_button->text();

    QString display_value = ui->display->text();

    if (display_value.toDouble() == 0 || display_value.toDouble() == 0.0) {
        ui->display->setText(button_value);
    } else {
        QString new_value = QString(display_value + button_value);
        double converted_new_value = new_value.toDouble();
        ui->display->setText(QString::number(converted_new_value, 'g', 16));
    }


}

void MainWindow::operatorPressed() {

    division_trigger = false;
    multiplication_trigger = false;
    addition_trigger = false;
    substraction_trigger = false;

    QString display_value = ui->display->text();
    current_value = display_value.toDouble();
    QPushButton *selected_operation = (QPushButton *)sender();
    QString operation = selected_operation->text();

    if (QString::compare(operation, "/", Qt::CaseInsensitive) == 0) {
        division_trigger = true;
    } else if (QString::compare(operation, "*", Qt::CaseInsensitive) == 0) {
        multiplication_trigger = true;
    } else if (QString::compare(operation, "+", Qt::CaseInsensitive) == 0) {
        addition_trigger = true;
    } else if (QString::compare(operation, "-", Qt::CaseInsensitive) == 0) {
        substraction_trigger = true;
    }

    ui->display->setText("0.0");
}

void MainWindow::equalsPressed() {

    double solution = 0.0;
    QString display_value = ui->display->text();
    double converted_display_value = display_value.toDouble();

    // Check that an operation was selected first
    if (division_trigger) {
        solution = current_value / converted_display_value;
    } else if (multiplication_trigger) {
        solution = current_value * converted_display_value;
    } else if (addition_trigger) {
        solution = current_value + converted_display_value;
    } else if (substraction_trigger) {
        solution = current_value - converted_display_value;
    }

    // Display solution
    ui->display->setText(QString::number(solution));
}

void MainWindow::changeSign() {
    QString display_value = ui->display->text();
    QRegularExpression expression = QRegularExpression("[-]?[0-9]*");
    QRegularExpressionMatch match = expression.match(display_value);

    if (match.hasMatch()) {
        double converted_display_value = display_value.toDouble();
        converted_display_value *= -1;
        ui->display->setText(QString::number(converted_display_value));
    }
}

void MainWindow::clearPressed() {
    ui->display->setText("0.0");
    current_value = 0.0;
}
