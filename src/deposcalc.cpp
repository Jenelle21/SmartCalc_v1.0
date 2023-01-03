#include "../include/deposcalc.h"

#include "ui_deposcalc.h"

DeposCalc::DeposCalc(QWidget *parent)
    : QStackedWidget(parent), ui(new Ui::DeposCalc) {
  ui->setupUi(this);
  connect(ui->toCalc, SIGNAL(clicked()), this, SLOT(onCalcClicked()));
  connect(ui->toCred, SIGNAL(clicked()), this, SLOT(credit()));
  connect(ui->calculate, SIGNAL(clicked()), this, SLOT(calculate()));
  connect(ui->back, SIGNAL(clicked()), this, SLOT(back()));
  connect(ui->checkM, SIGNAL(clicked()), this, SLOT(uncheckY()));
  connect(ui->checkY, SIGNAL(clicked()), this, SLOT(uncheckM()));
  connect(ui->add, SIGNAL(clicked()), this, SLOT(addField()));
  ui->interestEdit->setValidator(new QDoubleValidator(ui->interestEdit));
  ui->termEdit->setValidator(new QIntValidator(1, 50, ui->termEdit));
  ui->amountEdit->setValidator(new QDoubleValidator(this));
  ui->start->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
  ui->start->setDate(QDate::currentDate());
  ui->comboBox->setCurrentIndex(2);
  FieldsNumTotal = 0;
}

DeposCalc::~DeposCalc() {
    delete ui;
}

void DeposCalc::onCalcClicked() { emit CalcClicked(); }

void DeposCalc::credit() { emit CredClicked(); }

void DeposCalc::calculate() {
  if (ui->amountEdit->text() != "" && ui->interestEdit->text() != "" &&
      ui->termEdit->text() != "" &&
      (ui->checkM->isChecked() || ui->checkY->isChecked())) {
    struct tm first;
    double amount = ui->amountEdit->text().toDouble();
    int term = ui->termEdit->text().toInt();
    if (ui->checkY->isChecked()) term *= 12;
    double interest = ui->interestEdit->text().toDouble();
    int period = 1 + ui->comboBox->currentIndex();
    int capint = ui->capitalisation->isChecked();
    dates withrepls;
    double extra, total, effect;
    double taxamo = 0;
    QDate start = ui->start->date();
    get_date(start.year() - 1900, start.month() - 1, start.day(), &first, NULL);
    QDate wrDates[FieldsNumTotal];
    double wrValues[FieldsNumTotal];
    if (FieldsNumTotal ? !fillingWR(wrDates, wrValues) : false) {
      QMessageBox::critical(this, "Error", "All the fields must be filled");
    } else {
      if (FieldsNumTotal) {
        sortWR(wrDates, wrValues);
        for (int i = 0; i < FieldsNumTotal; i++) {
          get_date(wrDates[i].year() - 1900, wrDates[i].month() - 1,
                   wrDates[i].day(), &withrepls.day[i], NULL);
          withrepls.sum[i] = wrValues[i];
        }
        withrepls.amount = FieldsNumTotal;
      }
      depos_calc(amount, term, interest, period, first, capint, withrepls,
                 &extra, &taxamo, &total, &effect);
      ui->extraAmo->setText(QString::number(extra, 'f', 2));
      ui->taxAmo->setText(QString::number(taxamo, 'f', 2));
      ui->total->setText(QString::number(total, 'f', 2));
      effect /= amount;
      effect = round(effect * 100) / 100;
      if (!capint) {
        ui->finalInterest->hide();
        ui->fInt->hide();
      } else {
        ui->finalInterest->setText(QString::number(effect, 'f', 2));
        ui->finalInterest->show();
        ui->fInt->show();
      }
      setCurrentIndex(1);
    }
  } else {
    QMessageBox::critical(this, "Error", "All the fields must be filled");
  }
}

bool DeposCalc::fillingWR(QDate *WithReplDates, double *WithReplValues) {
  bool flag = true;
  for (int i = 0; i < FieldsNumTotal; i++) {
    WithReplsField *field = allFieldPtr[i];
    QDate date = field->getDateFromField();
    double val = field->getValueFromField();
    if (val == 0) {
      flag = false;
    } else {
      WithReplDates[i] = date;
      WithReplValues[i] = val;
    }
  }
  return flag;
}

void DeposCalc::sortWR(QDate *wrd, double *wrv) {
  int n = FieldsNumTotal;
  for (int i = 1; i < n; i++)
    for (int j = i; j > 0 && wrd[j - 1] > wrd[j]; j--) {
      std::swap(wrd[j - 1], wrd[j]);
      std::swap(wrv[j - 1], wrv[j]);
    }
  for (int i = 0; i < n - 1; i++) {
    if (wrd[i] == wrd[i + 1]) {
      wrv[i] += wrv[i + 1];
      for (int j = i + 1; j < n - 1; j++) {
        wrd[j] = wrd[j + 1];
        wrv[j] = wrv[j + 1];
      }
      n--;
      if (i) i--;
    }
  }
  FieldsNumTotal = n;
}

void DeposCalc::back() { setCurrentIndex(0); }

void DeposCalc::uncheckY() { ui->checkY->setChecked(false); }

void DeposCalc::uncheckM() { ui->checkM->setChecked(false); }

void DeposCalc::addField() {
  WithReplsField *newField = new WithReplsField(this);
  ui->scrollAreaWidgetContents->layout()->addWidget(newField);
  connect(newField, SIGNAL(closeThisField(int)), this, SLOT(delField(int)));
  newField->fieldNumber = FieldsNumTotal;
  allFieldPtr.append(newField);
  FieldsNumTotal++;
  if (FieldsNumTotal == 60) {
    ui->add->hide();
    QMessageBox::information(
        this, "Info",
        "The limit for the number of replenishments/partial withdrawals has "
        "been reached.");
  }
}

void DeposCalc::delField(int fieldNumber) {
  allFieldPtr[fieldNumber]->close();
  for (int i = fieldNumber + 1; i < allFieldPtr.length(); i++)
    allFieldPtr[i]->fieldNumber--;
  FieldsNumTotal--;
  allFieldPtr.remove(fieldNumber);
  ui->add->show();
}
