#include "../include/withreplsfield.h"

#include "ui_withreplsfield.h"

WithReplsField::WithReplsField(QWidget *parent)
    : QWidget(parent), ui(new Ui::WithReplsField) {
  ui->setupUi(this);

  ui->dateEdit->calendarWidget()->setFirstDayOfWeek(Qt::Monday);
  ui->dateEdit->setDate(QDate::currentDate());
  ui->dateEdit->setDisplayFormat("dd.MM.yyyy");
  connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(deleteField()));
}

WithReplsField::~WithReplsField() { delete ui; }

QDate WithReplsField::getDateFromField() { return ui->dateEdit->date(); }

double WithReplsField::getValueFromField() {
  return ui->lineEdit->text().toDouble();
}

void WithReplsField::deleteField() {
  emit closeThisField(fieldNumber);
  this->close();
}
