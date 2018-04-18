#ifndef THREAD_3_H
#define THREAD_3_H
#include <QThread>
#include <QtNetwork>
#include <QtCore>
#include <QtWidgets>
#include <qdebug.h>
#include <QMutex>
#include <chat.h>

class chat;
class thread_3 : public QThread
{
    Q_OBJECT
signals:
    void message(const QString& info);
    void progress(int present);
public:
    thread_3(chat *ch,QObject* par);
    ~thread_3();
	void senddata();
    void run();
	void resend();
protected:
	void init();
signals:
    void updata(int);
private slots:

	void handleTimeout();
private:
	QTimer *timer;
	chat *cha;
};

#endif // MYTHREAD_H