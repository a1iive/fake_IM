#include "mythread.h"
#define TIMER_TIMEOUT (2*1000) 
//extern QUdpSocket *udp_send_t;
//extern int base_num,next_num;
//extern QTimer *timer;
extern QMutex mutex; 
mythread::mythread(chat *ch,QObject* par):QThread(par){
	 //moveToThread(this);
	cha=ch;
}

mythread::~mythread()
{
    
}

void mythread::init()
{
	
	flag=1;
	num=1;
	//cha->base_num=1;
	//cha->next_num=1;
	udp_send= new QUdpSocket(this);
    udp_send->bind(myport-2);//收ackudp绑定本客户端tcp端口-2
	connect(udp_send,SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()),Qt::DirectConnection);  
    connect(cha->timer, SIGNAL(timeout()), this, SLOT(handleTimeout()),Qt::DirectConnection); 
	myfile.setFileName(file_path);
	if (!myfile.open(QIODevice::ReadOnly))
        return;
	file_size=myfile.size();
	

}

void mythread::run()
{
	init();
	qDebug()<<currentThreadId;
	while(1)
		senddata();
	exec();

}

void mythread::get_port(int myport,int port,QString path,QString ip){
	mythread::myport=myport;
	mythread::port=port;
	file_path=path;
	mythread::ip=ip;
}


void mythread::senddata(){
	if(!myfile.atEnd()){
		
		if(cha->next_num<cha->base_num+N){
		QByteArray line = myfile.read(4088);
		size_send=line.size();
		send_data.resize(8);
		int *ptr=(int *)send_data.data();
		*ptr=num;
        *(ptr+1)=cha->next_num;
		send_data=send_data+line;
		sndpkt[cha->next_num]=send_data.toStdString();
		udp_send->writeDatagram(send_data,send_data.size(),QHostAddress(ip),port-1);
		if(cha->base_num==cha->next_num)
		cha->timer->start(TIMER_TIMEOUT);
		//mutex.lock();

		(cha->next_num)++;
		//mutex.unlock();
		qDebug()<<currentThreadId;
		}
		
		}
}

void mythread::resend(){
	//mutex.lock();
	int i=cha->next_num-cha->base_num;
	int j=cha->base_num;
	//mutex.unlock();
	while(i){
		udp_send->writeDatagram(QByteArray::fromStdString(sndpkt[j]),QByteArray::fromStdString(sndpkt[j]).size(),QHostAddress(ip),port-1);
		j++;
		i--;
	}
	cha->timer->start(TIMER_TIMEOUT);
}

void mythread::handleTimeout(){
	resend();
}