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
    bool loguser(QString ID,QString passward,QString ip);  //��½��Ϣ
	bool logout(QString ID);  //����
    bool signup(QString ID,QString passward,QString question,QString answer);  //ע��
    bool refind(QString ID,QString passward,QString question,QString answer);  //�����һ�
	QString gfriend(QString ID);   //������Ϣ
	QString forstate(QString ID);  //������Ϣ
	QString myport(QString ID);    //���˿�
	bool firstport(QString ID);     //���ε�½��ö˿ں�
	QString otherport(QString ID);  
	int get_qrand();
private:  
    QSqlQuery *query;  
};  
  
#endif // MYSQL_H  
