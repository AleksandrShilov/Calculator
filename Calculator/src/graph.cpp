#include "graph.h"
#include "ui_graph.h"

extern "C" {
    #include "calculate.h"
}

Graph::Graph(QWidget *parent, QString function) :
    QDialog(parent),
    ui(new Ui::Graph) {
    ui->setupUi(this);
    this->function = function;
}

Graph::~Graph() {
    delete ui;
}

void Graph::on_pushButton_clicked() {
    QString x_input = ui->line_x->text();
    QString y_input = ui->line_y->text();
    int err_flag = 0;
    int x_val = 0;
    int y_val = 0;

    if (x_input.size() > 0 && y_input.size() > 0) {
        for (int i = 0; i < x_input.length() - 1; i++) {
            if (x_input.data()[i] < '0' || x_input.data()[i] > '9') {
                err_flag = 1;
                break;
            }
        }

        for (int i = 0; i < x_input.length() - 1; i++) {
            if (y_input.data()[i] < '0' || y_input.data()[i] > '9') {
                err_flag = 1;
                break;
            }
        }

        if (err_flag == 0) {
            x_val = x_input.toInt();
            y_val = y_input.toInt();
        } else {
            ui->line_x->setText("");
            ui->line_y->setText("");
        }


        ui->widget->xAxis->setRange(-1 * x_val, x_val);
        ui->widget->yAxis->setRange(-1 * y_val, y_val);

        char *str;
        h = 0.0001;

        for (X = -x_val; X <= x_val; X += h) {
            x.push_back(X);
            QByteArray arr = this->function.toLocal8Bit();
            str = arr.data();

            Y = calc(str, X);

            if (Y == y_val) {
                Y = -y_val;
            } else if (Y == -y_val) {
                Y = y_val;
            }

            y.push_back(Y);
        }

       ui->widget->addGraph();
       ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
       ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 2));
       ui->widget->graph(0)->addData(x, y);
       ui->widget->replot();
    }
    ui->line_x->setText("");
    ui->line_y->setText("");
}
