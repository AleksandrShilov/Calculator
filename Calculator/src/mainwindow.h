#ifndef SRC_MAINWINDOW_H_
#define SRC_MAINWINDOW_H_

#include <QMainWindow>
#include <iostream>
#include <QVector>

extern "C" {
    #include "calculate.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

 public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

 private:
    Ui::MainWindow *ui;

    struct Flags {
        int signal_simle_line = 0;
        int singnal_number = 1;
        int signal_pressed_eq = 1;
        int signal_pressed_ac = 1;
        int signal_pressed_x = 1;
        int signal_pressed_x_true = 0;
        int signal_pressed_ar_operators = 1;
        int signal_pressed_tr_operators = 1;
        int signal_pressed_brecket = 0;
        int signal_pressed_dot = 1;
        int signal_pressed_mod = 1;
        int signal_pressed_sub = 1;
        int signal_stop = 1;
    } flag_signals;

 private slots:
    void digits_numbers();
    void on_pushButton_dot_clicked();
    void operations();
    void on_pushButton_eq_clicked();
    void arithmetic_operations();
    void trigonometric_operations();
    void on_pushButton_clear_clicked();
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_pushButton_graph_clicked();
    void on_pushButton_credit_clicked();
    void on_pushButton_deposit_clicked();
    void on_pushButton_bracket_l_clicked();
    void on_pushButton_bracket_r_clicked();
    void on_pushButton_sqrt_clicked();
    void on_pushButton_mod_clicked();
    void on_pushButton_x_clicked();
    void on_pushButton_clear_del1_clicked();
    void on_pushButton_sub_clicked();
};

#endif  // SRC_MAINWINDOW_H_
