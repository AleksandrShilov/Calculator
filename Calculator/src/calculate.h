#ifndef SRC_CALCULATE_H_
#define SRC_CALCULATE_H_

#include <complex.h>
#include <math.h>
#include "rpn.h"

double calc(char *line, double value_x);
void credit_calculate(double amount_credit, double percent_credit, double time_credit,
                      double *month_pay, double *accrued_inter, double *all_credit);


#endif  // SRC_CALCULATE_H_
