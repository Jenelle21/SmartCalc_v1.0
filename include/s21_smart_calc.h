#ifndef INCLUDE_S21_SMART_CALC_H_
#define INCLUDE_S21_SMART_CALC_H_

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define STACK_SIZE 255
#define STACK_UNDERFLOW -101
#define ANN 1
#define DIFF 2
#define ERROR 0
#define SUCCESS 1

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Stack_tag {
  char data[STACK_SIZE][256];
  size_t size;
} Stack_t;

int controller(char *infix, double *res);

void push(Stack_t *stack, char *value);

char *pop(Stack_t *stack);

const char *peek(const Stack_t *stack);

void printStackValue(const char *value);

void printStack(const Stack_t *stack);

int validate(char *infix);

char *parserToRPN(char *infix, Stack_t *postfix, int *code);

double calculation(Stack_t *rpn, int *code);

int priority(const char *str);

double s21_add(double a, double b);

double s21_sub(double a, double b);

double s21_mul(double a, double b);

double s21_div(double a, double b);

#ifdef __cplusplus
}
#endif

#endif  // INCLUDE_S21_SMART_CALC_H_
