#ifndef SRC_STACK_H_
#define SRC_STACK_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>


struct maybe_int64 {
  int64_t value;
  bool valid;
};

/* приоритет сущности */
enum value_type {
    number, x, plus, minus, division, mult,
    module, degree, sn, cs, tn, ctn, asn, acs,
    atn, sqt, lg, l, bracket_l, bracket_r,
};

/* стек */
struct list {
  double value;
  int priority;
  int type;
  struct list* next;
};

/* создать стек */
struct list* node_create();

/* добавить элемент в стек (новые элементы добавляются в начало списка) */
void stack_push(struct list** old, double value, int priority_val, int type_val);

/* размер стека */
size_t list_length(const struct list* s);

/* удалить весь стек */
void list_destroy(struct list* list);

/* последний элеменент в стеке */
struct list* list_last(struct list * list);

/* добавить элемент в конец стека */
void list_add_back(struct list** old, double value, int priority_val, int type_val);

/* получить опреденный элемент по индексу */
struct maybe_int64 list_at(const struct list* list, size_t idx);

/* перевернутая копия стека */
struct list* list_reverse(const struct list* list);

/* считывает число из консоли и проверяет его */
struct maybe_int64 maybe_read_int64();

/* заполняет стек из консоли */
struct list* list_read();

/* вынуть значение с вершины стека */
double stack_pop(struct list** old);

/* посмотреть значение с вершины стека */
double stack_peek(struct list** old);

#endif  // SRC_STACK_H_
