#ifndef SRC_CREDITCALC_H_
#define SRC_CREDITCALC_H_

#include <QDialog>

namespace Ui {
class creditCalc;
}

class creditCalc : public QDialog {
    Q_OBJECT

 public:
    explicit creditCalc(QWidget *parent = nullptr);
    ~creditCalc();

 private slots:
    void check_input_value_credit(double *amount_credit, double *time_credit, double *percent_credit);

    void record_differ_table(double *accrued_inter, double amount_credit, double time_credit,
                             double percent_credit);

    void record_annuities(double accrued_inter, double amount_credit, double time_credit,
                          double percent_credit, double all_credit, double month_pay);

    void on_pushButton_credit_go_clicked();

    void on_pushButton_credit_clear_clicked();

 private:
    Ui::creditCalc *ui;
};

#endif  // SRC_CREDITCALC_H_
