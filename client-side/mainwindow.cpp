//mainwindow.cpp  
#include "mainwindow.h"  
#include "ui_mainwindow.h"  
#define IP "192.168.1.106"  
#define port "4001"  

QString myid;
MainWindow::MainWindow(QWidget *parent) :  
    QMainWindow(parent),  
    ui(new Ui::MainWindow)  
{  
    ui->setupUi(this);  
    ui->lineEdit_Password->setEchoMode(QLineEdit::Password);  
	socket=new QTcpSocket(); 
	connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),  
            this,SLOT(displayError(QAbstractSocket::SocketError)));   //发生错误时执行displayError函数  
	connectServer();
}  
  
MainWindow::~MainWindow()  
{  
	this->socket->close();
    delete this->socket;  
    delete ui;  
}  

void MainWindow::connectServer(){
	//socket->abort();   //取消已有的连接  
    socket->connectToHost(IP,QString(port).toInt());  
    connect(socket,SIGNAL(readyRead()),this,SLOT(readMessages()));  
}

void MainWindow::on_pushButton_Login_clicked(){
	QString userName=ui->lineEdit_ID->text();  
    QString passward=ui->lineEdit_Password->text();  
	if(userName=="" || passward=="")  
        QMessageBox::information(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("输入不能为空"),QMessageBox::Ok); 
	else{
	QString login="l";  //表示登陆
	//QString myip=getHostIpAddress();
    QString data=login+"/"+userName+"/"+passward;  
    socket->write(data.toLatin1()); 
	}
}

void MainWindow::on_pushButton_Reg_clicked()  
{  
    qDebug() << "Register " ; 
	Register *r=new Register(this);
	r->show();
}  

void MainWindow::on_forgetbtn_clicked()
{
	qDebug() << "refind " ; 
	refind *f=new refind(this);
	f->show();
}

void MainWindow::readMessages(){
	QString data=socket->readAll();  
    QStringList list=data.split("/");  
    if(list[0]=="l" && list[1]=="true")  
        {
			/*QByteArray s;
		    s.resize(8);  s[0] = '1'; s[1] = '2'; s[2] = '\0'; s[3] = '\0'; s[4] = 'a'; s[5] = '1'; s[6] = '\0'; s[7] = '3'; 
			std::string str=s.toStdString();
			std::string st=std::string(str,4);
			QByteArray s1=QByteArray::fromStdString(st);*/
			
			myid=ui->lineEdit_ID->text();
			login *l=new login(this);
			connect(l,SIGNAL(closelogin()),this,SLOT(closeit()));
			l->setWindowTitle(myid);
			l->show();
			this->hide();
	}
    else if(list[0]=="l" && list[1]=="false")  
        QMessageBox::information(this,QString::fromLocal8Bit("信息提示"),QString::fromLocal8Bit("用户名或密码错误！"),QMessageBox::Ok);  
    else  
        return;  
}

void MainWindow::displayError(QAbstractSocket::SocketError)  
{  
    qDebug()<<socket->errorString();   //输出出错信息  
} 

void MainWindow::closeit(){
	this->close();
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