#include"mytcpsocket.h"  
#include<QByteArray>  
#include<QDataStream>  
#include<QString>  
#include<QMessageBox>  
#include<QDebug>  
#define IP "192.168.1.106"  
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


void mytcpsocket::ReadData()//连接套接字接受数据，向服务器传送
{
	//_sleep(100);
	QByteArray data;  
    //读取缓冲区数据  
    data = this->readAll();  
	//信号上传服务器层
	emit SocketReadyRead(this->SocketID, IP, port, data);
}

void mytcpsocket::DisConnect()
{
	//信号上传
	emit SocketDisConnect(this->SocketID,IP,port);
}

void mytcpsocket::displayError(QAbstractSocket::SocketError)
{
	this->disconnectFromHost();
}
