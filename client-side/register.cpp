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

	//socket����
	connectServer();
	 
}  
  
Register::~Register()  
{  
	this->socket->close();
    delete this->socket;  
    delete ui;  
}  

void Register::connectServer(){
	//socket->abort();   //ȡ�����е�����  
    socket->connectToHost(IP,QString(port).toInt());  
    connect(socket,SIGNAL(readyRead()),this,SLOT(readMessages()));  
}

void Register::on_pushButton_Sure_clicked(){
	QString userName=ui->lineEdit_ID->text();  
    QString passward=ui->lineEdit_Pass->text();  
	QString question=ui->comboBox->currentText();
	QString answer=ui->lineEdit->text();
	if(userName==""||passward==""||answer=="")  
        QMessageBox::information(this,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("���벻��Ϊ��"),QMessageBox::Ok);  
	else{
	QString sign="s";  //��ʾע��
    QString data=sign+"/"+userName+"/"+passward+"/"+question+"/"+answer;  
    socket->write(data.toLatin1());  
	}
}

void Register::readMessages(){
	QString data=socket->readAll();  
    QStringList list=data.split("/");  
    if(list[0]=="s" && list[1]=="true")  
        QMessageBox::information(this,QString::fromLocal8Bit("��Ϣ��ʾ"),QString::fromLocal8Bit("ע��ɹ�!"),QMessageBox::Ok);  
    else if(list[0]=="s" && list[1]=="false")  
        QMessageBox::information(this,QString::fromLocal8Bit("��Ϣ��ʾ"),QString::fromLocal8Bit("ע��ʧ��,�û����Ѿ���ע��!"),QMessageBox::Ok);  
    else  
        return;  
}