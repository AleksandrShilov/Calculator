#ifndef SRC_INPUT_X_H_
#define SRC_INPUT_X_H_

#include <QDialog>

namespace Ui {
class input_x;
}

class input_x : public QDialog {
    Q_OBJECT

 public:
    explicit input_x(QWidget *parent = nullptr);
    ~input_x();

 public slots:

    double on_pushButton_ok_clicked();

 private:
    Ui::input_x *ui;
};

#endif  // SRC_INPUT_X_H_
