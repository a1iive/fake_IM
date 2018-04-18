#include "mainwindow.h"  
#include "ui_mainwindow.h"  
#include "mysql.h" 
#define port "4001"

MainWindow::MainWindow(QWidget *parent) :  
    QMainWindow(parent),  
    ui(new Ui::MainWindow)  
{  
    ui->setupUi(this);  
	init();  
  
}  
  
MainWindow::~MainWindow()  
{  
    server->close();  
    server->deleteLater();  
    delete ui;  
}  
 
void MainWindow::init(){
	server=new myserver(this);
	//socket=new QTcpSocket();
	//connect(server,SIGNAL(newConnection()),this,SLOT(acceptConnection()));  
}

void MainWindow::on_pushButton_Listen_clicked()  
{  
    if(ui->pushButton_Listen->text() == QString::fromLocal8Bit("开启服务器"))  
    {  
        //监听指定的端口  
        while(!server->isListening()&&!server->listen(QHostAddress::Any, QString(port).toInt()))  
        {  
            //若出错，则输出错误信息  
            qDebug()<<server->errorString();  
            return;  
        }  
		ui->pushButton_Listen->setEnabled(false);
    }   
}  
  
/* QString MainWindow::getHostIpAddress()  
{  
    QString strIpAddress;  
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();  
    // 获取第一个本主机的IPv4地址  
    int nListSize = ipAddressesList.size();  
    for (int i = 0; i < nListSize; ++i)  
    {  
           if (ipAddressesList.at(i) != QHostAddress::LocalHost &&  
               ipAddressesList.at(i).toIPv4Address()) {  
               strIpAddress = ipAddressesList.at(i).toString();  
               break;  
           }  
     }  
     // 如果没有找到，则以本地IP地址为IP  
     if (strIpAddress.isEmpty())  
        strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();  
     return strIpAddress;  
}  */


  

