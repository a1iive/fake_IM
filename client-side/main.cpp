#include "mainwindow.h"
#include <QtWidgets/QApplication>
//#include <QTextCodec>

int main(int argc, char *argv[])
{
	//QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
	QApplication a(argc, argv);
	MainWindow w;
	w.setWindowTitle("Client");
	w.show();
	return a.exec();
}
