#ifndef SRC_GRAPH_H_
#define SRC_GRAPH_H_

#include <QDialog>
#include <QVector>

namespace Ui {
class Graph;
}

class Graph : public QDialog {
    Q_OBJECT

 public:
    explicit Graph(QWidget *parent = nullptr, QString function = "");
    ~Graph();

 private slots:
    void on_pushButton_clicked();

 private:
    Ui::Graph *ui;
    double xBegin, xEnd, h, X, Y;
    QString function;

    QVector<double> x, y;
};

#endif  // SRC_GRAPH_H_
