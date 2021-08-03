#include "mainwindow.h"
#include <parser.h>
#include <translator.h>
#include <QApplication>

 int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}

//auto main(int argc, char** argv) -> int {
//  auto parser = std::shared_ptr<IParser>(new Parser());
//  auto translator = std::shared_ptr<ITranslator>(new Translator());

//  parser->set( // Begin
//      "# C\n"
//      "> author: `Iori`\nlink: [github](github.com)\n"
//      "## code\nabaaba\n"
//      "+ as we can write in a editor\n"
//      "+ write code\n"
//      "   + deploy\n"
//      "```\n"
//      "#include <stdio.h>\n"
//      "int main() {\n"
//      "printf(\"Hello, world\\n\");"
//      "}\n"
//      "```\n"
//      "This is a simple C program ## fff\n"
//      "1. C\n"
//      "2. Java\n"
//      "3. `Python`" // EOF
//  );
//  auto parsed = parser->parse();
//  auto s = translator->translate(parsed);

//  std::cout << s;
//}
