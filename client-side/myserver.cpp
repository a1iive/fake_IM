#include"myserver.h"  
#include<QMessageBox>  
#include"mytcpsocket.h"    
#include"chat.h"
int myserver::counts=0;
myserver::myserver(QObject * parent):QTcpServer(parent){  
  
  
}  
void myserver::incomingConnection(qintptr socketDescriptor)  //��д���麯��
{  
	mytcpsocket* tcpsocket = new mytcpsocket(socketDescriptor);
	connect(tcpsocket, SIGNAL(SocketReadyRead(qintptr , QString , int , QByteArray )), this, SLOT(receiveData(qintptr , QString , int , QByteArray)));//�ײ��׽����źŴ����ۺ���������
	connect(tcpsocket, SIGNAL(SocketDisConnect()), this, SLOT(DisConnect()));//�ײ��ж�Ӧ�ĺ���������ϴ�
	connect(tcpsocket, SIGNAL(aboutToClose()), this, SLOT(deleteLater()));//�׽��ֹرգ��ӳ�ɾ������
	sockethash.insert(socketDescriptor, tcpsocket);//����ÿ�������׽��ֵ���Ϣ
	counts++;
	//�����ź� biu~
	//emit hasConnect(serverSocketID, serverSocket->peerAddress().toString(), serverSocket->peerPort());
} 

void myserver::receiveData(qintptr SocketID, QString IP, int port, QByteArray data){
	mytcpsocket* socket=sockethash.value(SocketID);
	
	emit getdata(SocketID,IP,port,data);


}


void myserver::DisConnect(int serverSocketID, QString IP, int Port)
{
	sockethash.remove(serverSocketID);//�Ͽ����ӵ�ʱ���Ƴ��˿ں�
	counts--;
	//emit hasDisConnect(serverSocketID, IP, Port);//���ͶϿ����ӵ��ź���
}

