#include "creditcalc.h"
#include "ui_creditcalc.h"

extern "C" {
    #include "calculate.h"
}

creditCalc::creditCalc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::creditCalc) {
    ui->setupUi(this);
    ui->radioButton__type_1->setChecked(true);
    this->setMinimumHeight(450);
    this->setMinimumWidth(529);
    this->setMaximumWidth(529);
    this->setMaximumHeight(450);
}

creditCalc::~creditCalc() {
    delete ui;
}

void creditCalc::check_input_value_credit(double *amount_credit, double *time_credit,
                                            double *percent_credit) {
    QString temp_amount = ui->lineEdit_loan_amount->text();
    QString temp_time = ui->lineEdit_loan_term->text();
    QString temp_percent = ui->lineEdit_rate_credit->text();

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
            (temp_percent.data()[i] == ".")) {
            if (temp_percent.data()[i] == ".") {
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
        *amount_credit = temp_amount.toDouble();
        *time_credit = temp_time.toDouble();
        *percent_credit = temp_percent.toDouble();
    }
}

void creditCalc::record_differ_table(double *accrued_inter, double amount_credit, double time_credit,
                                     double percent_credit) {
    this->setMinimumWidth(990);
    this->setMaximumWidth(990);
    this->resize(990, 450);
    *accrued_inter = amount_credit;
    double month_pay = amount_credit / time_credit;
    double month_pay_percent = 0;
    double month_percent = 0;
    double all_pay = 0;
    int i = 0;
    int j = 0;

    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(time_credit);
    ui->tableWidget->setHorizontalHeaderLabels(
        QStringList() << "Остаток" << "Проценты" << "Погашено" << "Платеж");

    while (amount_credit > 0) {
        month_percent = amount_credit * (percent_credit / 100) * 31 / 365;
        amount_credit -= month_pay;
        month_pay_percent = month_pay + month_percent;
        all_pay += month_pay_percent;
        QTableWidgetItem *item = new QTableWidgetItem(tr("%1").arg(amount_credit, 0, 'f', 2));
        ui->tableWidget->setItem(i, j, item);
        j++;
        QTableWidgetItem *item2 = new QTableWidgetItem(tr("%1").arg(month_percent, 0, 'f', 2));
        ui->tableWidget->setItem(i, j, item2);
        j++;
        QTableWidgetItem *item3 = new QTableWidgetItem(tr("%1").arg(all_pay, 0, 'f', 2));
        ui->tableWidget->setItem(i, j, item3);
        j++;
        QTableWidgetItem *item4 = new QTableWidgetItem(tr("%1").arg(month_pay_percent, 0, 'f', 2));
        ui->tableWidget->setItem(i, j, item4);
        i++;
        j = 0;
    }

    *accrued_inter = all_pay - *accrued_inter;
    QString temp_month_pay = QString::number(month_pay, 'f', 2);
    QString temp_accrued_inter = QString::number(*accrued_inter, 'f', 2);
    QString temp_all_pay = QString::number(all_pay, 'f', 2);

    ui->month_payment->setText(temp_month_pay);
    ui->accrued_interest->setText(temp_accrued_inter);
    ui->all->setText(temp_all_pay);
}

void creditCalc::record_annuities(double accrued_inter, double amount_credit, double time_credit,
                                  double percent_credit, double all_credit, double month_pay) {
    this->resize(529, 450);
    credit_calculate(amount_credit, percent_credit, time_credit,
                     &month_pay, &accrued_inter, &all_credit);

    QString temp_month_pay = QString::number(month_pay, 'f', 2);
    QString temp_accrued_inter = QString::number(accrued_inter, 'f', 2);
    QString temp_all_credit = QString::number(all_credit, 'f', 2);

    ui->month_payment->setText(temp_month_pay);
    ui->accrued_interest->setText(temp_accrued_inter);
    ui->all->setText(temp_all_credit);
}

void creditCalc::on_pushButton_credit_go_clicked() {
    QString temp_amount = ui->lineEdit_loan_amount->text();
    QString temp_time = ui->lineEdit_loan_term->text();
    QString temp_percent = ui->lineEdit_rate_credit->text();

    double amount_credit = 0;
    double time_credit = 0;
    double percent_credit = 0;

    double month_pay = 0;
    double accrued_inter = 0;
    double all_credit = 0;

    if (temp_amount.length() > 0 && ui->label_loan_term->text().length() > 0 &&
            ui->lineEdit_rate_credit->text().length() > 0) {
        check_input_value_credit(&amount_credit, &time_credit, &percent_credit);

        if (ui->radioButton__type_2->isChecked()) {
            record_differ_table(&accrued_inter, amount_credit, time_credit, percent_credit);
        } else {
            this->setMinimumHeight(450);
            this->setMinimumWidth(529);
            this->setMaximumWidth(529);
            this->setMaximumHeight(450);
            record_annuities(accrued_inter, amount_credit, time_credit, percent_credit,
                             all_credit, month_pay);
        }
    }
}

void creditCalc::on_pushButton_credit_clear_clicked() {
    ui->lineEdit_loan_amount->setText("");
    ui->lineEdit_loan_term->setText("");
    ui->lineEdit_rate_credit->setText("");
    ui->accrued_interest->setText("");
    ui->month_payment->setText("");
    ui->all->setText("");
    this->setMinimumHeight(450);
    this->setMinimumWidth(529);
    this->setMaximumWidth(529);
    this->setMaximumHeight(450);
    this->resize(529, 450);
}
