//
// Created by Jenelle Puddy on 12/15/22.
//

#ifndef SRC_S21_CREDIT_CALC_H_
#define SRC_S21_CREDIT_CALC_H_

#include <math.h>

#define ANN 1
#define DIFF 2

#ifdef __cplusplus
extern "C" {
#endif

void credit_calc(double amount, int term, double interest, int type,
                 double *overpay, double *total, double **res);

#ifdef __cplusplus
}
#endif

#endif  // SRC_S21_CREDIT_CALC_H_
