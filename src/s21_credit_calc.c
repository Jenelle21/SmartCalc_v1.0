//
// Created by Jenelle Puddy on 12/15/22.
//

#include "../include/s21_credit_calc.h"

void credit_calc(double amount, int term, double interest, int type,
                 double *overpay, double *total, double **res) {
  double m_interest;
  m_interest = interest / 1200;
  if (type == ANN) {
    (*res)[0] = amount * m_interest / (1 - pow(1 + m_interest, -term));
    for (int i = 1; i < term; i++) {
      (*res)[i] = (*res)[0];
    }
    *total = (*res)[0] * (term - 1) + (*res)[term - 1];
    *overpay = *total - amount;
  } else {
    *overpay = 0;
    double ost = amount;
    for (int i = 0; i < term; i++) {
      (*res)[i] = ost / (term - i) + ost * m_interest;
      *overpay += ost * m_interest;
      ost = ost - ost / (term - i);
    }
    *total = amount + *overpay;
  }
}
