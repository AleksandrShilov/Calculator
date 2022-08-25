#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graph.h"
#include "creditcalc.h"
#include "depositcalc.h"
#include "input_x.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->groupBox_2->hide();
    this->setMinimumHeight(395);
    this->setMinimumWidth(325);
    this->setMaximumHeight(395);
    this->setMaximumWidth(325);
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));

    connect(ui->pushButton_percent, SIGNAL(clicked()), this, SLOT(operations()));

    connect(ui->pushButton_sum, SIGNAL(clicked()), this, SLOT(arithmetic_operations()));
    connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(arithmetic_operations()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(arithmetic_operations()));
    connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(arithmetic_operations()));

    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(trigonometric_operations()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(trigonometric_operations()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(trigonometric_operations()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(trigonometric_operations()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(trigonometric_operations()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(trigonometric_operations()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(trigonometric_operations()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(trigonometric_operations()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::digits_numbers() {
    if (flag_signals.signal_pressed_eq && flag_signals.signal_pressed_x) {
        QPushButton *button = (QPushButton *)sender();
        QString new_label;
        new_label = ui->result_show->text();

        if (ui->result_show->text() == "0") {
            new_label = button->text();
        } else {
            new_label += button->text();
        }
        ui->result_show->setText(new_label);
        flag_signals.singnal_number = 0;
        flag_signals.signal_pressed_ar_operators = 1;
        flag_signals.signal_simle_line = 1;
        flag_signals.signal_pressed_tr_operators = 1;
        flag_signals.signal_pressed_dot = 1;
        flag_signals.signal_pressed_mod = 1;
        flag_signals.signal_pressed_sub = 1;
        flag_signals.signal_stop = 1;
    }
}

void MainWindow::on_pushButton_dot_clicked() {
    if (flag_signals.signal_pressed_eq) {
        if (flag_signals.signal_pressed_dot) {
            ui->result_show->setText(ui->result_show->text() + ".");
            flag_signals.signal_pressed_dot = 0;
        }
    }
}

void MainWindow::operations() {
    if (flag_signals.signal_pressed_eq) {
        QPushButton *button = (QPushButton *)sender();
        double all_numbers;
        QString new_label;

        if (button->text() == "%") {
            all_numbers = ((ui->result_show->text()).toDouble());
            all_numbers *= 0.01;
            new_label = QString::number(all_numbers, 'g', 15);
            ui->result_show->setText(new_label);
        }
        flag_signals.signal_pressed_dot = 1;
    }
}

void MainWindow::on_pushButton_eq_clicked() {
    QByteArray str_bit = ui->result_show->text().toLocal8Bit();
    char *res_str = str_bit.data();
    setlocale(LC_NUMERIC, "C");
    double result = 0;

    if (flag_signals.signal_pressed_x_true) {
        double temp_x;
        input_x input_X;
        input_X.setModal(true);
        input_X.exec();

        if (flag_signals.signal_pressed_ar_operators && flag_signals.signal_stop &&
            flag_signals.signal_pressed_mod) {
            temp_x = input_X.on_pushButton_ok_clicked();
            result = calc(res_str, temp_x);
            QString res_string;
            res_string = QString::number(result, 'g', 15);

            ui->result_show->setText(res_string);
            flag_signals.signal_pressed_eq = 0;
            flag_signals.signal_pressed_x_true = 0;
        }
    } else {
        if (flag_signals.signal_pressed_ar_operators && flag_signals.signal_stop &&
            flag_signals.signal_pressed_mod) {
            result = calc(res_str, 0);
            QString res_string;
            res_string = QString::number(result, 'g', 15);
            ui->result_show->setText(res_string);
            flag_signals.signal_pressed_eq = 0;
        }
    }
}

void MainWindow::arithmetic_operations() {
    if (flag_signals.signal_pressed_ar_operators && flag_signals.signal_pressed_eq &&
        flag_signals.signal_simle_line) {
        QPushButton *button = (QPushButton *)sender();
        if (button->text() == "+") {
            ui->result_show->setText(ui->result_show->text() + "+");
        } else if (button->text() == "*") {
            ui->result_show->setText(ui->result_show->text() + "*");
        } else if (button->text() == "/") {
            ui->result_show->setText(ui->result_show->text() + "/");
        } else if (button->text() == "^") {
            ui->result_show->setText(ui->result_show->text() + "^");
        } else if (button->text() == "^") {
            ui->result_show->setText(ui->result_show->text() + "^");
        }
        flag_signals.signal_pressed_ar_operators = 0;
        flag_signals.singnal_number = 1;
        flag_signals.signal_pressed_x = 1;
        flag_signals.signal_pressed_dot = 1;
        flag_signals.signal_pressed_sub = 0;
    }
}

void MainWindow::trigonometric_operations() {
    if (flag_signals.signal_pressed_eq && flag_signals.singnal_number && flag_signals.signal_pressed_x) {
        QPushButton *button = (QPushButton *)sender();
        if (ui->result_show->text() == "0" && button->text() != "") {
            ui->result_show->setText(button->text() + "(");
        } else {
            ui->result_show->setText(ui->result_show->text() + button->text() + "(");
        }
        flag_signals.signal_simle_line = 1;
        flag_signals.signal_pressed_brecket++;
        flag_signals.signal_pressed_tr_operators = 0;
        flag_signals.signal_pressed_ar_operators = 1;
        flag_signals.signal_pressed_x = 1;
        flag_signals.signal_pressed_dot = 1;
        flag_signals.signal_pressed_sub = 0;
    }
}

void MainWindow::on_pushButton_clear_clicked() {
    ui->result_show->setText("0");
    flag_signals.signal_pressed_eq = 1;
    flag_signals.signal_pressed_ac = 1;
    flag_signals.signal_pressed_ar_operators = 1;
    flag_signals.signal_simle_line = 1;
    flag_signals.singnal_number = 1;
    flag_signals.signal_pressed_brecket = 0;
    flag_signals.signal_simle_line = 0;
    flag_signals.signal_pressed_tr_operators = 1;
    flag_signals.signal_pressed_x = 1;
    flag_signals.signal_pressed_x_true = 0;
    flag_signals.signal_pressed_dot = 1;
    flag_signals.signal_pressed_mod = 1;
    flag_signals.signal_pressed_sub = 1;
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1) {
    if (arg1 == "Расширенный") {
        this->setMaximumWidth(521);
        this->setMinimumWidth(521);
        ui->groupBox_2->show();
        this->resize(521, 395);
    } else if (arg1 == "Обычный") {
        this->setMaximumWidth(325);
        this->setMinimumWidth(325);
        ui->groupBox_2->hide();
        this->resize(325, 395);
    }
}

void MainWindow::on_pushButton_graph_clicked() {
    QString label;
    label = ui->result_show->text();

    if (label.length() <= 255) {
        Graph graph(nullptr, label);
        graph.setModal(true);
        graph.exec();
    }
}

void MainWindow::on_pushButton_credit_clicked() {
    creditCalc credit;
    credit.setModal(true);
    credit.exec();
}

void MainWindow::on_pushButton_deposit_clicked() {
    depositCalc deposit_calc;
    deposit_calc.setModal(true);
    deposit_calc.exec();
}

void MainWindow::on_pushButton_bracket_l_clicked() {
    if (flag_signals.signal_pressed_eq && flag_signals.signal_pressed_brecket >= 0) {
        if (ui->result_show->text() == "0") {
            ui->result_show->setText("(");
        } else {
            ui->result_show->setText(ui->result_show->text() + "(");
        }
        flag_signals.signal_pressed_brecket++;
        flag_signals.signal_simle_line = 1;
        flag_signals.signal_pressed_sub = 1;
    }
}

void MainWindow::on_pushButton_bracket_r_clicked() {
    if (flag_signals.signal_pressed_eq && flag_signals.signal_pressed_brecket != 0) {
        ui->result_show->setText(ui->result_show->text() + ")");
        flag_signals.signal_pressed_brecket--;
        flag_signals.signal_simle_line = 1;
        flag_signals.signal_pressed_tr_operators = 1;
        flag_signals.signal_stop = 1;
        flag_signals.signal_pressed_sub = 1;
    }
}

void MainWindow::on_pushButton_sqrt_clicked() {
    if (flag_signals.singnal_number && flag_signals.signal_pressed_x) {
        if (flag_signals.signal_pressed_eq) {
            if (ui->result_show->text() == "0") {
                 ui->result_show->setText("sqrt(");
            } else {
                 ui->result_show->setText(ui->result_show->text() + "sqrt(");
            }
            flag_signals.signal_pressed_brecket++;
        }
    }
}

void MainWindow::on_pushButton_mod_clicked() {
    if (flag_signals.signal_pressed_ar_operators && flag_signals.signal_simle_line &&
            flag_signals.signal_pressed_tr_operators && flag_signals.signal_pressed_mod) {
        ui->result_show->setText(ui->result_show->text() + "mod");
        flag_signals.singnal_number = 1;
        flag_signals.signal_pressed_eq = 1;
        flag_signals.signal_pressed_mod = 0;
    }
}

void MainWindow::on_pushButton_x_clicked() {
    if (flag_signals.signal_pressed_eq && flag_signals.signal_pressed_x) {
        if (ui->result_show->text() == "0") {
             ui->result_show->setText("x");
        } else {
             ui->result_show->setText(ui->result_show->text() + "x");
        }
        flag_signals.signal_pressed_x = 0;
        flag_signals.signal_pressed_x_true = 1;
        flag_signals.singnal_number = 1;
        flag_signals.signal_simle_line = 1;
        flag_signals.signal_pressed_ar_operators = 1;
        flag_signals.signal_pressed_sub = 1;
        flag_signals.signal_pressed_mod = 1;
    }
}

void MainWindow::on_pushButton_clear_del1_clicked() {
    QString result_show_new = ui->result_show->text();
    QByteArray temp_result_show = result_show_new.toLocal8Bit();
    if (result_show_new.data()[result_show_new.length() - 1] == ')') {
        flag_signals.signal_pressed_brecket++;
    }
    result_show_new.chop(1);
    if (result_show_new.data()[result_show_new.length() - 1] == '+' ||
               result_show_new.data()[result_show_new.length() - 1] == '-' ||
               result_show_new.data()[result_show_new.length() - 1] == '/' ||
               result_show_new.data()[result_show_new.length() - 1] == '*' ||
               result_show_new.data()[result_show_new.length() - 1] == '^' ||
               result_show_new.data()[result_show_new.length() - 1] == 't' ||
               result_show_new.data()[result_show_new.length() - 1] == 'd') {
        flag_signals.signal_pressed_ar_operators = 0;
        flag_signals.signal_stop = 0;
    } else if (result_show_new.data()[result_show_new.length() - 1] == 's' ||
               result_show_new.data()[result_show_new.length() - 1] == 'n' ||
               result_show_new.data()[result_show_new.length() - 1] == 'g') {
        flag_signals.signal_stop = 0;
    } else if (result_show_new.data()[result_show_new.length() - 1] == '.') {
        flag_signals.signal_stop = 0;
    }

    if (result_show_new.size() < 1) {
        result_show_new = "0";
        flag_signals.signal_pressed_eq = 1;
        flag_signals.signal_pressed_ac = 1;
        flag_signals.signal_pressed_ar_operators = 1;
        flag_signals.signal_simle_line = 1;
        flag_signals.singnal_number = 1;
        flag_signals.signal_pressed_brecket = 0;
        flag_signals.signal_simle_line = 0;
        flag_signals.signal_pressed_tr_operators = 1;
        flag_signals.signal_pressed_x = 1;
        flag_signals.signal_pressed_x_true = 0;
        flag_signals.signal_pressed_dot = 1;
    }

    ui->result_show->setText(result_show_new);
}

void MainWindow::on_pushButton_sub_clicked() {
    if (flag_signals.signal_pressed_sub && flag_signals.signal_pressed_eq && flag_signals.signal_simle_line) {
        ui->result_show->setText(ui->result_show->text() + "-");
        flag_signals.signal_pressed_ar_operators = 0;
        flag_signals.singnal_number = 1;
        flag_signals.signal_pressed_x = 1;
        flag_signals.signal_pressed_dot = 1;
        flag_signals.signal_pressed_sub = 0;
    }
}
