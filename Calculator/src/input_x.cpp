#include "input_x.h"
#include "ui_input_x.h"

input_x::input_x(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::input_x) {
    ui->setupUi(this);
}

input_x::~input_x() {
    delete ui;
}

double input_x::on_pushButton_ok_clicked() {
      QString temp_str_x = ui->lineEdit_number_input_x->text();
      double num_input_x = 0;
      int flag_err = 0;
      int flag_dot = 0;

      for (int i = 0; i < temp_str_x.length() - 1; i++) {
          if ((temp_str_x.data()[i] >= '0' && temp_str_x.data()[i] <= '9') || temp_str_x.data()[i] == '.') {
            if (temp_str_x.data()[i] == '.') {
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
          num_input_x = temp_str_x.toDouble();
          close();
      } else {
          ui->lineEdit_number_input_x->setText("");
      }
      return num_input_x;
}
