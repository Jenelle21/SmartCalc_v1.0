#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QDoubleValidator>
#include <QIntValidator>
#include <QMainWindow>
#include <QTimer>
#include <QVector>

#include "../include/creditcalc.h"
#include "../include/deposcalc.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculator;
}
QT_END_NAMESPACE

class Calculator : public QMainWindow {
  Q_OBJECT

 public:
  Calculator(QWidget *parent = nullptr);
  ~Calculator();
  QTimer *timer;

 private:
  Ui::Calculator *ui;
  QVector<double> x, y;
  CreditCalc _CredCalc;
  DeposCalc _DepCalc;

 private slots:
  void digitsNumbers();
  void clear();
  void arithmetic();
  void func();
  void calculate();
  void xPressed();
  void printX();
  void backToCalc();
  void makeGraph();
  void toCredit();
  void toDepos();
  void fromCredToDep();
  void fromDepToCred();
  void backFromCredit();
  void backFromDepos();
};
#endif  // CALCULATOR_H
