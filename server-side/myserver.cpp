#include"myserver.h"  
#include<QMessageBox>  


int myserver::counts=0;
myserver::myserver(QObject * parent):QTcpServer(parent){  
  
  
}  
void myserver::incomingConnection(qintptr socketDescriptor)  //重写该虚函数
{  
	mytcpsocket* tcpsocket = new mytcpsocket(socketDescriptor);
	connect(tcpsocket, SIGNAL(SocketReadyRead(qintptr , QString  )), this, SLOT(receiveData(qintptr , QString )));//底层套接字信号触发槽函数读数据
	connect(tcpsocket, SIGNAL(SocketDisConnect()), this, SLOT(DisConnect()));
	connect(tcpsocket, SIGNAL(aboutToClose()), this, SLOT(deleteLater()));//套接字关闭，延迟删除对象
	sockethash.insert(socketDescriptor, tcpsocket);//保存每个连接套接字的信息
	counts++;

} 


void myserver::receiveData(qintptr SocketID,QString data)
{
    mytcpsocket* socket=sockethash.value(SocketID);
	QHash<qintptr,mytcpsocket*>::iterator i;
    QStringList list=data.split("/");
    bool ret=0;
    if(list[0]=="s")     //注册  
        ret=checkSignUp(list[1],list[2],list[3],list[4]);  
    else if(list[0]=="l")  //登录  
        ret=checkSignIn(list[1],list[2],socket->peerAddress ().toString()); 
	else if(list[0]=="r")     //密码找回  
        ret=checkrefind(list[1],list[2],list[3],list[4]); 
	else if(list[0]=="w")     //加载好友面板  
        {
			socket->write(gfriend(list[1]).toLatin1());
			return;
	}
	else if(list[0]=="first_myport"){ //初次登录创建端口号
		firstport(list[1]);
		return;
	}
	else if(list[0]=="o")     //有人下线
	{
		logout(list[1]);
		return;
	}
	else if(list[0]=="state") //有人上线，寻求好友列表信息
	{
		socket->write(forstate(list[1]).toLatin1());
		return;
	}
	else if(list[0]=="myport") //更新端口号
	{
		socket->write(getmyport(list[1]).toLatin1());
		return;
	}
	else if(list[0]=="otherport") //获得对等方端口号
	{
		socket->write(getotherport(list[1]).toLatin1());
		return;
	}
	else if(list[0]=="file")  //聊天时，第一步操作为发文件时寻求对方端口号
	{
		socket->write(getfileport(list[1]).toLatin1());
		return;
	}
	else if(list[0]=="read_file") //聊天时，第一步操作为收文件时寻求对方端口号
	{
		socket->write(getread_fileport(list[1]).toLatin1());
		return;
	}
	else if(list[0]=="send_off_mess") //有人发离线消息
	{
		socket->write(send_off_message(list[1],list[2],list[3]).toLatin1());
		return;
	}
	else if(list[0]=="get_off_mess")  //有人上线，将离线消息给他
	{
		socket->write(get_off_message(list[1]).toLatin1());
		return;
	}
    else  
        return;
    QString sendData=list[0];
    if(ret)
        sendData+="/true";
    else
        sendData+="/false";
    socket->write(sendData.toLatin1());
}

bool myserver::checkSignIn(QString ID,QString passward,QString ip)
{

    MySql *mysql=new MySql();
    bool ret=mysql->loguser(ID,passward,ip);
    return ret;
}
bool myserver::logout(QString ID){
	MySql *mysql=new MySql();
    bool ret=mysql->logout(ID);
    return ret;
}
bool myserver::checkSignUp(QString ID, QString passward,QString question,QString answer)
{
    MySql *mysql=new MySql();
    bool ret=mysql->signup(ID,passward,question,answer);
    return ret;
}

bool myserver::checkrefind(QString ID, QString passward,QString question,QString answer)
{
	MySql *mysql=new MySql();
    bool ret=mysql->refind(ID,passward,question,answer);
    return ret;
}

QString myserver::gfriend(QString ID){
	MySql *mysql=new MySql();
    QString data=mysql->gfriend(ID);
	return data;
}

QString myserver::forstate(QString ID){
	MySql *mysql=new MySql();
    QString data=mysql->forstate(ID);
	return data;
}

bool myserver::firstport(QString ID){
	MySql *mysql=new MySql();
    bool ret=mysql->firstport(ID);
	return ret;
}

QString myserver::getmyport(QString ID){
	MySql *mysql=new MySql();
    QString data=mysql->myport(ID);
	return data;
}

QString myserver::getotherport(QString ID){
	MySql *mysql=new MySql();
	QString str="otherport";
    QString data=str+"/"+mysql->otherport(ID);
	return data;
}

QString myserver::getfileport(QString ID){
	MySql *mysql=new MySql();
	QString str="file";
    QString data=str+"/"+mysql->otherport(ID);
	return data;
}

QString myserver::getread_fileport(QString ID){
	MySql *mysql=new MySql();
	QString str="read_file";
    QString data=str+"/"+mysql->otherport(ID);
	return data;
}


QString myserver::send_off_message(QString name_get,QString name_send,QString data){
	message_sql *mes_sql=new message_sql();
	bool ret=mes_sql->send_message(name_get,name_send,data);
	if(ret){
		QString data="send_off_mess/true";
		return data;
	}
	else {
		QString data="send_off_mess/false";
		return data;
	}
}

QString myserver::get_off_message(QString name_get){
	message_sql *mes_sql=new message_sql();
	QString data=mes_sql->get_message(name_get);
	return data;
}
void myserver::DisConnect(int serverSocketID)
{
	sockethash.remove(serverSocketID);//断开连接的时候，移除端口号
	counts--;
	
}

