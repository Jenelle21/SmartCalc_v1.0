#include <QApplication>

#include "../include/calculator.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Calculator w;
  w.setWindowTitle("Calculator v1.0");
  w.show();
  return a.exec();
}
