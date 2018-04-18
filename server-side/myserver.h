#ifndef MYSERVER_H  
#define MYSERVER_H  
#include<QObject>  
#include<QTcpServer>  
#include<QWidget>  
#include<QHash>
#include"mytcpsocket.h" 
#include"mytcpsocket.h"    
#include "mysql.h"
#include "message_sql.h"
class myserver :public QTcpServer{  
    Q_OBJECT  
public:  
    explicit myserver(QObject * parent);
	bool checkSignIn(QString ID,QString passward,QString ip);  //��¼
	bool logout(QString ID);         //����
    bool checkSignUp(QString ID, QString passward,QString question,QString answer); //ע��
	bool checkrefind(QString ID, QString passward,QString question,QString answer);  //�һ�����
	QString gfriend(QString ID); //��ȡ�����б�
	QString forstate(QString ID);//��ȡ����״̬��ip
	QString getmyport(QString ID);//��ȡ���ͻ��˶˿�
	bool firstport(QString ID);
	QString getotherport(QString ID);//��ȡ�Է��ͻ��˶˿�
	QString getfileport(QString ID);//��һ�η����ļ�
	QString getread_fileport(QString ID);//��һ�ν����ļ�
	QString send_off_message(QString,QString,QString);//���˷���������Ϣ
	QString get_off_message(QString);//��������Ϣ��������
	static int counts;
protected:  
    virtual void incomingConnection(qintptr socketDescriptor);  
private slots:
	void receiveData(qintptr SocketID, QString data);
	void DisConnect(int serverSocketID);
private:
	QHash<qintptr,mytcpsocket*> sockethash;

  
};  
//|����Ľ��� �����;  
#endif // MYSERVER_H