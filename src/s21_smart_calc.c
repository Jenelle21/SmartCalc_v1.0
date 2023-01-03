#include "../include/s21_smart_calc.h"

int controller(char *infix, double *res) {
  Stack_t postfix, rpn;
  postfix.size = 0;
  rpn.size = 0;
  int flag = validate(infix);
  if (flag == SUCCESS) {
    parserToRPN(infix, &postfix, &flag);
  }
  if (flag == SUCCESS) {
    while (postfix.size) push(&rpn, pop(&postfix));
    *res = calculation(&rpn, &flag);
  }
  return flag;
}

int validate(char *infix) {
  int code = SUCCESS;
  int check = 0;
  for (size_t i = 0; i < strlen(infix); i++) {
    if (infix[i] == '(')
      check++;
    else if (infix[i] == ')')
      check--;
    if (check < 0) {
      code = ERROR;
      break;
    }
    if (i == strlen(infix) - 1 && check != 0) code = ERROR;
  }
  return code;
}

char *parserToRPN(char *infix, Stack_t *postfix, int *code) {
  char operations[15][7] = {"+\0",    "-\0",    "*\0",    "/\0",   "^\0",
                            "mod\0",  "sin\0",  "cos\0",  "tan\0", "acos\0",
                            "asin\0", "atan\0", "sqrt\0", "ln\0",  "log\0"};
  char digits[15] = "1234567890.eE\0";
  Stack_t stack;
  stack.size = 0;
  char *cursor;
  cursor = (char *)infix;
  int flag = 1;
  while (*cursor) {
    char support[256] = "\0";
    if (*cursor == ' ') {
      cursor++;
    } else if (*cursor == '(') {
      cursor++;
      cursor = parserToRPN(cursor, postfix, code);
      flag = 0;
    } else if (*cursor == ')') {
      cursor++;
      break;
    } else if (strspn(cursor, digits) != 0) {
      if (flag == 0) {
        *code = ERROR;
        break;
      }
      strncpy(support, cursor, strspn(cursor, digits));
      push(postfix, support);
      cursor += strspn(cursor, digits);
      flag = 0;
    } else if (*cursor == '-' && flag == 1) {
      char unar[3] = "~\0";
      push(&stack, unar);
      cursor++;
    } else if (*cursor == '+' && flag == 1) {
      cursor++;
    } else {
      *code = ERROR;
      for (int j = 0; j < 15; j++) {
        if (strstr(cursor, operations[j]) == cursor) {
          while (stack.size &&
                 priority(peek(&stack)) >= priority(operations[j])) {
            if (!strcmp(peek(&stack), "^") && !strcmp(operations[j], "^"))
              break;
            else
              push(postfix, pop(&stack));
          }
          push(&stack, operations[j]);
          cursor += strlen(operations[j]);
          flag = 1;
          *code = SUCCESS;
          break;
        }
      }
      if (*code == ERROR) break;
    }
  }
  while (stack.size) {
    push(postfix, pop(&stack));
  }
  return cursor;
}

double calculation(Stack_t *rpn, int *code) {
  char oper[15][7] = {"+\0",    "-\0",    "*\0",    "/\0",   "^\0",
                      "mod\0",  "sin\0",  "cos\0",  "tan\0", "acos\0",
                      "asin\0", "atan\0", "sqrt\0", "ln\0",  "log\0"};
  double numbers[128] = {0};
  int counter = 0;
  double (*func[9])(double) = {&sin,  &cos,  &tan, &acos, &asin,
                               &atan, &sqrt, &log, &log10};
  double (*func2arg[6])(double, double) = {&s21_add, &s21_sub, &s21_mul,
                                           &s21_div, &pow,     &fmod};

  while (rpn->size) {
    double num = atof(peek(rpn));
    if (num != 0 || !strcmp(peek(rpn), "0")) {
      numbers[counter] = num;
      counter++;
    } else if (!strcmp(peek(rpn), "~")) {
      numbers[counter - 1] *= -1;
    } else {
      for (int j = 0; j < 15; j++)
        if (!strcmp(peek(rpn), oper[j])) {
          if (j < 6) {
            if (counter < 2) {
              *code = ERROR;
              break;
            }
            counter--;
            numbers[counter - 1] =
                func2arg[j](numbers[counter - 1], numbers[counter]);
          } else {
            if (counter < 1) {
              *code = ERROR;
              break;
            }
            numbers[counter - 1] = func[j - 6](numbers[counter - 1]);
          }
          break;
        }
    }
    pop(rpn);
    if (*code == ERROR) break;
  }
  return numbers[0];
}

void push(Stack_t *stack, char *value) {
  strcpy(stack->data[stack->size], value);
  stack->size++;
}

char *pop(Stack_t *stack) {
  if (stack->size == 0) {
    exit(STACK_UNDERFLOW);
  }
  stack->size--;
  return stack->data[stack->size];
}

const char *peek(const Stack_t *stack) {
  if (stack->size <= 0) {
    exit(STACK_UNDERFLOW);
  }
  return stack->data[stack->size - 1];
}

int priority(const char *str) {
  int pr;
  if (!strcmp(str, "+") || !strcmp(str, "-") || !strcmp(str, "~"))
    pr = 1;
  else if (!strcmp(str, "*") || !strcmp(str, "/") || !strcmp(str, "mod"))
    pr = 2;
  else if (!strcmp(str, "^"))
    pr = 3;
  else
    pr = 4;
  return pr;
}

double s21_add(double a, double b) { return a + b; }

double s21_sub(double a, double b) { return a - b; }

double s21_mul(double a, double b) { return a * b; }

double s21_div(double a, double b) { return a / b; }
