#include "register.h"
#include "ui_register.h" 

#define IP "192.168.1.106"  
#define port "4001"  
Register::Register(QWidget *parent) :  
    QMainWindow(parent),  
    ui(new Ui::Register)  
{  
    ui->setupUi(this);  
    ui->lineEdit_Pass->setEchoMode(QLineEdit::Password);
    socket = new QTcpSocket(); 

	//socket连接
	connectServer();
	 
}  
  
Register::~Register()  
{  
	this->socket->close();
    delete this->socket;  
    delete ui;  
}  

void Register::connectServer(){
	//socket->abort();   //取消已有的连接  
    socket->connectToHost(IP,QString(port).toInt());  
    connect(socket,SIGNAL(readyRead()),this,SLOT(readMessages()));  
}

void Register::on_pushButton_Sure_clicked(){
	QString userName=ui->lineEdit_ID->text();  
    QString passward=ui->lineEdit_Pass->text();  
	QString question=ui->comboBox->currentText();
	QString answer=ui->lineEdit->text();
	if(userName==""||passward==""||answer=="")  
        QMessageBox::information(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("输入不能为空"),QMessageBox::Ok);  
	else{
	QString sign="s";  //表示注册
    QString data=sign+"/"+userName+"/"+passward+"/"+question+"/"+answer;  
    socket->write(data.toLatin1());  
	}
}

void Register::readMessages(){
	QString data=socket->readAll();  
    QStringList list=data.split("/");  
    if(list[0]=="s" && list[1]=="true")  
        QMessageBox::information(this,QString::fromLocal8Bit("信息提示"),QString::fromLocal8Bit("注册成功!"),QMessageBox::Ok);  
    else if(list[0]=="s" && list[1]=="false")  
        QMessageBox::information(this,QString::fromLocal8Bit("信息提示"),QString::fromLocal8Bit("注册失败,用户名已经被注册!"),QMessageBox::Ok);  
    else  
        return;  
}