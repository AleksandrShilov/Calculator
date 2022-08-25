#include "depositcalc.h"
#include "ui_depositcalc.h"
#include <math.h>

depositCalc::depositCalc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::depositCalc) {
    ui->setupUi(this);
    ui->lineEdit_label_deposit->setFocus();
    this->resize(640, 600);
    this->setMinimumHeight(600);
    this->setMinimumWidth(640);
    this->setMaximumWidth(640);
    this->setMaximumHeight(600);
}

depositCalc::~depositCalc() {
    delete ui;
}

void depositCalc::check_input_value(double *amount_deposit, double *time_deposit, double *percent_deposit) {
    QString temp_amount = ui->lineEdit_label_deposit->text();
    QString temp_time = ui->lineEdit_term_placement->text();
    QString temp_percent = ui->lineEdit_percent->text();

    int flag_err = 0;
    int flag_dot = 0;

    for (int i = 0; i < temp_amount.length() - 1; i++) {
        if (temp_amount.data()[i] < '0' || temp_amount.data()[i] > '9') {
            flag_err = 1;
            break;
        }
    }

    for (int i = 0; i < temp_time.length() - 1; i++) {
        if (temp_time.data()[i] < '0' || temp_time.data()[i] > '9') {
            flag_err = 1;
            break;
        }
    }

    for (int i = 0; i < temp_percent.length() - 1; i++) {
        if ((temp_percent.data()[i] >= '0' || temp_percent.data()[i] <= '9') ||
            temp_percent.data()[i] <= '.') {
            if (temp_percent.data()[i] == '.') {
                flag_dot++;
            }

            if (flag_dot > 1) {
                flag_err = 1;
                break;
            }
        } else {
            flag_err = 1;
            break;
        }
    }


    if (!flag_err) {
        *amount_deposit = temp_amount.toDouble();
        *time_deposit = temp_time.toDouble();
        *percent_deposit = temp_percent.toDouble();
    }
}

void depositCalc::calculate_time_deposit(int *all_day, int *converter_array, double *time_deposit) {
    if (ui->comboBox_date_form->currentText() == "месяцев") {
        int num_month = ui->dateEdit->date().month();
        int score_sum = 0;
        int add_mouth = 0;
        score_sum = round(*time_deposit / 12);
        add_mouth = fmod(*time_deposit, 12.0);

        for (int i = 0; i < (score_sum * 12); i++) {
            if (num_month >= 13) {
                num_month = 1;
            }
            *all_day += converter_array[num_month];
            num_month++;
        }

        for (int i = 0; i < add_mouth; i++) {
            if (num_month >= 13) {
                num_month = 1;
            }
            *all_day += converter_array[num_month];
            num_month++;
        }
    } else if (ui->comboBox_date_form->currentText() == "дней") {
        *all_day = *time_deposit;
        *time_deposit /= 30.0;
    }
}

void depositCalc::calculate_amount_deposit_and_percent(double *all_deposit, double *time_deposit,
            double amount_deposit, double percent_deposit, double *accrued_inter, int all_day) {
    if (ui->checkBox_capital_interest->isChecked()) {
        if (ui->comboBox_frequency_payments->currentText() == "Раз в месяц") {
            *all_deposit = amount_deposit * pow((1 + (percent_deposit / 100) / 12), *time_deposit);
            *accrued_inter = *all_deposit - amount_deposit;
            *time_deposit = ceil(*time_deposit);
        } else if (ui->comboBox_frequency_payments->currentText() == "Раз в день") {
            *all_deposit = amount_deposit * pow((1 + (percent_deposit / 100) / 365), all_day);
            *accrued_inter = *all_deposit - amount_deposit;
            *time_deposit = all_day;
        } else if (ui->comboBox_frequency_payments->currentText() == "Раз в квартал") {
            *all_deposit = amount_deposit * pow((1 + (percent_deposit / 100) / 4), *time_deposit / 3);
            *accrued_inter = *all_deposit - amount_deposit;
            *time_deposit = ceil(*time_deposit / 3);
        }
    } else {
        *accrued_inter = (amount_deposit * percent_deposit * all_day / 365) / 100;
        *all_deposit = *accrued_inter + amount_deposit;
        *time_deposit = ceil(*time_deposit);
    }
}

void depositCalc::writing_table(double time_deposit, double accrued_inter, int all_day, int *converter_array,
                                double amount_deposit) {
    double percent_day = accrued_inter / all_day;
    double percent_temp = accrued_inter / 12;
    double percent_mouth = 0;
    double remains = 0;

    ui->tableWidget->setRowCount(time_deposit + 1);
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(
        QStringList() << "Начислено процентов" << "Вклад пополнен" << "Остаток на вкладе");
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QTableWidgetItem *im1 = new QTableWidgetItem(tr("%1").arg(percent_mouth, 0, 'f', 2));
    ui->tableWidget->setItem(0, 0, im1);
    QTableWidgetItem *im2 = new QTableWidgetItem(tr("%1").arg(remains, 0, 'f', 2));
    ui->tableWidget->setItem(0, 1, im2);
    QTableWidgetItem *im3 = new QTableWidgetItem(tr("%1").arg(amount_deposit, 0, 'f', 2));
    ui->tableWidget->setItem(0, 2, im3);

    for (int i = 1, j = 1, k = 0; i < time_deposit + 1; i++, j++) {
        if (j >= 13) {
            j = 1;
        }
        if (ui->comboBox_date_form->currentText() == "дней") {
            percent_mouth = percent_temp;
        } else {
            percent_mouth = converter_array[j] * percent_day;
        }

        if (ui->checkBox_capital_interest->isChecked()) {
            remains = percent_mouth;
            amount_deposit += remains;
        }
        QTableWidgetItem *item1 = new QTableWidgetItem(tr("%1").arg(percent_mouth, 0, 'f', 2));
        ui->tableWidget->setItem(i, k, item1);
        k++;
        QTableWidgetItem *item2 = new QTableWidgetItem(tr("%1").arg(remains, 0, 'f', 2));
        ui->tableWidget->setItem(i, k, item2);
        k++;
        QTableWidgetItem *item3 = new QTableWidgetItem(tr("%1").arg(amount_deposit, 0, 'f', 2));
        ui->tableWidget->setItem(i, k, item3);
        k = 0;
    }
}

void depositCalc::on_pushButton_go_clicked() {
    this->setMaximumWidth(1204);
    this->setMinimumWidth(1204);
    this->resize(1204, 600);
    QString temp_amount = ui->lineEdit_label_deposit->text();
    QString temp_time = ui->lineEdit_term_placement->text();
    QString temp_percent = ui->lineEdit_percent->text();

    int converter_array[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int all_day = 0;
    double amount_deposit = 0;
    double time_deposit = 0;
    double percent_deposit = 0;
    double accrued_inter = 0;
    double all_deposit = 0;
    double tax = 0;
    double no_tax = 1000000 * 0.08;

    if (temp_amount.length() > 0 && temp_time.length() > 0 &&
            temp_percent.length() > 0) {
        check_input_value(&amount_deposit, &time_deposit, &percent_deposit);
        amount_deposit += add_amount;

        calculate_time_deposit(&all_day, converter_array, &time_deposit);
        calculate_amount_deposit_and_percent(&all_deposit, &time_deposit,
                                             amount_deposit, percent_deposit,
                                             &accrued_inter, all_day);

        writing_table(time_deposit, accrued_inter, all_day, converter_array, amount_deposit);

        if (accrued_inter > no_tax) {
            tax = accrued_inter * 0.13;
        }

        QString temp_accrued_inter = QString::number(accrued_inter, 'f', 2);
        QString temp_all_deposit = QString::number(all_deposit, 'f', 2);
        QString temp_tax = QString::number(tax, 'f', 2);
        ui->lineEdit_accrued_interest->setText(temp_accrued_inter);
        ui->lineEdit_amount_end->setText(temp_all_deposit);
        ui->lineEdit_tax->setText(temp_tax);
    }
}

void depositCalc::on_pushButton_add_refill_clicked() {
    QString temp_line_deposits =  ui->lineEdit_deposits->text();
    double value_add = 0;
    int flag_err = 0;

    if (temp_line_deposits.length() > 0) {
        for (int i = 0; i < temp_line_deposits.length() - 1; i++) {
            if (temp_line_deposits.data()[i] < '0' || temp_line_deposits.data()[i] > '9') {
                flag_err = 1;
                break;
            }
        }

        if (!flag_err) {
            value_add = temp_line_deposits.toDouble();
        }
        add_amount += value_add;
    }
    ui->lineEdit_deposits->setText("");
}

void depositCalc::on_pushButton_add_remove_clicked() {
    QString temp_line_withdrawals =  ui->lineEdit_partial_withdrawals->text();
    double value_add = 0;
    int flag_err = 0;

    if (temp_line_withdrawals.length() > 0) {
        for (int i = 0; i < temp_line_withdrawals.length() - 1; i++) {
            if (temp_line_withdrawals.data()[i] < '0' || temp_line_withdrawals.data()[i] > '9') {
                flag_err = 1;
                break;
            }
        }

        if (!flag_err) {
            value_add = temp_line_withdrawals.toDouble();
        }
        add_amount -= value_add;
    }
    ui->lineEdit_partial_withdrawals->setText("");
}

void depositCalc::on_pushButton_clear_clicked() {
    ui->lineEdit_label_deposit->setText("");
    ui->lineEdit_term_placement->setText("");
    ui->lineEdit_percent->setText("");
    ui->lineEdit_accrued_interest->setText("");
    ui->lineEdit_tax->setText("");
    ui->lineEdit_amount_end->setText("");
    ui->checkBox_capital_interest->setChecked(false);
    this->setMaximumWidth(640);
    this->setMinimumWidth(640);
    this->resize(640, 600);
}
