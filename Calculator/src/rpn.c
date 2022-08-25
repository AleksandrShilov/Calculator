#include "rpn.h"


struct list *distribution_values(char *line) {
    struct list *input_line = parse_line(line);
    struct list *ready_line = {0};
    struct list *support_line = {0};
    short flag_bracket_l = 0;
    while (input_line) {
        if (input_line->type == number) {
            stack_push(&ready_line, input_line->value, input_line->priority, input_line->type);
        }

        if (input_line->type == x) {
            stack_push(&ready_line, input_line->value, input_line->priority, input_line->type);
        } else if (input_line->type == bracket_l) {
            flag_bracket_l++;
            stack_push(&support_line, input_line->value, input_line->priority, input_line->type);
        } else if (flag_bracket_l && input_line->type != bracket_r) {
            if (support_line && input_line->type != number) {
                if (input_line->priority > support_line->priority) {
                    stack_push(&support_line, input_line->value, input_line->priority, input_line->type);
                } else {
                    while (support_line->type != bracket_l &&
                    support_line->priority >= input_line->priority) {
                        stack_push(&ready_line, support_line->value, support_line->priority,
                        support_line->type);
                        stack_pop(&support_line);
                    }
                    stack_push(&support_line, input_line->value, input_line->priority, input_line->type);
                }
            } else if (support_line == 0 && input_line->type != number) {
                stack_push(&support_line, input_line->value, input_line->priority, input_line->type);
            }
        } else if (input_line->type == bracket_r) {
            while (support_line->priority < 5) {
                if (support_line->type != bracket_l) {
                    stack_push(&ready_line, support_line->value, support_line->priority, support_line->type);
                }
                stack_pop(&support_line);
            }
            stack_pop(&support_line);
            flag_bracket_l--;
        } else {
            if (support_line && input_line->type != number && !flag_bracket_l) {
                if (input_line->priority > support_line->priority) {
                    stack_push(&support_line, input_line->value, input_line->priority, input_line->type);
                } else {
                    while (support_line && (support_line->priority >= input_line->priority)) {
                        stack_push(&ready_line, support_line->value, support_line->priority,
                        support_line->type);
                        stack_pop(&support_line);
                    }
                    stack_push(&support_line, input_line->value, input_line->priority, input_line->type);
                }
            } else if (support_line == 0 && input_line->type != number && !flag_bracket_l) {
                stack_push(&support_line, input_line->value, input_line->priority, input_line->type);
            }
        }
        stack_pop(&input_line);
    }
    while (support_line) {
        if (support_line->type != bracket_l) {
            stack_push(&ready_line, support_line->value, support_line->priority, support_line->type);
        }
        stack_pop(&support_line);
    }
    list_destroy(input_line);
    return ready_line;
}
