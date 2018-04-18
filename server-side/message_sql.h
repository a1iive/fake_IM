#ifndef MESSAGE_SQL_H  
#define MESSAGE_SQL_H  
  
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDebug>  
#include <QtGlobal>
#include <QTime>

class message_sql  
{  
public:  
    message_sql();  
    void initsql();  
    void createtable();  
	bool send_message(QString,QString,QString);//���˷�������Ϣ
	QString get_message(QString name_get);//��������Ϣ����ȥ
private:  
    QSqlQuery *query;  
};  
  
#endif // MESSAGE_SQL_H  