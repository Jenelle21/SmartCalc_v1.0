//
// Created by Jenelle Puddy on 12/17/22.
//

#ifndef SRC_S21_DEPOS_CALC_H_
#define SRC_S21_DEPOS_CALC_H_

#include <math.h>
#include <time.h>

#define TAX_LIMIT 1000000 * 7.5 / 100
#define ED 1
#define EW 2
#define EM 3
#define EQ 4
#define EHY 5
#define EY 6

#ifdef __cplusplus
extern "C" {
#endif

typedef struct dates_t {
  int amount;
  struct tm day[60];
  double sum[60];
} dates;

typedef struct res_t {
  struct tm day;
  double sum;
} list;

/// @brief Заполняет структуру времени на основе предоставленных данных,
/// приводит её значения к реальным
/// @param [in] year Год (-1900 для формата time.h)
/// @param [in] month Месяц (-1 для формата time.h)
/// @param [in] day День
/// @param [out] date Структура времени
/// @param [in/out] date_t Числовое значение даты, может быть NULL
void get_date(int year, int month, int day, struct tm *date, time_t *date_t);
/**
 * @brief Депозитный калькулятор
 * @param amount [in] Сумма вклада
 * @param term [in] Срок вклада (в месяцах)
 * @param interest [in] Процент
 * @param period [in] Частота выплат
 * @param start [in] День создания вклада
 * @param capint [in] Капитализация (есть/нет)
 * @param withrepls [in] Структура пополнений/снятий
 * @param extra [out] Доход за весь срок вклада
 * @param taxamo [out] Сумма налога за весь срок вклада
 * @param total [out] Итоговая сумма на счету
 */
void depos_calc(double amount, int term, double interest, int period,
                struct tm start, int capint, dates withrepls, double *extra,
                double *taxamo, double *total, double *);

#ifdef __cplusplus
}
#endif

#endif  // SRC_S21_DEPOS_CALC_H_
