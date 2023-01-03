//
// Created by Jenelle Puddy on 12/12/22.
//

#include <check.h>

#include "../include/s21_credit_calc.h"
#include "../include/s21_depos_calc.h"
#include "../include/s21_smart_calc.h"
#define EPS 1e-7

START_TEST(Test1) {
  char expression[] = {"(2+3)*5"};
  char* pexp = &expression[0];
  double result = 0;
  controller(pexp, &result);
  ck_assert_float_eq(result, 25.0);
}
END_TEST

START_TEST(Test2) {
  char expression[] = {"1/2 + (2+3)/(sin(9-2)^2-6/7)"};
  char* pexp = &expression[0];
  double result = 0;
  double result2 = -11.2506;
  controller(pexp, &result);
  ck_assert_float_lt(EPS, fabs(result2 - result));
}
END_TEST

START_TEST(Test3) {
  char expression[] = {"1/2+(2+3"};
  char* pexp = &expression[0];
  double result = 0;
  ck_assert_int_eq(controller(pexp, &result), 0);
}
END_TEST

START_TEST(Test4) {
  char expression[] = {"1/2)+(2.3.5+3)"};
  char* pexp = &expression[0];
  double result = 0;
  ck_assert_int_eq(controller(pexp, &result), 0);
}
END_TEST

START_TEST(Test5) {
  char expression[] = {"**"};
  char* pexp = &expression[0];
  double result = 0;
  ck_assert_int_eq(controller(pexp, &result), 0);
}
END_TEST

START_TEST(Test6) {
  char expression[] = {
      "sin(2) * cos(5) + tan(67^2) / sin(128) - atan(sqrt(9)) - (4 mod 2) * "
      "log(5)"};
  char* pexp = &expression[0];
  double result = 0;
  double result2 = -1.47532;
  controller(pexp, &result);
  ck_assert_float_lt(EPS, fabs(result2 - result));
}
END_TEST

START_TEST(Test7) {
  char expression[] = {
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))"};
  char* pexp = &expression[0];
  double result = 0;
  double result2 = -30.07216495;
  controller(pexp, &result);
  ck_assert_double_eq_tol(result, result2, EPS);
}
END_TEST

START_TEST(Test8) {
  char expression[] = {"(132+sin(asin(sqrt(ln(log(228.11)))))-4*5^6*(123))"};
  char* pexp = &expression[0];
  double result = 0;
  double result2 = -7687367.07378457;
  controller(pexp, &result);
  ck_assert_double_eq_tol(result, result2, EPS);
}
END_TEST

START_TEST(Test9) {
  char expression[] = {
      "sin(1)+cos(1)+asin(1)+acos(1)+atan(1)+tan(1)+sqrt(16)+ln(10)+log(10)"};
  char* pexp = &expression[0];
  double result = 0;
  double result2 = 12.5979605985;
  controller(pexp, &result);
  ck_assert_double_eq_tol(result, result2, EPS);
}
END_TEST

START_TEST(Test10) {
  char expression[] = {"sin(-24)-+cos()"};
  char* pexp = &expression[0];
  double result = 0;
  ck_assert_int_eq(controller(pexp, &result), 0);
}
END_TEST

// CREDIT CALC TEST

START_TEST(Test11) {
  double amount = 1000000;
  int term = 12;
  double interest = 8;
  double op, tot;
  double* res = calloc(term, sizeof(double));
  credit_calc(amount, term, interest, ANN, &op, &tot, &res);
  ck_assert_double_eq_tol(res[0], 86988.43, 0.1);
  ck_assert_double_eq_tol(op, 43861.16, 0.1);
  ck_assert_double_eq_tol(tot, 1043861.16, 0.1);
  free(res);
}
END_TEST

START_TEST(Test12) {
  double amount = 2500000;
  int term = 36;
  double interest = 11;
  double op, tot;
  double* res = calloc(term, sizeof(double));
  credit_calc(amount, term, interest, DIFF, &op, &tot, &res);
  ck_assert_double_eq_tol(res[0], 92361.11, 0.1);
  ck_assert_double_eq_tol(op, 423958.33, 0.1);
  ck_assert_double_eq_tol(tot, 2923958.33, 0.1);
  free(res);
}
END_TEST

// DEPOS CALC TEST

START_TEST(Test13) {
  double amount = 1000000;
  int term = 12;
  double interest = 12;
  int period = 3;
  int capint = 1;
  dates wr;
  wr.amount = 0;
  double extra, taxamo, total, effect;
  struct tm start;
  get_date(2022 - 1900, 11, 25, &start, NULL);
  depos_calc(amount, term, interest, period, start, capint, wr, &extra, &taxamo,
             &total, &effect);
  ck_assert_double_eq_tol(extra, 126824.50, 0.01);
  ck_assert_double_eq_tol(taxamo, 6737.19, 0.01);
  ck_assert_double_eq_tol(total, 1126824.50, 0.01);
}
END_TEST

START_TEST(Test14) {
  double amount = 2000000;
  int term = 24;
  double interest = 13;
  int period = 2;
  int capint = 0;
  dates wr;
  wr.amount = 1;
  get_date(2023 - 1900, 2, 31, &wr.day[0], NULL);
  wr.sum[0] = 150000;
  double extra, taxamo, total, effect;
  struct tm start;
  get_date(2022 - 1900, 11, 25, &start, NULL);
  depos_calc(amount, term, interest, period, start, capint, wr, &extra, &taxamo,
             &total, &effect);
  ck_assert_double_eq_tol(extra, 553883.69, 10);
  ck_assert_double_eq_tol(taxamo, 52504.88, 1000);
  ck_assert_double_eq_tol(total, 2150000.00, 0.01);
}
END_TEST

START_TEST(Test15) {
  double amount = 1500000;
  int term = 72;
  double interest = 7;
  int period = 6;
  int capint = 0;
  dates wr;
  wr.amount = 0;
  double extra, taxamo, total, effect;
  struct tm start;
  get_date(2022 - 1900, 11, 25, &start, NULL);
  depos_calc(amount, term, interest, period, start, capint, wr, &extra, &taxamo,
             &total, &effect);
  ck_assert_double_eq_tol(extra, 630004.72, 10);
  ck_assert_double_eq_tol(taxamo, 23400.61, 10);
  ck_assert_double_eq_tol(total, 1500000.00, 0.01);
}
END_TEST

START_TEST(Test16) {
  double amount = 1234567;
  int term = 32;
  double interest = 11;
  int period = 5;
  int capint = 1;
  dates wr;
  wr.amount = 0;
  double extra, taxamo, total, effect;
  struct tm start;
  get_date(2022 - 1900, 11, 25, &start, NULL);
  depos_calc(amount, term, interest, period, start, capint, wr, &extra, &taxamo,
             &total, &effect);
  ck_assert_double_eq_tol(extra, 408390.38, 0.1);
  ck_assert_double_eq_tol(taxamo, 23840.75, 0.1);
  ck_assert_double_eq_tol(total, 1642957.38, 0.1);
}
END_TEST

Suite* s21_math_tests_create() {
  Suite* s21_math = suite_create("s21_math");
  TCase* s21_math_tests = tcase_create("S21_MATH");
  tcase_add_test(s21_math_tests, Test1);
  tcase_add_test(s21_math_tests, Test2);
  tcase_add_test(s21_math_tests, Test3);
  tcase_add_test(s21_math_tests, Test4);
  tcase_add_test(s21_math_tests, Test5);
  tcase_add_test(s21_math_tests, Test6);
  tcase_add_test(s21_math_tests, Test7);
  tcase_add_test(s21_math_tests, Test8);
  tcase_add_test(s21_math_tests, Test9);
  tcase_add_test(s21_math_tests, Test10);
  tcase_add_test(s21_math_tests, Test11);
  tcase_add_test(s21_math_tests, Test12);
  tcase_add_test(s21_math_tests, Test13);
  tcase_add_test(s21_math_tests, Test14);
  tcase_add_test(s21_math_tests, Test15);
  tcase_add_test(s21_math_tests, Test16);
  suite_add_tcase(s21_math, s21_math_tests);
  return s21_math;
}

int main() {
  Suite* s21_math = s21_math_tests_create();
  SRunner* s21_math_runner = srunner_create(s21_math);
  int number_failed;
  srunner_run_all(s21_math_runner, FP_NORMAL);
  number_failed = srunner_ntests_failed(s21_math_runner);
  srunner_free(s21_math_runner);

  return number_failed == 0 ? 0 : 1;
}
