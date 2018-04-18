#ifndef MYTHREAD_R_H
#define MYTHREAD_R_H
#include <QThread>
#include <QtNetwork>
#include <QtCore>
#include <QtWidgets>

class mythread_r : public QThread
{
    Q_OBJECT
signals:
    void message(const QString& info);
    void progress(int present);
public:
    mythread_r(QObject* par);
    ~mythread_r();
	void run();
	void senddata();
protected:
	void init();
signals:
	void to_chat();
	void save_over();
private slots:
	void get_port(int,int,QString,QString);
	void readPendingDatagrams_r();
private:
	int n;
	int myport,port;
	int num,expect_num;
	QByteArray ack_data;
	QString file_path,ip;
	QFile myfile;
	QUdpSocket *udp_read;
};

#endif // MYTHREAD_R_H