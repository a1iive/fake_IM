#include "mysql.h"  
  
MySql::MySql()  
{  
  
}  
  
void MySql::initsql()  //数据库初始化
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
		db.setDatabaseName("User.db");
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
  
void MySql::createtable()  //创建用户信息表
{  
    query=new QSqlQuery; 
	QString create_sql="create table user(ID VARCHAR(40) PRIMARY KEY UNIQUE NOT NULL,passward VARCHAR(40),question VARCHAR(40),answer VARCHAR(40),state VARCHAR(40),ord VARCHAR(40),itip VARCHAR(40))";
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
  
  
bool MySql::loguser(QString ID, QString passward,QString ip)  //登录验证
{  //加密
	QString md5_1;  
	QString pwd=passward;  
	QByteArray bb;  
	bb = QCryptographicHash::hash ( pwd.toLatin1(), QCryptographicHash::Md5 );  
	md5_1.append(bb.toHex());  
	int flag=0;
    QString str=QString("select * from user ");  
    query=new QSqlQuery;  
    query->exec(str);  
    while(query->next())
    {
        QString s1 = query->value(0).toString();
		QString s2 = query->value(1).toString();
		if(s1==ID&&s2==md5_1)flag=1;
    }
    if(flag==0)
        return false;
	else {
		QString update_sql = "update user set state = :state,itip =:itip where ID = :ID ";
		query=new QSqlQuery;  
		query->prepare(update_sql);
		query->bindValue(":state", "online");
		query->bindValue(":itip", ip);
		query->bindValue(":ID", ID);
		query->exec();
		return true;
	}
}  
  
  
bool MySql::signup(QString ID,QString passward,QString question,QString answer)  //注册
{  //加密
	QString md5_1,md5_2,md5_3;  
	QString pwd=passward;  
	QByteArray bb;  
	bb = QCryptographicHash::hash ( pwd.toLatin1(), QCryptographicHash::Md5 );  
	md5_1.append(bb.toHex());  
	pwd=question;
	bb = QCryptographicHash::hash ( pwd.toLatin1(), QCryptographicHash::Md5 );  
	md5_2.append(bb.toHex());  
	pwd=answer;
	bb = QCryptographicHash::hash ( pwd.toLatin1(), QCryptographicHash::Md5 );  
	md5_3.append(bb.toHex());  
  
	int flag=0;
    QString str=QString("select * from user ");  
    query=new QSqlQuery;  
    query->exec(str);  
    while(query->next())
    {
        QString s1 = query->value(0).toString();
		if(s1==ID)flag=1;
    }
    if(flag!=0)
        return false;
    str=QString("insert into user values('%1','%2','%3','%4','offline',' ',' ')").arg(ID).arg(md5_1).arg(md5_2).arg(md5_3);
    bool ret=query->exec(str);
    return ret;
} 

bool MySql::refind(QString ID,QString passward,QString question,QString answer){ //找回密码
	QString md5_1,md5_2,md5_3;  
	QString pwd=passward;  
	QByteArray bb;  
	bb = QCryptographicHash::hash ( pwd.toLatin1(), QCryptographicHash::Md5 );  
	md5_1.append(bb.toHex());  
	pwd=question;
	bb = QCryptographicHash::hash ( pwd.toLatin1(), QCryptographicHash::Md5 );  
	md5_2.append(bb.toHex());  
	pwd=answer;
	bb = QCryptographicHash::hash ( pwd.toLatin1(), QCryptographicHash::Md5 );  
	md5_3.append(bb.toHex());  
 
	int flag=0;
    QString str=QString("select * from user ");  
	query=new QSqlQuery;  
    query->exec(str);  
    while(query->next())
    {
        QString s1 = query->value(0).toString();
		QString s2 = query->value(2).toString();
		QString s3 = query->value(3).toString();
		if(s1==ID&&s2==md5_2&&s3==md5_3)flag=1;
    }
	if(flag==0)
        return false;
	else {
		QString update_sql = "update user set passward = :passward where ID = :ID ";
		query=new QSqlQuery;  
		query->prepare(update_sql);
		query->bindValue(":passward", md5_1);
		query->bindValue(":ID", ID);
		return query->exec();
	}
} 

QString MySql::gfriend(QString ID){ //获取好友列表
	QStringList datalist;
	datalist<<"friend";
	QString data;
	QString str=QString("select * from user ");
	query=new QSqlQuery;  
	query->exec(str);  
	while(query->next())
	{
		if(query->value(0).toString()!=ID)
		datalist<<(query->value(0).toString());
	}
	data=datalist.join("/"); //qstringlist转成QString
	return data;
}

QString MySql::forstate(QString ID){ //给在线状态
	QString data,state,ip,port;
	QString str=QString("select * from user ");  
    query=new QSqlQuery;  
    query->exec(str);  
    while(query->next())
    {
        if(query->value(0).toString()==ID){
			state=query->value(4).toString();
			port=query->value(5).toString();
			ip=query->value(6).toString();
		}
    }
	QString sta="state";
	data=sta+"/"+state+"/"+ip;
	return data;
}

bool MySql::logout(QString ID){ //下线
	QString update_sql = "update user set state = :state where ID = :ID ";
	query=new QSqlQuery;  
	query->prepare(update_sql);
	query->bindValue(":state", "offline");
	query->bindValue(":ID", ID);
	return query->exec();
}

QString MySql::myport(QString ID){ //每次更新新端口
	QString port,data;
	QString update_sql = "update user set ord = :ord where ID = :ID ";
	query=new QSqlQuery;  
	query->prepare(update_sql);
	query->bindValue(":ord",QString::number(get_qrand(),10));
	query->bindValue(":ID", ID);
	query->exec();
	QString str=QString("select * from user ");  
    query=new QSqlQuery;  
    query->exec(str);  
    while(query->next())
    {
        if(query->value(0).toString()==ID)port=query->value(5).toString();
    }
	QString p="myport";
	data=p+"/"+port;
	return data;
}

bool MySql::firstport(QString ID){ //第一次登录创建端口号
	QString port,data;
	QString update_sql = "update user set ord = :ord where ID = :ID ";
	query=new QSqlQuery;  
	query->prepare(update_sql);
	query->bindValue(":ord",QString::number(get_qrand(),10));
	query->bindValue(":ID", ID);
	return query->exec();
	
}

QString MySql::otherport(QString ID){//获得对方端口
	QString port;
	QString str=QString("select * from user ");  
    query=new QSqlQuery;  
    query->exec(str);  
    while(query->next())
    {
        if(query->value(0).toString()==ID)port=query->value(5).toString();
    }

	return port;
}

int MySql::get_qrand(){  //随机数生成
	static QTime t=QTime::currentTime();
	QTime T=QTime::currentTime();
	int i=T.msecsTo(t);
	qsrand(i);

	return qrand();
}