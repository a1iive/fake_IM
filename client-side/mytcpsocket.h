#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H
#include<QTcpSocket>  
  
  
class mytcpsocket :public QTcpSocket  
{  
    Q_OBJECT  
public:  
    explicit mytcpsocket(qintptr socketDescriptor, QObject *parent = 0);  
signals:
	void SocketReadyRead(qintptr SocketID, QString IP, int port, QByteArray data);
	void SocketDisConnect(qintptr SocketID, QString IP, int port);
private:
	qintptr SocketID;

private slots:
	void ReadData();
	void DisConnect();
	void displayError(QAbstractSocket::SocketError);
};
   
#endif // MYTCPSOCKET_H  