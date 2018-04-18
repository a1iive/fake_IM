#include "refind.h"
#include "ui_refind.h" 

#define IP "192.168.1.106"  
#define port "4001"  
refind::refind(QWidget *parent) :  
    QMainWindow(parent),  
    ui(new Ui::refind)  
{  
    ui->setupUi(this);  
    ui->lineEdit_3->setEchoMode(QLineEdit::Password);
    socket = new QTcpSocket(); 

	//socket连接
	connectServer();
	 
}  
  
refind::~refind()  
{  
	this->socket->close();
    delete this->socket;  
    delete ui;  
}  

void refind::connectServer(){
	//socket->abort();   //取消已有的连接  
    socket->connectToHost(IP,QString(port).toInt());  
    connect(socket,SIGNAL(readyRead()),this,SLOT(readMessages()));  
}

void refind::on_surebtn_clicked(){
	QString userName=ui->lineEdit->text();  
    QString passward=ui->lineEdit_3->text();  
	QString question=ui->comboBox->currentText();
	QString answer=ui->lineEdit_2->text();
	if(userName==""||passward==""||answer=="")  
        QMessageBox::information(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit("输入不能为空"),QMessageBox::Ok);  
	else{
	QString sign="r";  //表示密码找回
    QString data=sign+"/"+userName+"/"+passward+"/"+question+"/"+answer;  
    socket->write(data.toLatin1());  
	}
}

void refind::readMessages(){
	QString data=socket->readAll();  
    QStringList list=data.split("/");  
    if(list[0]=="r" && list[1]=="true")  
        QMessageBox::information(this,QString::fromLocal8Bit("信息提示"),QString::fromLocal8Bit("新密码修改成功!"),QMessageBox::Ok);  
    else if(list[0]=="r" && list[1]=="false")  
        QMessageBox::information(this,QString::fromLocal8Bit("信息提示"),QString::fromLocal8Bit("新密码修改失败,信息不正确！"),QMessageBox::Ok);  
    else  
        return;  
}