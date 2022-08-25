#include "stack.h"

/* создать стек */
struct list* node_create() {
    struct list* list = malloc(sizeof(struct list));
    if (list) {
        list->value = -1;
        list->priority = -1;
        list->type = -1;
        list->next  = NULL;
    }
    return list;
}

/* добавить элемент в стек (новые элементы добавляются в начало списка) */
void stack_push(struct list** old, double value, int priority_val, int type_val) {
    if (old) {
        struct list* list2 = node_create(value);
        list2->value = value;
        list2->priority = priority_val;
        list2->type = type_val;
        list2->next = (*old);
        (*old) = list2;
    }
}

/* удалить весь стек */
void list_destroy(struct list* list) {
    if (list) {
        while (list) {
            struct list *tmp = list->next;
            free(list);
            list = tmp;
        }
    }
}

/* перевернутая копия стека */
struct list* list_reverse(const struct list* list) {
    struct list* list_revers = {0};
    if (list) {
        struct list* tmp_list = (struct list*) list;
        while (tmp_list) {
            stack_push(&list_revers, tmp_list->value, tmp_list->priority, tmp_list->type);
            stack_pop(&tmp_list);
        }
    }
    return list_revers;
}

/* вынуть значение с вершины стека */
double stack_pop(struct list** old) {
    double result = 0;
    if (old) {
        result = (*old)->value;
        struct list *tmp = (*old)->next;
        free(*old);
        (*old) = tmp;
    }
    return result;
}
