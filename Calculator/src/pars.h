#ifndef SRC_PARS_H_
#define SRC_PARS_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#define size_arr 255

/* проверка на наличие обеих скобок */
void validation_bracket(char symbol, int *flag_bracket);

/* проверка на наличие чисел до точки и после точки */
void validation_dot(char *symbol, int *flag_dot);

/* проверка на наличие чисел до оператора и после оператора */
void validation_operators(char *symbol, int *flag_operators, int flag_bracket);

/* проверка строки на корректный ввод */
bool validations(char *line);

/* проверка на корректность ввода тригонометрических функций */
void validation_trigonometric(char **symbol, int *flag_trigonometric);

/* проверка на ноль */
void validation_zero(char *symbol, int *flag_zero);

struct list *parse_line(char *line);

#endif  // SRC_PARS_H_
