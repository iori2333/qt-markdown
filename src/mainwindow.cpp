#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <page.h>
#include <QWebChannel>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), parser(new Parser),
      translator(new Translator) {
  ui->setupUi(this);
  ui->viewer->setContextMenuPolicy(Qt::NoContextMenu);

  auto page = new Page(this);
  ui->viewer->setPage(page);

  connect(ui->editor, &QPlainTextEdit::textChanged, this,
          &MainWindow::on_plainTextEdit_textChanged);

  auto channel = new QWebChannel(this);
  channel->registerObject(QStringLiteral("content"), &content);
  page->setWebChannel(channel);

  ui->viewer->setUrl(QUrl("qrc:/index.html"));
}

MainWindow::~MainWindow() {
  delete ui;
  delete parser;
  delete translator;
}

void MainWindow::on_actionSave_triggered() {}

void MainWindow::on_actionClose_triggered() {}

void MainWindow::on_actionAbout_triggered() {}

void MainWindow::on_actionAbout_Qt_triggered() {}

void MainWindow::on_plainTextEdit_textChanged() {
  auto text = ui->editor->toPlainText().toStdString();
  parser->set(text);
  auto out = translator->translate(parser->parse());

  content.setText(QString::fromStdString(out));
  std::cout << out << std::endl;
}
