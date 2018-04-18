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

	//socket����
	connectServer();
	 
}  
  
refind::~refind()  
{  
	this->socket->close();
    delete this->socket;  
    delete ui;  
}  

void refind::connectServer(){
	//socket->abort();   //ȡ�����е�����  
    socket->connectToHost(IP,QString(port).toInt());  
    connect(socket,SIGNAL(readyRead()),this,SLOT(readMessages()));  
}

void refind::on_surebtn_clicked(){
	QString userName=ui->lineEdit->text();  
    QString passward=ui->lineEdit_3->text();  
	QString question=ui->comboBox->currentText();
	QString answer=ui->lineEdit_2->text();
	if(userName==""||passward==""||answer=="")  
        QMessageBox::information(this,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("���벻��Ϊ��"),QMessageBox::Ok);  
	else{
	QString sign="r";  //��ʾ�����һ�
    QString data=sign+"/"+userName+"/"+passward+"/"+question+"/"+answer;  
    socket->write(data.toLatin1());  
	}
}

void refind::readMessages(){
	QString data=socket->readAll();  
    QStringList list=data.split("/");  
    if(list[0]=="r" && list[1]=="true")  
        QMessageBox::information(this,QString::fromLocal8Bit("��Ϣ��ʾ"),QString::fromLocal8Bit("�������޸ĳɹ�!"),QMessageBox::Ok);  
    else if(list[0]=="r" && list[1]=="false")  
        QMessageBox::information(this,QString::fromLocal8Bit("��Ϣ��ʾ"),QString::fromLocal8Bit("�������޸�ʧ��,��Ϣ����ȷ��"),QMessageBox::Ok);  
    else  
        return;  
}