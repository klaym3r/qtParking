#include "widget.h"

#include <cmath>

#include <QApplication>
#include <QString>
#include <QVector>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  Widget w;
  const int wx = w.getWx();
  const int wy = w.getWy();
  w.setFixedSize(wx, wy);

  w.setSlot();
  w.setCar();
  w.parking();

  w.show();
  return a.exec();
}
