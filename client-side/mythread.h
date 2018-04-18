#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <QtNetwork>
#include <QtCore>
#include <QtWidgets>
#include <qdebug.h>
#include <QMutex>
#include <chat.h>
#define N 10
class chat;
class mythread : public QThread
{
    Q_OBJECT
signals:
    void message(const QString& info);
    void progress(int present);
public:
    mythread(chat *ch,QObject* par);
    ~mythread();
	void senddata();
    void run();
	void resend();
protected:
	void init();
signals:
	//void information(int);
	void file_over();
private slots:
	void get_port(int,int,QString,QString);
	//void readPendingDatagrams();
	void handleTimeout();
private:
	int myport,port;
	int num,size_send;
	int file_size;
	QString file_path,ip;
	QFile myfile;
	QUdpSocket *udp_send;
	QByteArray send_data;
	std::string sndpkt[130000];
	int flag;
	chat *cha;
	
};

#endif // MYTHREAD_H