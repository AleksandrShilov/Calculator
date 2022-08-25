#ifndef SRC_DEPOSITCALC_H_
#define SRC_DEPOSITCALC_H_

#include <QDialog>

namespace Ui {
class depositCalc;
}

class depositCalc : public QDialog {
    Q_OBJECT

 public:
    explicit depositCalc(QWidget *parent = nullptr);
    ~depositCalc();

 private slots:
    void check_input_value(double *amount_deposit, double *time_deposit, double *percent_deposit);

    void calculate_time_deposit(int *all_day, int *converter_array, double *time_deposit);

    void calculate_amount_deposit_and_percent(double *all_deposit, double *time_deposit,
    double amount_deposit, double percent_deposit, double *accrued_inter, int all_day);

    void writing_table(double time_deposit, double accrued_inter, int all_day, int *converter_array,
                       double amount_deposit);

    void on_pushButton_go_clicked();

    void on_pushButton_add_refill_clicked();

    void on_pushButton_add_remove_clicked();

    void on_pushButton_clear_clicked();

 private:
    Ui::depositCalc *ui;
    double add_amount = 0;
};

#endif  // SRC_DEPOSITCALC_H_
