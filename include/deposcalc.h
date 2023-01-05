#ifndef INCLUDE_DEPOSCALC_H_
#define INCLUDE_DEPOSCALC_H_

#include <QBoxLayout>
#include <QCalendarWidget>
#include <QMessageBox>
#include <QStackedWidget>
#include <QVector>

#include "s21_depos_calc.h"
#include "withreplsfield.h"

namespace Ui {
class DeposCalc;
}

class DeposCalc : public QStackedWidget {
  Q_OBJECT

 public:
  QHash<QPushButton *, QHBoxLayout *> mButtonToLayoutMap;
  explicit DeposCalc(QWidget *parent = nullptr);
  ~DeposCalc();
  int FieldsNumTotal;
  QVector<WithReplsField *> allFieldPtr;

 public slots:
  void delField(int);

 private:
  Ui::DeposCalc *ui;

 signals:
  void CalcClicked();
  void CredClicked();

 private slots:
  void onCalcClicked();
  void credit();
  void calculate();
  void back();
  void uncheckY();
  void uncheckM();
  void addField();
  bool fillingWR(QDate *, double *);
  void sortWR(QDate *, double *);
  void on_amountEdit_textEdited(const QString &arg1);
};

#endif  // INCLUDE_DEPOSCALC_H_
