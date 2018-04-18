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
	bool checkSignIn(QString ID,QString passward,QString ip);  //登录
	bool logout(QString ID);         //下线
    bool checkSignUp(QString ID, QString passward,QString question,QString answer); //注册
	bool checkrefind(QString ID, QString passward,QString question,QString answer);  //找回密码
	QString gfriend(QString ID); //获取好友列表
	QString forstate(QString ID);//获取在线状态和ip
	QString getmyport(QString ID);//获取本客户端端口
	bool firstport(QString ID);
	QString getotherport(QString ID);//获取对方客户端端口
	QString getfileport(QString ID);//第一次发送文件
	QString getread_fileport(QString ID);//第一次接收文件
	QString send_off_message(QString,QString,QString);//有人发送离线消息
	QString get_off_message(QString);//将离线消息给上线者
	static int counts;
protected:  
    virtual void incomingConnection(qintptr socketDescriptor);  
private slots:
	void receiveData(qintptr SocketID, QString data);
	void DisConnect(int serverSocketID);
private:
	QHash<qintptr,mytcpsocket*> sockethash;

  
};  
//|定义的结束 必须加;  
#endif // MYSERVER_H