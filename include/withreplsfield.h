#ifndef INCLUDE_WITHREPLSFIELD_H_
#define INCLUDE_WITHREPLSFIELD_H_

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

#endif  // INCLUDE_WITHREPLSFIELD_H_
