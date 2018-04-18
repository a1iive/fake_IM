#include "message_sql.h"  
  
message_sql::message_sql()  
{  
  
}  
  
void message_sql::initsql()  
{  
    QSqlDatabase db; 
	if (QSqlDatabase::contains("qt_sql_default_connection"))
	{
		db = QSqlDatabase::database("qt_sql_default_connection");
	}
	else
	{
		db = QSqlDatabase::addDatabase("QSQLITE");
		db.setHostName("192.168.116.1"); 
		db.setDatabaseName("message.db");
		db.setUserName("huhaosheng");
		db.setPassword("123456");
	}
    if(db.open())  
        {  
            qDebug()<<"Database connected successfully!";  
            createtable();  
            return;  
        }  
    else  
        {  
            qDebug()<<"Database connected failed!";  
            return;  
        }  
}  
  
void message_sql::createtable()  
{  
    query=new QSqlQuery; ;
	QString create_sql="create table message(id INTEGER PRIMARY KEY,name_get varchar(30),name_send varchar(30),data varchar(300))";
	query->prepare(create_sql);
	if(!query->exec())
	{
		qDebug() << "Error: Fail to create table." << query->lastError();
	}
	else
	{
		qDebug() << "Table created!";
	}
}  

bool message_sql::send_message(QString name_get,QString name_send,QString data){ //有人发来离线消息
	QString str=QString("insert into message values(null,'%1','%2','%3')").arg(name_get).arg(name_send).arg(data);
	query=new QSqlQuery;  
    return query->exec(str);  
}

QString message_sql::get_message(QString name_get){  //有人上线，将离线消息给他
	QString data="get_off_mess/";
    QString str=QString("select * from message ");  
	query=new QSqlQuery;  
    query->exec(str);  
    while(query->next())
    {
        QString s1 = query->value(1).toString();
		QString s2 = query->value(2).toString();
		QString s3 = query->value(3).toString();
		if(s1==name_get)data=data+s2+":"+s3+"\n";
    }
	QString delete_sql=QString("delete from message where name_get=:name_get");
	query=new QSqlQuery;   
	query->prepare(delete_sql);
	query->bindValue(":name_get", name_get);
	query->exec();  
	return data;
}