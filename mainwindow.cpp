#include "mainwindow.h"
#include "./ui_mainwindow.h"

double current_value = 0.0;
bool division_trigger = false,
     multiplication_trigger = false,
     addition_trigger = false,
     substraction_trigger = false;

bool is_negative = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->display->setText(QString::number(current_value));

    QPushButton *number_buttons[10];
    for (int i {}; i < 10; i++) {
        QString button_name = QString("button_" + QString::number(i));
        number_buttons[i] = MainWindow::findChild<QPushButton *>(button_name);
        connect(number_buttons[i], SIGNAL(released()), this, SLOT(numPressed()));
    }

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
