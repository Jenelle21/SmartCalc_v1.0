//
// Created by Jenelle Puddy on 12/17/22.
//

#include "../include/s21_depos_calc.h"
#include "stdio.h"

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
  int day = start.tm_mday;
  int year = start.tm_year;
  // Переменные суммарной прибыли, ежемесячной и ежегодной
  long double interest_amo = 0;
  long double period_pay = 0;
  long double year_profit = 0;
  // Основной цикл
  int i_for_dates = 0;
  time_t date_to_pay = next_date(start, end, period);
  for (int i = 0; i <= diff; i++) {
    if (i_for_dates < withrepls.amount &&
        mktime(&withrepls.day[i_for_dates]) == mktime(&start)) {
      amount += withrepls.sum[i_for_dates];
      i_for_dates++;
    }
    if (round(difftime(date_to_pay, mktime(&start)) / 60 / 60 / 24) == 0) {
        period_pay = roundl(period_pay * 100) / 100;
        interest_amo += period_pay;
        year_profit += period_pay;
        printf("%2d.%2d.%4d - %Lf\n", start.tm_mday, start.tm_mon + 1, start.tm_year + 1900, period_pay);
        if (capint) amount += period_pay;
        period_pay = 0;
        date_to_pay = next_date(start, end, period);
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
  }
  *extra = interest_amo;
  *total = amount;
  *effect = *extra * 365 / diff * 100;
}

time_t next_date(struct tm now, struct tm end, int period) {
    struct tm next;
    time_t next_t;
    switch (period) {
        case ED:
            get_date(now.tm_year, now.tm_mon, now.tm_mday + 1, &next, &next_t);
            break;
        case EW:
            get_date(now.tm_year, now.tm_mon, now.tm_mday + 7, &next, &next_t);
            break;
        case EM:
            get_date(now.tm_year, now.tm_mon + 1, now.tm_mday, &next, &next_t);
            while (next.tm_mon - now.tm_mon == 2)
                get_date(next.tm_year, next.tm_mon, next.tm_mday - 1, &next, &next_t);
            break;
        case EQ:
            get_date(now.tm_year, now.tm_mon + 3, now.tm_mday, &next, &next_t);
            while (next.tm_mon - now.tm_mon == 4)
                get_date(next.tm_year, next.tm_mon, next.tm_mday - 1, &next, &next_t);
            break;
        case EHY:
            get_date(now.tm_year, now.tm_mon + 6, now.tm_mday, &next, &next_t);
            while (next.tm_mon - now.tm_mon == 7)
                get_date(next.tm_year, next.tm_mon, next.tm_mday - 1, &next, &next_t);
            break;
        case EY:
            get_date(now.tm_year + 1, now.tm_mon, now.tm_mday, &next, &next_t);
            break;
    }
    if (round(difftime(mktime(&end), next_t) / 60 / 60 / 24) < 0)
        next_t = mktime(&end);
    return next_t;
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
