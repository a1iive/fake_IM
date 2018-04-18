#include "mythread_r.h"
mythread_r::mythread_r(QObject* par):QThread(par){

}

mythread_r::~mythread_r()
{
    
}

void mythread_r::init()
{
	n=0;
	num=1;
	expect_num=1;
	ack_data.resize(8);
	int *p=(int *)ack_data.data();
	*p=num;
    *(p+1)=0;
	udp_read = new QUdpSocket(this);
    udp_read->bind(myport-1); //接收方绑定本客户端tcp端口-1
	connect(udp_read,SIGNAL(readyRead()), this, SLOT(readPendingDatagrams_r()),Qt::DirectConnection);
}

void mythread_r::run(){
	init();
	myfile.setFileName(file_path);
	if (!myfile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Unbuffered))
        return;
	exec();
}

void mythread_r::get_port(int myport,int port,QString path,QString ip){
	mythread_r::myport=myport;
	mythread_r::port=port;
	file_path=path;
	mythread_r::ip=ip;
}

void mythread_r::readPendingDatagrams_r(){
	if(n==0){//显示传输过程界面
		emit to_chat();
		n=1;
	}
	while (udp_read->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udp_read->pendingDatagramSize());
        udp_read->readDatagram(datagram.data(), datagram.size());
		int *ptr = (int *)datagram.data();
		if(*ptr ==num&&*(ptr+1)==expect_num){
			std::string str=datagram.toStdString();
			std::string st=std::string(str,8);
			QByteArray save_data=QByteArray::fromStdString(st);
			myfile.write(save_data,save_data.size());
			ack_data.resize(8);
			int *p=(int *)ack_data.data();
			*p=num;
			*(p+1)=expect_num;
			udp_read->writeDatagram(ack_data,ack_data.size(),QHostAddress(ip),port-3);
			if(save_data.size()<4088){
				emit save_over();
			}
			expect_num++;
		}
		else udp_read->writeDatagram(ack_data,ack_data.size(),QHostAddress(ip),port-3);
	}
}