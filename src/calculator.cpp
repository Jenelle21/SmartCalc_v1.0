#include "../include/calculator.h"

#include "ui_calculator.h"

// TODO: пофиксить сортировку пополнений в депозите, хз что там, но не работает при одинаковых датах
// TODO: теперь после уменьшения даты под маленький месяц нужно добавить увеличение

static bool check = true;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Calculator) {
  ui->setupUi(this);
  timer = new QTimer;
  ui->stackedWidget->addWidget(&_CredCalc);
  ui->stackedWidget->addWidget(&_DepCalc);
  ui->stackedWidget->insertWidget(2, &_CredCalc);
  ui->stackedWidget->insertWidget(3, &_DepCalc);

  connect(ui->Button_0, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
  connect(ui->Button_1, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
  connect(ui->Button_2, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
  connect(ui->Button_3, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
  connect(ui->Button_4, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
  connect(ui->Button_5, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
  connect(ui->Button_6, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
  connect(ui->Button_7, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
  connect(ui->Button_8, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
  connect(ui->Button_9, SIGNAL(clicked()), this, SLOT(digitsNumbers()));
  connect(ui->Button_dot, SIGNAL(clicked()), this, SLOT(digitsNumbers()));

  connect(ui->Button_del, SIGNAL(clicked()), this, SLOT(clear()));
  connect(ui->Button_clear, SIGNAL(clicked()), this, SLOT(clear()));

  connect(ui->Button_add, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->Button_sub, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->Button_mul, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->Button_div, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->Button_scale, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->Button_open, SIGNAL(clicked()), this, SLOT(arithmetic()));
  connect(ui->Button_close, SIGNAL(clicked()), this, SLOT(arithmetic()));

  connect(ui->Button_sin, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->Button_cos, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->Button_tan, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->Button_asin, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->Button_acos, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->Button_atan, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->Button_sqrt, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->Button_ln, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->Button_log, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->Button_mod, SIGNAL(clicked()), this, SLOT(func()));

  connect(ui->Result, SIGNAL(returnPressed()), this, SLOT(calculate()));
  connect(ui->Button_equal, SIGNAL(clicked()), this, SLOT(calculate()));
  connect(ui->Back, SIGNAL(clicked()), this, SLOT(backToCalc()));
  connect(ui->Grapx, SIGNAL(clicked()), this, SLOT(makeGraph()));
  connect(ui->Graph, SIGNAL(returnPressed()), this, SLOT(makeGraph()));

  connect(ui->Button_x, SIGNAL(clicked()), this, SLOT(xPressed()));
  ui->Value->setValidator(new QDoubleValidator(ui->Value));
  ui->Xmax_edit->setValidator(
      new QIntValidator(-1000000, 1000000, ui->Xmax_edit));
  ui->Xmin_edit->setValidator(
      new QIntValidator(-1000000, 1000000, ui->Xmin_edit));

  connect(ui->Button_credit, SIGNAL(clicked()), this, SLOT(toCredit()));
  connect(ui->Button_depos, SIGNAL(clicked()), this, SLOT(toDepos()));
  connect(&_CredCalc, SIGNAL(CalcClicked()), this, SLOT(backFromCredit()));
  connect(&_DepCalc, SIGNAL(CalcClicked()), this, SLOT(backFromDepos()));
  connect(&_CredCalc, SIGNAL(DeposClicked()), this, SLOT(fromCredToDep()));
  connect(&_DepCalc, SIGNAL(CredClicked()), this, SLOT(fromDepToCred()));

  connect(timer, SIGNAL(timeout()), this, SLOT(printX()));
}

Calculator::~Calculator() {
  delete ui;
  delete timer;
}

void Calculator::digitsNumbers() {
  QPushButton *button = (QPushButton *)sender();
  QString result_label = ui->Result->text();
  if (result_label == "Incorrect input") {
    ui->Result->setText("");
    result_label = ui->Result->text();
  }
  QByteArray ba = result_label.toLocal8Bit();
  char *char_array = ba.data();
  if (button == ui->Button_dot &&
      ((!(char_array[result_label.size() - 1] >= '0' &&
          char_array[result_label.size() - 1] <= '9')) ||
       (result_label.size() == 0))) {
    ui->Result->setText(result_label + "0.");
  } else {
    ui->Result->setText(result_label + button->text());
  }
}

void Calculator::clear() {
  QPushButton *button = (QPushButton *)sender();
  if (button == ui->Button_clear) {
    ui->Result->setText("");
  } else {
    QString result_label = ui->Result->text();
    result_label.resize(result_label.size() - 1);
    ui->Result->setText(result_label);
  }
}

void Calculator::arithmetic() {
  QPushButton *button = (QPushButton *)sender();
  QString result_label = ui->Result->text();
  if (result_label == "Incorrect input") {
    ui->Result->setText("");
    result_label = ui->Result->text();
  }
  ui->Result->setText(result_label + button->text());
}

void Calculator::func() {
  QPushButton *button = (QPushButton *)sender();
  QString result_label = ui->Result->text();
  if (result_label == "Incorrect input") {
    ui->Result->setText("");
    result_label = ui->Result->text();
  }
  ui->Result->setText(result_label + button->text() + "(");
}

void Calculator::calculate() {
  QString str = ui->Result->text();
  str.replace(",", ".");
  str.replace(")(", ")*(");
  if (str.contains('x') && ui->Value->text() == "") {
    ui->Result->setText("Incorrect input");
  } else {
    if (str.contains('x')) str.replace("x", ui->Value->text());
    QByteArray bstr = str.toLocal8Bit();
    char *str_for_c = bstr.data();
    double result = 0;
    if (str == "" or str == "Incorrect input") {
      ui->Result->setText("Incorrect input");
    } else {
      if (controller(str_for_c, &result) == ERROR) {
        ui->Result->setText("Incorrect input");
      } else {
        ui->Result->setText(QString::number(result, 'g', 10));
      }
    }
  }
}

void Calculator::xPressed() {
  if (check) {
    check = false;
    timer->setSingleShot(true);
    timer->setInterval(250);
    timer->start();
  } else {
    check = true;
    if (timer->isActive()) {
      timer->stop();
      ui->stackedWidget->setCurrentIndex(1);
    }
  }
}

void Calculator::printX() {
  if (ui->Result->text() == "Incorrect input") {
    ui->Result->setText("");
  }
  check = true;
  ui->Result->setText(ui->Result->text() + "x");
}

void Calculator::backToCalc() { ui->stackedWidget->setCurrentIndex(0); }

void Calculator::makeGraph() {
  QString str = ui->Graph->text();
  if (str == "Incorrect input") {
    ui->Graph->setText("");
  } else if (double supp = 5 && !controller(str.replace("x", ui->Xmin_edit->text()).toLocal8Bit().data(), &supp)) {
    ui->Graph->setText("Incorrect input");
  } else {
    x.clear();
    y.clear();
    int Xmin = ui->Xmin_edit->text().toInt();
    int Xmax = ui->Xmax_edit->text().toInt();
    double step = 0.1;
    double Y;
    double X = (double)Xmin;
    double Ymin = 0;
    double Ymax = 0;
    while (X < (double)Xmax) {
      x.push_back(X);
      str = ui->Graph->text();
      str.replace("x", QString::number(X));
      QByteArray ba = str.toLocal8Bit();
      char *char_array = ba.data();
      controller(char_array, &Y);
      if (X == Xmin) {
        Ymin = Y;
        Ymax = Y;
      }
      if (Y < Ymin) Ymin = Y;
      if (Y > Ymax) Ymax = Y;
      y.push_back(Y);
      X += step;
      X = round(X * 10000000) / 10000000;
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->data()->clear();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->xAxis->setRange(Xmin, Xmax);
    ui->widget->yAxis->setRange(Ymin, Ymax);
    ui->widget->replot();
    ui->widget->setInteraction(QCP::iRangeZoom, true);
    ui->widget->setInteraction(QCP::iRangeDrag, true);
  }
}

void Calculator::toCredit() { ui->stackedWidget->setCurrentIndex(2); }

void Calculator::toDepos() { ui->stackedWidget->setCurrentIndex(3); }

void Calculator::backFromCredit() { ui->stackedWidget->setCurrentIndex(0); }

void Calculator::backFromDepos() { ui->stackedWidget->setCurrentIndex(0); }

void Calculator::fromCredToDep() { ui->stackedWidget->setCurrentIndex(3); }

void Calculator::fromDepToCred() { ui->stackedWidget->setCurrentIndex(2); }
