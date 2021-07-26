// #include "mainwindow.h"
#include <parser.h>
// #include <QApplication>

// int main(int argc, char* argv[]) {
//  QApplication a(argc, argv);
//  MainWindow w;
//  w.show();
//  return a.exec();
//}

auto main(int argc, char** argv) -> int {
  auto parser = Parser();
  parser.set("![114514](www.tiansuo.com)**a**$$x+1$$*a+aaa*");
  auto p = parser.parse();
}
