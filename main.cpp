#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  a.setStyle(QStyleFactory::create("Fusion"));

  QPalette p= a.palette();
  p.setColor(QPalette::Window,      QColor(53,53,53));
  p.setColor(QPalette::Button,      QColor(53,53,53));
  p.setColor(QPalette::Highlight,   QColor(142,45,197));
  p.setColor(QPalette::ButtonText,  QColor(255,255,255));
  a.setPalette(p);

  MainWindow w;
  w.show();

  return a.exec();
}
