#include "chat.h"  
#include "ui_chat.h"  
#define s_IP "192.168.1.106" 
#define s_port "4001" 
#define TIMER_TIMEOUT (500) 

extern QString myid;
//QUdpSocket *udp_send_t;
//int base_num,next_num;
//QTimer *timer;
QMutex mutex;

chat::chat(QWidget *parent) :  
    QMainWindow(parent),  
    ui(new Ui::chat)  
{  
    ui->setupUi(this); 
	ui->textEdit_read->setReadOnly(true);
	this->setAttribute(Qt::WA_DeleteOnClose);
	connect_server();
	connect(this,SIGNAL(start_chat()),this,SLOT(chat_with()));
	connect(this,SIGNAL(start_file()),this,SLOT(file_first()));
	connect(this,SIGNAL(first_return()),this,SLOT(return_first()));
	if_con="0",get_port="0"; 
  
}  
  
chat::~chat()  
{  
	if(if_con=="2"){
		QString cue="-d:i leave";
		to_socket->write(cue.toLatin1());  
		to_socket->flush(); 
	}
	this->server->close();
	delete server;
    delete ui;  
}  
//与服务器的连接
void chat::connect_server(){
	socket=new QTcpSocket(); 
	socket->connectToHost(s_IP,QString(s_port).toInt());  
    connect(socket,SIGNAL(readyRead()),this,SLOT(read_server()));
	QString string="myport";
	QString data=string+"/"+myid;  
    socket->write(data.toLatin1()); 
}
//读取服务器发来的消息
void chat::read_server(){
	QString data=socket->readAll();  
	QStringList list=data.split("/"); 
	if(list[0]=="myport"){
		myport=list[1].toInt();
		init(); 
		initudp();
		
	}
	else if(list[0]=="otherport"){
		if(get_port=="0"){
		port=list[1].toInt();
		get_port="1";
		}
		emit start_chat(); //触发chat_with函数
	}
	else if(list[0]=="send_off_mess"){
		if(list[1]=="true")
		QMessageBox::information(this,QString::fromLocal8Bit("信息提示"),QString::fromLocal8Bit("离线消息发送成功！"),QMessageBox::Ok); 
		else QMessageBox::information(this,QString::fromLocal8Bit("信息提示"),QString::fromLocal8Bit("离线消息发送失败！"),QMessageBox::Ok); 
		this->close();
	}
	else if(list[0]=="file"){  //第一次主动发送文件 向服务器询问对方端口
		if(get_port=="0"){
			port=list[1].toInt();
			get_port="1";
		}
		emit start_file(); //触发file_first函数
	}
	else if(list[0]=="read_file"){ //第一次接收文件 向服务器寻求对方端口
		if(get_port=="0"){
			port=list[1].toInt();
			get_port="1";
		}
		emit first_return(); //触发return_first函数
	}

}

void chat::init(){
	server = new QTcpServer();  
	if(!server->listen(QHostAddress::Any, myport)) 
	{  
		//若出错，则输出错误信息  
		qDebug()<<server->errorString();  
		return;  
	}  
	connect(server,&QTcpServer::newConnection,this,&chat::server_New_Connect);  
}

void chat::server_New_Connect(){ //如果有人寻求连接，成为点对点交流的服务器端
	if_con="1";
	//获取客户端连接  
    from_socket = server->nextPendingConnection(); 
	//server->close();
    //连接QTcpSocket的信号槽，以读取新数据  
    connect(from_socket, SIGNAL(readyRead()), this, SLOT(fsocket_Read_Data()));  
    connect(from_socket, SIGNAL(disconnected()), this, SLOT(fsocket_Disconnected()));  
	connect(from_socket, SIGNAL(disconnected()), this, SLOT(deleteLater()));
}  

void chat::on_sendbtn_clicked(){ //发送文本消息  如果之前没有获得端口，那么向服务器要对方端口，成为点对点交流的客户端方
	QString str = ui->textEdit_read->toPlainText();  
	str+="you:";
	str+=ui->textEdit_write->toPlainText();
	str+=("\n");
        //刷新显示  
    ui->textEdit_read->setText(str);  
	if(get_port=="0"&&state=="online"){
		QString string="otherport";
	    QString data=string+"/"+name;  
        socket->write(data.toLatin1()); 

	}
	else if(get_port=="1"&&state=="online")
		emit start_chat();
	else if(state=="offline"){
		QString string="send_off_mess";	
	    QString data=string+"/"+name+"/"+myid+"/"+ui->textEdit_write->toPlainText();  
		socket->write(data.toLatin1());  
	}
}

void chat::chat_with(){
	if(if_con=="0"&&state=="online"){
		if_con="2";
	    to_socket=new QTcpSocket();  
	    connect(to_socket, SIGNAL(readyRead()), this, SLOT(tsocket_Read_Data()));  
        connect(to_socket, SIGNAL(disconnected()), this, SLOT(tsocket_Disconnected()));  
	    connect(to_socket, SIGNAL(disconnected()), this, SLOT(deleteLater()));

        to_socket->connectToHost(ip, port);  
	    if(!to_socket->waitForConnected(3000)) 
		{  
            return;  
        }  
	    to_socket->write(ui->textEdit_write->toPlainText().toLatin1());  
        to_socket->flush(); 
	
	    }
	else if(if_con=="1"&&state=="online"){
		from_socket->write(ui->textEdit_write->toPlainText().toLatin1()); 
		from_socket->flush(); 
	}
	else if(if_con=="2"&&state=="online"){
		to_socket->write(ui->textEdit_write->toPlainText().toLatin1());  
		to_socket->flush(); 
	}
}

//作为服务器端收消息
void chat::fsocket_Read_Data(){
	QByteArray data;  
	//读取缓冲区数据  
    data = from_socket->readAll();  
	if(tr(data)=="-d:i leave"){
		this->close();
		return;
	}
	if(!data.isEmpty())  
    {  
        QString str = ui->textEdit_read->toPlainText();  
        str+=tr(data);
		str+=("\n");
        //刷新显示  
        ui->textEdit_read->setText(str);  
    }  

}
//作为客户端收消息
void chat::tsocket_Read_Data(){
	QByteArray data;  
	//读取缓冲区数据  
    data = to_socket->readAll();  
	if(!data.isEmpty())  
    {  
        QString str = ui->textEdit_read->toPlainText();  
        str+=tr(data); 
		str+=("\n");
        //刷新显示  
        ui->textEdit_read->setText(str);  
    }  
}

void chat::fsocket_Disconnected(){
	from_socket->close();
}

void chat::tsocket_Disconnected(){
	to_socket->close();
} 

//获得本聊天窗口聊天对象的ip、在线状态、名字（ID）
void chat::get_ip_state(QString state,QString ip,QString name){
	chat::ip=ip;
	chat::state=state;
	chat::name=name;
}

//
//以下为文件传输部分
//
void chat::on_filebtn_clicked(){
	file *f=new file(this);
    f->show();
	connect(f,SIGNAL(send_file(QString,QString)),this,SLOT(send_file(QString,QString)));
	//connect(this,SIGNAL(to_file_pro(int)),f,SLOT(update_pro(int)));
}

void chat::send_file(QString name,QString path){
	file_name=name;
	file_path=path;
	myfile.setFileName(path);
	if (myfile.open(QIODevice::ReadOnly)) file_size=myfile.size();
	if(get_port=="0"&&state=="online"){
		QString string="file";
	    QString data=string+"/"+chat::name;  
        socket->write(data.toLatin1()); 
	}
	else if(get_port=="1"&&state=="online")
		emit start_file();//触发file_first函数
}

void chat::file_first(){
	QByteArray name_data=file_name.toLatin1();
	char *ch=name_data.data();
	send_data.resize(12);
	int *ptr=(int *)send_data.data();
	page_num=1;
	num=0;
	page_num_read=1;
	num_read=0;
    *ptr=num;
    *(ptr+1)=page_num;
	*(ptr+2)=file_size;
	send_data=send_data+name_data;
	udp_send->writeDatagram(send_data,send_data.size(),QHostAddress(ip),port+1);
	//first_t->start(FIRST_TIMEOUT);  
}

void chat::initudp(){
	udp_send = new QUdpSocket(this);
    udp_send->bind(myport+2); //发送方绑定本客户端tcp端口+2
	udp_read = new QUdpSocket(this);
	udp_read->bind(myport+1); //接收方绑定客户端tcp端口+1
    connect(udp_send, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
    connect(udp_read, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams_r()));
	
	udp_send_t= new QUdpSocket(this);
    udp_send_t->bind(myport-3);//收ackudp绑定本客户端tcp端口-3
	connect(udp_send_t,SIGNAL(readyRead()), this, SLOT(readdatagram()));

	timer = new QTimer(this);
	base_num=1;
	next_num=1;
}

void chat::readPendingDatagrams(){
	while (udp_send->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udp_send->pendingDatagramSize());

        udp_send->readDatagram(datagram.data(), datagram.size());
		int *ptr = (int *)datagram.data();
        if(*ptr ==0&&*(ptr+1)==1){
            qDebug() << "send OK!";	
			pro_spe *pro=new pro_spe(this);
			connect(this, SIGNAL(to_pro_spe()), pro, SLOT(update()));
			//connect(this, SIGNAL(to_pro_spe_t()), pro, SLOT(update_t()));
			pro->show();
			//thread_3 *thread_pro=new thread_3(this,NULL);
			//connect(thread_pro,&QThread::finished,thread_pro,&QObject::deleteLater);//线程结束后调用deleteLater来销毁分配的内存
			//connect(thread_pro, SIGNAL(update(int)), pro, SLOT(update(int)));
            //thread_pro->start();

			send_file_data();
        }
    }
}

void chat::send_file_data(){
	//qDebug()<<currentThreadId;
	mythread *thread_send=new mythread(this,NULL);
	//connect(thread_send,SIGNAL(information(int)),this,SLOT(information(int)));
	connect(thread_send,SIGNAL(file_over()),this,SLOT(file_over()));
	connect(this,SIGNAL(to_thread(int,int,QString,QString)),thread_send,SLOT(get_port(int,int,QString,QString)));
	connect(thread_send,&QThread::finished,thread_send,&QObject::deleteLater);//线程结束后调用deleteLater来销毁分配的内存
	emit to_thread(myport,port,file_path,ip);
	thread_send->start();

}
void chat::readPendingDatagrams_r(){
	while (udp_read->hasPendingDatagrams()) {
        QByteArray datagram;
		QString str;
        datagram.resize(udp_read->pendingDatagramSize());
		char*arr;
        udp_read->readDatagram(datagram.data(), datagram.size());
		str=QString(datagram);
		int *ptr = (int *)datagram.data();
        if(*ptr ==0&&*(ptr+1)==1){
			num_read=1;
			page_num_read=1;
			get_file_size=*(ptr+2);
			arr=datagram.data();
			arr=arr+12;
			get_file_name=QString(QLatin1String(arr));
			if(get_port=="0"){
				QString string="read_file";
				QString data=string+"/"+chat::name;  
				socket->write(data.toLatin1()); 
				return;
			}
			else{
				emit first_return();
			}
		}
		/*else if(*ptr==num_read&&*(ptr+1)==page_num_read){
			std::string str=datagram.toStdString();
			std::string st=std::string(str,8);
			QByteArray save_data=QByteArray::fromStdString(st);
			myfile_r.write(save_data,save_data.size());
			
			ack_data.resize(8);
			int *p=(int *)ack_data.data();
			*p=num_read;
			*(p+1)=page_num_read;
			udp_read->writeDatagram(ack_data,ack_data.size(),QHostAddress(ip),port-2);
			if(save_data.size()<4088){
				QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("文件接收完成"),QMessageBox::Ok); 

			}
			page_num_read++;
		}
		else if(*ptr==num_read&&*(ptr+1)==(page_num_read-1)){
			udp_read->writeDatagram(ack_data,ack_data.size(),QHostAddress(ip),port-2);
		}*/
    }
}

void chat::return_first(){
	file_rev *fr=new file_rev(this);
    fr->show();
	connect(this,SIGNAL(file_name_get(QString,int)),fr,SLOT(file_name(QString,int)));
	connect(fr,SIGNAL(save_file(QString,QString)),this,SLOT(save_first(QString,QString)));
	emit file_name_get(get_file_name,get_file_size);
}

void chat::save_first(QString name,QString path){
	myfile_r.setFileName(path);
	if (!myfile_r.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Unbuffered))
        return;
	ack_data.resize(8);
	int *p=(int *)ack_data.data();
	*p=0;
	*(p+1)=1;
	udp_read->writeDatagram(ack_data,ack_data.size(),QHostAddress(ip),port+2);
	mythread_r *thread_rev=new mythread_r(this);
	connect(thread_rev, SIGNAL(to_chat()), this, SLOT(from_rth()));
	connect(thread_rev,SIGNAL(save_over()),this,SLOT(save_over()));
	connect(this,SIGNAL(to_thread_r(int,int,QString,QString)),thread_rev,SLOT(get_port(int,int,QString,QString)));
	connect(thread_rev,&QThread::finished,thread_rev,&QObject::deleteLater);//线程结束后调用deleteLater来销毁分配的内存
	emit to_thread_r(myport,port,path,ip);
	thread_rev->start();

}

void chat::readdatagram(){
	while (udp_send_t->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udp_send_t->pendingDatagramSize());
        udp_send_t->readDatagram(datagram.data(), datagram.size());
		int *ptr = (int *)datagram.data();
		if(*ptr ==1){
			//mutex.lock();
			base_num=*(ptr+1)+1;
			//mutex.unlock();
			if(base_num==next_num)
			timer->stop();
			else timer->start(TIMER_TIMEOUT);
		}
    }
	if(base_num==(file_size/4088+2))
		emit to_pro_spe();
	//else emit to_pro_spe_t(base_num);
	
}

/*void chat::handleTimeout_1(){
	int i;
    i=base_num/(file_size/4088+1)*100;
	emit to_file_pro(i);
	t1->start(1000);
}*/

void chat::information(int page_num){
	QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::number(page_num,10),QMessageBox::Ok); 
}

void chat::file_over(){
	QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("传输完成"),QMessageBox::Ok); 
}

void chat::save_over(){
	emit to_pro_spe_r();
	//QMessageBox::information(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("接收完成"),QMessageBox::Ok); 
}

void chat::from_rth(){
    pro_r=new pro_spe(this);
    connect(this, SIGNAL(to_pro_spe_r()), pro_r, SLOT(update()));
	pro_r->show();

}