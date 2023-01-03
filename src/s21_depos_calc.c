//
// Created by Jenelle Puddy on 12/17/22.
//

#include "../include/s21_depos_calc.h"

void depos_calc(double amount, int term, double interest, int period,
                struct tm start, int capint, dates withrepls, double *extra,
                double *taxamo, double *total, double *effect) {
  // Структура времени под дату завершения вклада
  struct tm end;
  time_t start_t, end_t;
  start_t = mktime(&start);
  get_date(start.tm_year, start.tm_mon + term, start.tm_mday, &end, &end_t);
  // Структуры для определения начала и конца года
  // Нужно для расчёта суточного процента и годового налога
  struct tm start_year, end_year;
  time_t stry_t, endy_t;
  get_date(start.tm_year, 0, 1, &start_year, &stry_t);
  get_date(start.tm_year + 1, 0, 1, &end_year, &endy_t);
  // Расчёт суточного процента
  int diff = (int)(round(difftime(end_t, start_t) / 60 / 60 / 24));
  long double daily_interest =
      interest / 100.0 / (round(difftime(endy_t, stry_t)) / 60 / 60 / 24);
  // Переменные
  int month_old = start.tm_mon;
  int day = start.tm_mday;
  int year = start.tm_year;
  int day_of_week = start.tm_wday;
  // Переменные суммарной прибыли, ежемесячной и ежегодной
  long double interest_amo = 0;
  long double period_pay = 0;
  long double year_profit = 0;
  // Основной цикл
  int i_for_dates = 0;
  int count = 0;
  for (int i = 0; i <= diff; i++) {
    if (i_for_dates < withrepls.amount &&
        mktime(&withrepls.day[i_for_dates]) == mktime(&start)) {
      amount += withrepls.sum[i_for_dates];
      i_for_dates++;
    }
    switch (period) {
      case ED:
        period_pay = roundl(period_pay * 100) / 100;
        interest_amo += period_pay;
        year_profit += period_pay;
        if (capint) amount += period_pay;
        period_pay = 0;
        break;
      case EW:
        if (start.tm_wday == day_of_week || i == diff) {
          period_pay = roundl(period_pay * 100) / 100;
          interest_amo += period_pay;
          year_profit += period_pay;
          if (capint) amount += period_pay;
          period_pay = 0;
        }
        break;
      case EM:
        if (start.tm_mday == day && start.tm_mon != month_old) {
          month_old = start.tm_mon;
          period_pay = roundl(period_pay * 100) / 100;
          interest_amo += period_pay;
          year_profit += period_pay;
          if (capint) amount += period_pay;
          period_pay = 0;
        }
        break;
      case EQ:
        if (start.tm_mday == day && start.tm_mon != month_old) {
          count++;
          month_old = start.tm_mon;
        }
        if ((start.tm_mday == day && count == 3) || i == diff) {
          count = 0;
          period_pay = roundl(period_pay * 100) / 100;
          interest_amo += period_pay;
          year_profit += period_pay;
          if (capint) amount += period_pay;
          period_pay = 0;
        }
        break;
      case EHY:
        if (start.tm_mday == day && start.tm_mon != month_old) {
          count++;
          month_old = start.tm_mon;
        }
        if ((start.tm_mday == day && count == 6) || i == diff) {
          count = 0;
          period_pay = roundl(period_pay * 100) / 100;
          interest_amo += period_pay;
          year_profit += period_pay;
          if (capint) amount += period_pay;
          period_pay = 0;
        }
        break;
      case EY:
        if (start.tm_mday == day && start.tm_mon != month_old) {
          count++;
          month_old = start.tm_mon;
        }
        if ((start.tm_mday == day && count == 12) || i == diff) {
          count = 0;
          period_pay = roundl(period_pay * 100) / 100;
          interest_amo += period_pay;
          year_profit += period_pay;
          if (capint) amount += period_pay;
          period_pay = 0;
        }
        break;
    }
    if (start.tm_year - year || i == diff) {
      double supp = year_profit - TAX_LIMIT;
      year_profit = 0;
      if (supp > 0) *taxamo += roundl(supp * 13) / 100;
      year++;
      start_year.tm_year++;
      end_year.tm_year++;
      stry_t = mktime(&start_year);
      endy_t = mktime(&end_year);
      daily_interest =
          interest / 100.0 / round((difftime(endy_t, stry_t) / 60 / 60 / 24));
    }
    period_pay += amount * daily_interest;
    start.tm_mday++;
    mktime(&start);
  }
  *extra = interest_amo;
  *total = amount;
  *effect = *extra * 365 / diff * 100;
}

void get_date(int year, int month, int day, struct tm *date, time_t *date_t) {
  time_t now;
  time(&now);
  *date = *localtime(&now);
  date->tm_year = year;
  date->tm_mon = month;
  date->tm_mday = day;
  date->tm_hour = 0;
  date->tm_min = 0;
  date->tm_sec = 0;
  if (date_t)
    *date_t = mktime(date);
  else
    mktime(date);
}
