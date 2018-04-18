//mainwindow.h  
#ifndef MAINWINDOW_H  
#define MAINWINDOW_H  
#include <QtWidgets/QMainWindow>  
#include <QtNetwork/QTcpSocket>  
#include <QtNetwork>
#include <qstring.h>
#include "register.h" 
#include "refind.h "
#include "login.h"

namespace Ui {  
class MainWindow;  
}  
  
class MainWindow : public QMainWindow  
{  
    Q_OBJECT  
  
public:  
    explicit MainWindow(QWidget *parent = 0);  
    ~MainWindow(); 
protected:   
    void connectServer();  
	//QString getHostIpAddress() ;
	//void closeEvent(QCloseEvent *e);
private slots:  
    //°´Å¥²Ûº¯Êý
    void on_pushButton_Login_clicked();  
    void on_pushButton_Reg_clicked();  
	void on_forgetbtn_clicked();
	//socket²Ûº¯Êý
    void displayError(QAbstractSocket::SocketError);  
	void readMessages(); 
	void closeit();
private:  
    Ui::MainWindow *ui;  
	//Register r;
	//refind f;
	QTcpSocket *socket;
      
};  
  
#endif // MAINWINDOW_H  