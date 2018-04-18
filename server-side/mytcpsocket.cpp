#include"mytcpsocket.h"  
#include<QByteArray>  
#include<QDataStream>  
#include<QString>  
#include<QMessageBox>  
#include<QDebug>  
#define IP "192.168.116.1"  
#define port 4001

mytcpsocket::mytcpsocket(qintptr socketDescriptor, QObject *parent ):QTcpSocket(parent),SocketID(socketDescriptor) 
{  
  
    //connect(this,SIGNAL(),this,SLOT(on_connected()));  
	this->setSocketDescriptor(socketDescriptor);
	connect(this, SIGNAL(readyRead()), this, SLOT(ReadData()));
	connect(this, SIGNAL(disconnected()), this, SLOT(DisConnect()));
	connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));
	connect(this,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));
}


void mytcpsocket::ReadData()//连接套接字接受数据，向上层传送
{
	
	QString data = this->readAll();
	//信号上传连接套接字
	emit SocketReadyRead(this->SocketID, data);
}

void mytcpsocket::DisConnect()
{
	//信号上传
	emit SocketDisConnect(this->SocketID);
}

void mytcpsocket::displayError(QAbstractSocket::SocketError)
{
	this->disconnectFromHost();
}
