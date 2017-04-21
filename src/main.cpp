#include "ShaderParser.h"
#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QCommandLineParser>

int main(int argc, char* argv[])
{
  // make an instance of the QApplication
  QApplication a(argc, argv);
  // process command line and pass and .oso files to MainWindow
  QCommandLineParser parser;
  parser.process(a);
  const QStringList args = parser.positionalArguments().filter(".oso");

  // Create a new MainWindow
  MainWindow w(args);
  // show it
  w.show();
  // hand control over to Qt framework
  return a.exec();
}

