#include "calculate.h"


double calc(char *line, double value_x) {
    struct list *ready_line = distribution_values(line);
    struct list *result = {0};
    double temp;
    ready_line = list_reverse(ready_line);

    while (ready_line) {
        if (ready_line->type == number) {
            stack_push(&result, ready_line->value, ready_line->priority, ready_line->type);
            stack_pop(&ready_line);
        } else if (ready_line->type == x) {
            stack_push(&result, value_x, 0, number);
            stack_pop(&ready_line);
        } else {
            if (ready_line->type == plus) {
                temp = stack_pop(&result) + stack_pop(&result);
                stack_push(&result, temp, 1, number);
                stack_pop(&ready_line);
            } else if (ready_line->type == minus) {
                double temp2 = stack_pop(&result);
                temp = stack_pop(&result) - temp2;
                stack_push(&result, temp, 1, number);
                stack_pop(&ready_line);
            } else if (ready_line->type == division) {
                double temp2 = stack_pop(&result);
                temp = stack_pop(&result) / temp2;
                stack_push(&result, temp, 1, number);
                stack_pop(&ready_line);
            } else if (ready_line->type == mult) {
                temp = stack_pop(&result) * stack_pop(&result);
                stack_push(&result, temp, 1, number);
                stack_pop(&ready_line);
            } else if (ready_line->type == degree) {
                temp = pow(stack_pop(&result), stack_pop(&result));
                stack_push(&result, temp, 1, number);
                stack_pop(&ready_line);
            } else if (ready_line->type == cs) {
                temp = cos(stack_pop(&result));
                stack_push(&result, temp, 1, number);
                stack_pop(&ready_line);
            } else if (ready_line->type == sn) {
                temp = sin(stack_pop(&result));
                stack_push(&result, temp, 1, number);
                stack_pop(&ready_line);
            } else if (ready_line->type == tn) {
                temp = tan(stack_pop(&result));
                stack_push(&result, temp, 1, number);
                stack_pop(&ready_line);
            } else if (ready_line->type == asn) {
                temp = asin(stack_pop(&result));
                stack_push(&result, temp, 1, number);
                stack_pop(&ready_line);
            } else if (ready_line->type == acs) {
                temp = acos(stack_pop(&result));
                stack_push(&result, temp, 1, number);
                stack_pop(&ready_line);
            } else if (ready_line->type == atn) {
                temp = atan(stack_pop(&result));
                stack_push(&result, temp, 1, number);
                stack_pop(&ready_line);
            } else if (ready_line->type == sqt) {
                temp = sqrt(stack_pop(&result));
                stack_push(&result, temp, 1, number);
                stack_pop(&ready_line);
            } else if (ready_line->type == lg) {
                temp = log(stack_pop(&result));
                stack_push(&result, temp, 1, number);
                stack_pop(&ready_line);
            } else if (ready_line->type == l) {
                temp = log10(stack_pop(&result));
                stack_push(&result, temp, 1, number);
                stack_pop(&ready_line);
            } else if (ready_line->type == module) {
                double temp2 = stack_pop(&result);
                temp = fmod(stack_pop(&result), temp2);
                stack_push(&result, temp, 1, number);
                stack_pop(&ready_line);
            }
        }
    }

    double res = 0;
    if (result) {
        res = result->value;
    }
    list_destroy(result);
    return res;
}

void credit_calculate(double amount_credit, double percent_credit, double time_credit,
                      double *month_pay, double *accrued_inter, double *all_credit) {
    double month_loan_rate = percent_credit / 12 / 100;
    double annuity_ratio = (month_loan_rate * pow((1 + month_loan_rate), time_credit))
                            / (pow((1 + month_loan_rate), time_credit) - 1);
    *month_pay = annuity_ratio * amount_credit;
    *all_credit = *month_pay * time_credit;
    *accrued_inter = *all_credit - amount_credit;
}
