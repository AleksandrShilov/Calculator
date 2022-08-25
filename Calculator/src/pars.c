#include "pars.h"


/* проверка на наличие обеих скобок */
void validation_bracket(char symbol, int *flag_bracket) {
    if (symbol == '(') {
        (*flag_bracket)++;
    } else if (symbol == ')') {
        (*flag_bracket)--;
    }
}

/* проверка на наличие чисел до точки и после точки */
void validation_dot(char *symbol, int *flag_dot) {
    if (*symbol == 46) {
        symbol--;
        if (!(*symbol > 47 && *symbol < 58)) {
            *flag_dot = 1;
        }
        symbol++;
        symbol++;
        if (!(*symbol > 47 && *symbol < 58)) {
            *flag_dot = 1;
        }
    }
}

/* проверка на наличие чисел до оператора и после оператора */
void validation_operators(char *symbol, int *flag_operators, int flag_bracket) {
    if (*symbol == 43 || *symbol == 42 || *symbol == 45 || *symbol == 47 || *symbol == 94) {
        char exceptions[9] = {'c', 's', 't', 'a', 'l', 's', '^', 'x'};
        if (!flag_bracket) {
            symbol--;
            if (!(*symbol > 47 && *symbol < 58) && !(*symbol == ')')) {
                if (!(strchr(exceptions, *symbol))) {
                    *flag_operators = 1;
                } else if (*symbol == 0) {
                    *flag_operators = 1;
                }
            }
            symbol++;
            symbol++;
            if (!(*symbol > 47 && *symbol < 58) && !(*symbol == '(')) {
                if (!(strchr(exceptions, *symbol))) {
                    *flag_operators = 1;
                } else if (*symbol == 0) {
                    *flag_operators = 1;
                }
            }
        } else {
            symbol--;
            if (!(*symbol > 47 && *symbol < 58) && !(*symbol == '(' || *symbol == ')')) {
                if (!(strchr(exceptions, *symbol))) {
                    *flag_operators = 1;
                }
            }
            symbol++;
            symbol++;
            if (!(*symbol > 47 && *symbol < 58) && !(*symbol == '(' || *symbol == ')')) {
                if (!(strchr(exceptions, *symbol))) {
                    *flag_operators = 1;
                }
            }
        }
    }
}

/* 
проверка на корректность ввода тригонометрических функций
(указатель на указатель для того чтобы сразу проверить название функции и
незаходить снова если попалась буква)
*/
void validation_trigonometric(char **symbol, int *flag_trigonometric) {
    char exceptions[9] = {')', '(', '+', '-', '/', '*', '^', 'x'};
    if (**symbol == 'a' || **symbol == 'c' || **symbol == 'l' || **symbol == 's'
        || **symbol == 't' || **symbol == 'm') {
        if (**symbol == 'a') {
            (*symbol)++;
            if (**symbol == 'c' || **symbol == 's' || **symbol == 't') {
                (*symbol)++;
                if (**symbol == 'o' || **symbol == 'i' || **symbol == 'a') {
                    (*symbol)++;
                    if (!(**symbol == 's' || **symbol == 'n')) {
                        *flag_trigonometric = 1;
                    }
                } else {
                    *flag_trigonometric = 1;
                }
            } else {
                *flag_trigonometric = 1;
            }
        } else if (**symbol == 's') {
            (*symbol)++;
            if (**symbol == 'i') {
                (*symbol)++;
                if (!(**symbol == 'n')) {
                    *flag_trigonometric = 1;
                }
            } else if (**symbol == 'q') {
                (*symbol)++;
                if (**symbol == 'r') {
                    (*symbol)++;
                    if (!(**symbol == 't')) {
                        *flag_trigonometric = 1;
                    }
                } else {
                    *flag_trigonometric = 1;
                }
            } else {
                *flag_trigonometric = 1;
            }
        } else if (**symbol == 'c' || **symbol == 'l' || **symbol == 't') {
            (*symbol)++;
            if (**symbol == 'a' || **symbol == 'o') {
                (*symbol)++;
                if (!(**symbol == 'g' || **symbol == 'n' || **symbol == 's')) {
                    *flag_trigonometric = 1;
                }
            } else if (**symbol == 'n') {
                *flag_trigonometric = 0;
            } else {
                *flag_trigonometric = 1;
            }
        } else if (**symbol == 'm') {
            (*symbol)++;
            if (**symbol == 'o') {
                (*symbol)++;
                if (!(**symbol == 'd')) {
                    *flag_trigonometric = 1;
                }
            } else {
                *flag_trigonometric = 1;
            }
        } else {
            *flag_trigonometric = 1;
        }
    } else if ((**symbol > 47 && **symbol < 58) || strchr(exceptions, **symbol)) {
        *flag_trigonometric = 0;
    } else {
        *flag_trigonometric = 1;
    }
}

/* проверка на ноль */
void validation_zero(char *symbol, int *flag_zero) {
    if (*symbol == '0') {
        symbol--;
        if (*symbol == '/') {
            *flag_zero = 1;
        }
    }
}

/* проверка строки на корректный ввод */
bool validations(char *line) {
    bool result = true;
    int flag_bracket = 0;
    int flag_dot = 0;
    int flag_operators = 0;
    int flag_trigonometric = 0;
    int flag_zero = 0;

    while (*line && !flag_zero) {
        validation_bracket(*line, &flag_bracket);
        validation_dot(line, &flag_dot);
        validation_operators(line, &flag_operators, flag_bracket);
        validation_trigonometric(&line, &flag_trigonometric);
        validation_zero(line, &flag_zero);
        line++;
    }

    if (flag_bracket || flag_dot || flag_operators || flag_trigonometric || flag_zero) {
        result = false;
    }

    return result;
}

/* зануление массива */
void clear_array(char *arr, double *numeric_val, int *j) {
    *numeric_val = -1;
    *j = 0;
    for (int i = 0; i < size_arr + 1; i++) {
        arr[i] = 0;
    }
}

/* забираем цифры для преобразования их в числовое значение */
void parse_number(char const *line, int *flag_bracket_l, char *number_values, int *i) {
    if ((*line > 47 && *line < 58) || *line == 46) {
        *flag_bracket_l = 0;
        number_values[*i] = *line;
        (*i)++;
    }
}

void parse_x(char const *line, struct list **input_line) {
    if (*line == 'x') {
        stack_push(input_line, 0, 0, x);
    }
}

/* забираем арифметические операторы */
void parse_arithmetic(char const *line, struct list **input_line, double *numeric_val, char *number_values,
                      int *flag_bracket_l, int *i) {
    if ((*line > 39 && *line < 44) || *line == '-' || *line == '/' || *line == '^') {
        /* преобразование цифр в числовое значение и добавляение в стек */
        sscanf(number_values, "%lf", numeric_val);
        if (*numeric_val != -1) {
            stack_push(input_line, *numeric_val, 0, number);
            clear_array(number_values, numeric_val, i);
        }

        if (*line == '+') {
            stack_push(input_line, 0, 1, plus);
        } else if (*line == '-') {
            if (*flag_bracket_l) {
                stack_push(input_line, 0, 0, number);
                stack_push(input_line, 0, 1, minus);
            } else {
                stack_push(input_line, 0, 1, minus);
            }
        } else if (*line == '*') {
            stack_push(input_line, 0, 2, mult);
        } else if (*line == '/') {
            stack_push(input_line, 0, 2, division);
        } else if (*line == '^') {
            stack_push(input_line, 0, 3, degree);
        } else if (*line == '(') {
            stack_push(input_line, 0, 5, bracket_l);
            *flag_bracket_l = 1;
        } else if (*line == ')') {
            stack_push(input_line, 0, 5, bracket_r);
        }
    }
}

/* забираем тригонометрические функции */
void parse_trigonometric(char const *line, char *trigonometric_func, struct list **input_line,
                         double *numeric_val, char *number_values, int *i, int *k) {
    if (*line == 'a' || *line == 'c' || *line == 'd' || *line == 'g' || *line == 'i' ||
                (*line > 'k' && *line < 'p') || (*line > 'p' && *line < 'u')) {
        trigonometric_func[*k] = *line;
        (*k)++;
        if (strstr(trigonometric_func, "acos")) {
            stack_push(input_line, 0, 4, acs);
            memset(trigonometric_func, '?', *k);
            *k = 0;
        } else if (strstr(trigonometric_func, "cos")) {
            stack_push(input_line, 0, 4, cs);
            memset(trigonometric_func, '?', *k);
            *k = 0;
        } else if (strstr(trigonometric_func, "asin")) {
            stack_push(input_line, 0, 4, asn);
            memset(trigonometric_func, '?', *k);
            *k = 0;
        } else if (strstr(trigonometric_func, "atan")) {
            stack_push(input_line, 0, 4, atn);
            memset(trigonometric_func, '?', *k);
            *k = 0;
        } else if (strstr(trigonometric_func, "sin")) {
            stack_push(input_line, 0, 4, sn);
            memset(trigonometric_func, '?', *k);
            *k = 0;
        } else if (strstr(trigonometric_func, "tan")) {
            stack_push(input_line, 0, 4, tn);
            memset(trigonometric_func, '?', *k);
            *k = 0;
        } else if (strstr(trigonometric_func, "log")) {
            stack_push(input_line, 0, 4, l);
            memset(trigonometric_func, '?', *k);
            *k = 0;
        } else if (strstr(trigonometric_func, "sqrt")) {
            stack_push(input_line, 0, 4, sqt);
            memset(trigonometric_func, '?', *k);
            *k = 0;
        } else if (strstr(trigonometric_func, "ln")) {
            stack_push(input_line, 0, 4, lg);
            memset(trigonometric_func, '?', *k);
            *k = 0;
        } else if (strstr(trigonometric_func, "mod")) {
            sscanf(number_values, "%lf", numeric_val);
            if (*numeric_val != -1) {
                stack_push(input_line, *numeric_val, 0, number);
                clear_array(number_values, numeric_val, i);
            }
            stack_push(input_line, 0, 2, module);
            memset(trigonometric_func, '?', *k);
            *k = 0;
        }
    }
}

/* преобразование цифр в числовое значение */
void converting_digits(struct list **input_line, double *numeric_val, char *number_values, int *i) {
    sscanf(number_values, "%lf", numeric_val);
    if (*numeric_val != -1) {
        stack_push(input_line, *numeric_val, 0, number);
        clear_array(number_values, numeric_val, i);
    }
}

struct list *parse_line(char *line) {
    struct list *input_line = {0};
    if (validations(line)) {
        char trigonometric_func[size_arr] = {0};
        char number_values[size_arr] = {0};
        double numeric_val = -1;
        int flag_bracket_l = 0;
        int i = 0;
        int k = 0;

        while (*line) {
            parse_number(line, &flag_bracket_l, number_values, &i);
            parse_x(line, &input_line);
            parse_arithmetic(line, &input_line, &numeric_val, number_values, &flag_bracket_l, &i);
            parse_trigonometric(line, trigonometric_func, &input_line, &numeric_val,
                                number_values, &i, &k);
            line++;
        }

        converting_digits(&input_line, &numeric_val, number_values, &i);
        input_line = list_reverse(input_line);
    }
    return input_line;
}
