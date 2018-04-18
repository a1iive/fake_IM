//mainwindow.h  
#ifndef MAINWINDOW_H  
#define MAINWINDOW_H  
  
#include <QtWidgets/QMainWindow>  
#include <QtNetwork/QTcpServer>  
#include <QtNetwork/QTcpSocket>  
#include <QtNetwork>
#include"myserver.h"
namespace Ui {  
class MainWindow;  
}  
  
class MainWindow : public QMainWindow  
{  
    Q_OBJECT  
  
public:  
    explicit MainWindow(QWidget *parent = 0);  
    ~MainWindow(); 
	//bool checkSignIn(QString ID,QString passward);  
    //bool checkSignUp(QString ID, QString passward,QString question,QString answer);  

protected:  
    void init();    
	//QString getHostIpAddress() ;
private slots:  
    void on_pushButton_Listen_clicked();  
  
private:  
    Ui::MainWindow *ui;  

	myserver *server;
};  
  
#endif // MAINWINDOW_H  