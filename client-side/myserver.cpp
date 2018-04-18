#include"myserver.h"  
#include<QMessageBox>  
#include"mytcpsocket.h"    
#include"chat.h"
int myserver::counts=0;
myserver::myserver(QObject * parent):QTcpServer(parent){  
  
  
}  
void myserver::incomingConnection(qintptr socketDescriptor)  //重写该虚函数
{  
	mytcpsocket* tcpsocket = new mytcpsocket(socketDescriptor);
	connect(tcpsocket, SIGNAL(SocketReadyRead(qintptr , QString , int , QByteArray )), this, SLOT(receiveData(qintptr , QString , int , QByteArray)));//底层套接字信号触发槽函数读数据
	connect(tcpsocket, SIGNAL(SocketDisConnect()), this, SLOT(DisConnect()));//底层有对应的函数，层层上传
	connect(tcpsocket, SIGNAL(aboutToClose()), this, SLOT(deleteLater()));//套接字关闭，延迟删除对象
	sockethash.insert(socketDescriptor, tcpsocket);//保存每个连接套接字的信息
	counts++;
	//发射信号 biu~
	//emit hasConnect(serverSocketID, serverSocket->peerAddress().toString(), serverSocket->peerPort());
} 

void myserver::receiveData(qintptr SocketID, QString IP, int port, QByteArray data){
	mytcpsocket* socket=sockethash.value(SocketID);
	
	emit getdata(SocketID,IP,port,data);


}


void myserver::DisConnect(int serverSocketID, QString IP, int Port)
{
	sockethash.remove(serverSocketID);//断开连接的时候，移除端口号
	counts--;
	//emit hasDisConnect(serverSocketID, IP, Port);//发送断开连接的信号了
}

