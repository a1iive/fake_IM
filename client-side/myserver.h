#ifndef MYSERVER_H  
#define MYSERVER_H  
#include<QObject>  
#include<QTcpServer>  
#include<QWidget>  
#include<QHash>
#include"mytcpsocket.h" 

class myserver :public QTcpServer{  
    Q_OBJECT  
public:  
    explicit myserver(QObject * parent);
	static int counts;
protected:  
    virtual void incomingConnection(qintptr socketDescriptor);  
private slots:
	void receiveData(qintptr SocketID, QString IP, int port, QByteArray data);
	void DisConnect(int serverSocketID, QString IP, int Port);
private:
	QHash<qintptr,mytcpsocket*> sockethash;
signals:
	void getdata(qintptr SocketID, QString IP, int port, QByteArray data);
  
};  
//|定义的结束 必须加;  
#endif // MYSERVER_H