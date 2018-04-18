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
	bool send_message(QString,QString,QString);//有人发离线消息
	QString get_message(QString name_get);//将离线消息传出去
private:  
    QSqlQuery *query;  
};  
  
#endif // MESSAGE_SQL_H  