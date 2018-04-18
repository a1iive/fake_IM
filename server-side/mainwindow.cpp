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
    if(ui->pushButton_Listen->text() == QString::fromLocal8Bit("����������"))  
    {  
        //����ָ���Ķ˿�  
        while(!server->isListening()&&!server->listen(QHostAddress::Any, QString(port).toInt()))  
        {  
            //�����������������Ϣ  
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
    // ��ȡ��һ����������IPv4��ַ  
    int nListSize = ipAddressesList.size();  
    for (int i = 0; i < nListSize; ++i)  
    {  
           if (ipAddressesList.at(i) != QHostAddress::LocalHost &&  
               ipAddressesList.at(i).toIPv4Address()) {  
               strIpAddress = ipAddressesList.at(i).toString();  
               break;  
           }  
     }  
     // ���û���ҵ������Ա���IP��ַΪIP  
     if (strIpAddress.isEmpty())  
        strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();  
     return strIpAddress;  
}  */


  

