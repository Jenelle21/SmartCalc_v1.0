#ifndef WITHREPLSFIELD_H
#define WITHREPLSFIELD_H

#include <QCalendarWidget>
#include <QWidget>

namespace Ui {
class WithReplsField;
}

class WithReplsField : public QWidget {
  Q_OBJECT

 public:
  explicit WithReplsField(QWidget *parent = nullptr);
  ~WithReplsField();
  int fieldNumber;

 public slots:
  QDate getDateFromField();
  double getValueFromField();

 private:
  Ui::WithReplsField *ui;

 private slots:
  void deleteField();

 signals:
  void closeThisField(int);
};

#endif  // WITHREPLSFIELD_H
