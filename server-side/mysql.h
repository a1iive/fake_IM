#ifndef MYSQL_H  
#define MYSQL_H  
  
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>  
#include <QtGlobal>
#include <QTime>
#include <QCryptographicHash>
class MySql  
{  
public:  
    MySql();  
    void initsql();  
    void createtable();  
    bool loguser(QString ID,QString passward,QString ip);  //登陆信息
	bool logout(QString ID);  //下线
    bool signup(QString ID,QString passward,QString question,QString answer);  //注册
    bool refind(QString ID,QString passward,QString question,QString answer);  //密码找回
	QString gfriend(QString ID);   //好友信息
	QString forstate(QString ID);  //在线信息
	QString myport(QString ID);    //本端口
	bool firstport(QString ID);     //初次登陆获得端口号
	QString otherport(QString ID);  
	int get_qrand();
private:  
    QSqlQuery *query;  
};  
  
#endif // MYSQL_H  
