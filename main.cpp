#include "mainwindow.h"
#include <QtWidgets/QApplication>
//#include <QTextCodec>
#include "mysql.h" 
#include "message_sql.h"
int main(int argc, char *argv[])
{
	//QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
	QApplication a(argc, argv);
	MySql ms;  
    ms.initsql();  
	message_sql mes;
	mes.initsql();
	MainWindow w;
	w.setWindowTitle("Server");
	w.show();
	return a.exec();
}
