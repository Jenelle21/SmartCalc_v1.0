#include "../include/creditcalc.h"

#include "ui_creditcalc.h"

CreditCalc::CreditCalc(QWidget *parent)
    : QStackedWidget(parent),
      CredCalc_(new QStackedWidget(this)),
      ui(new Ui::CreditCalc) {
  ui->setupUi(this);

  connect(ui->toCalc, SIGNAL(clicked()), this, SLOT(onCalcClicked()));
  connect(ui->toDepos, SIGNAL(clicked()), this, SLOT(depos()));
  connect(ui->amountSlider, SIGNAL(valueChanged(int)), this, SLOT(setValAmo()));
  connect(ui->interestSlider, SIGNAL(valueChanged(int)), this,
          SLOT(setValInt()));
  connect(ui->termSlider, SIGNAL(valueChanged(int)), this, SLOT(setValTerm()));
  ui->interestEdit->setValidator(new QDoubleValidator(ui->interestEdit));
  ui->termEdit->setValidator(new QIntValidator(1, 36, ui->termEdit));
  connect(ui->calculate, SIGNAL(clicked()), this, SLOT(calculate()));
  connect(ui->back, SIGNAL(clicked()), this, SLOT(back()));
  ui->checkM->setChecked(true);
  connect(ui->checkM, SIGNAL(clicked()), this, SLOT(uncheckY()));
  connect(ui->checkY, SIGNAL(clicked()), this, SLOT(uncheckM()));
  connect(ui->checkAnn, SIGNAL(clicked()), this, SLOT(uncheckDiff()));
  connect(ui->checkDiff, SIGNAL(clicked()), this, SLOT(uncheckAnn()));
}

CreditCalc::~CreditCalc() { delete ui; }

void CreditCalc::onCalcClicked() { emit CalcClicked(); }

void CreditCalc::depos() { emit DeposClicked(); }

void CreditCalc::setValAmo() {
  int a = round(ui->amountSlider->value() / 100000) * 100000;
  QString text = QString::number(a);
  ui->loanEdit->setText(text);
}

void CreditCalc::setValInt() {
  QString text = QString::number(ui->interestSlider->value());
  ui->interestEdit->setText(text);
}

void CreditCalc::setValTerm() {
  QString text = QString::number(ui->termSlider->value());
  ui->termEdit->setText(text);
}

void CreditCalc::on_loanEdit_textChanged(const QString &arg1) {
  ui->amountSlider->setSliderPosition(arg1.toInt());
}

void CreditCalc::on_interestEdit_textChanged(const QString &arg1) {
  ui->interestSlider->setSliderPosition(arg1.toInt());
}

void CreditCalc::on_termEdit_textChanged(const QString &arg1) {
  ui->termSlider->setSliderPosition(arg1.toInt());
}

void CreditCalc::calculate() {
  if ((ui->checkAnn->isChecked() || ui->checkDiff->isChecked()) &&
      ui->interestEdit->text() != "" && ui->loanEdit->text() != "" &&
      ui->termEdit->text() != "") {
    double amount = ui->loanEdit->text().toDouble();
    int term = ui->termEdit->text().toInt();
    double interest = ui->interestEdit->text().toInt();
    int type;
    if (ui->checkY->isChecked()) term *= 12;
    if (ui->checkAnn->isChecked())
      type = ANN;
    else
      type = DIFF;
    double overpay, total, *pays;
    pays = new double[term];
    credit_calc(amount, term, interest, type, &overpay, &total, &pays);
    ui->overPay->setText(QString::number(overpay, 'f', 2));
    ui->totPay->setText(QString::number(total, 'f', 2));
    if (type == DIFF)
      ui->monPay->setText(QString::number(pays[0], 'f', 2) + " ... " +
                          QString::number(pays[term - 1], 'f', 2));
    else
      ui->monPay->setText(QString::number(pays[0], 'f', 2));
    delete(pays);
    setCurrentIndex(1);
  } else {
    QMessageBox::critical(this, "Error", "All the fields must be filled");
  }
}

void CreditCalc::back() { setCurrentIndex(0); }

void CreditCalc::uncheckY() { ui->checkY->setChecked(false); }

void CreditCalc::uncheckM() { ui->checkM->setChecked(false); }

void CreditCalc::uncheckAnn() { ui->checkAnn->setChecked(false); }

void CreditCalc::uncheckDiff() { ui->checkDiff->setChecked(false); }
