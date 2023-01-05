#ifndef INCLUDE_CREDITCALC_H_
#define INCLUDE_CREDITCALC_H_

#include <QDoubleValidator>
#include <QIntValidator>
#include <QMessageBox>
#include <QStackedWidget>

#include "s21_credit_calc.h"

namespace Ui {
class CreditCalc;
}

class CreditCalc : public QStackedWidget {
  Q_OBJECT

 public:
  explicit CreditCalc(QWidget *parent = nullptr);
  ~CreditCalc();
  QStackedWidget *CredCalc_;

 private:
  Ui::CreditCalc *ui;

 signals:
  void CalcClicked();
  void DeposClicked();

 private slots:
  void onCalcClicked();
  void depos();
  void setValAmo();
  void setValInt();
  void setValTerm();
  void on_loanEdit_textChanged(const QString &arg1);
  void on_interestEdit_textChanged(const QString &arg1);
  void on_termEdit_textChanged(const QString &arg1);
  void calculate();
  void back();
  void uncheckY();
  void uncheckM();
  void uncheckDiff();
  void uncheckAnn();
};

#endif  // INCLUDE_CREDITCALC_H_
