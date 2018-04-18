#include"login.h"  

#include "ui_login.h" 

#define IP "192.168.1.106"  
#define port "4001"  
extern QString myid;

login::login( QWidget *parent):  
    QMainWindow(parent),  
    ui(new Ui::login)  
{  
    ui->setupUi(this);  
    socket = new QTcpSocket(); 
	//socket����
	connectServer();
	firstwrite();

}
	   

login::~login()  
{  
	QString out="o";
	QString logout=out+"/"+myid;
	socket->write(logout.toLatin1());
	socket->waitForBytesWritten();
	this->socket->disconnectFromHost();
	this->socket->close();
    delete this->socket;    
    delete ui;  
	emit closelogin();
}  

void login::connectServer(){
	//socket->abort();   //ȡ�����е�����  
    socket->connectToHost(IP,QString(port).toInt());  
    connect(socket,SIGNAL(readyRead()),this,SLOT(readMessages()));  
}

void login::texts(const QModelIndex &index){
	name=index.data().toString();
	QString state="state";
	QString data=state+"/"+name;
	socket->write(data.toLatin1()); 

}

void login::firstwrite(){
	QString write="w";
	QString data=write+"/"+myid;
	socket->write(data.toLatin1()); 
}

void login::readMessages(){
	QString data=socket->readAll();  
	QStringList list=data.split("/"); 
	if(list[0]=="friend"){    //��ú����б�
		list.removeOne("friend");
		model = new QStringListModel(this); 
	    model->setStringList(list);	
	    ui->listView->setModel(model);
	    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	    connect(ui->listView,SIGNAL(clicked(const QModelIndex &)),this,SLOT(texts(const QModelIndex &)));
		QString string="get_off_mess";	 //Ѱ��������Ϣ
	    QString data=string+"/"+myid;  
		socket->write(data.toLatin1());  
	}
	else if(list[0]=="state"){ //������ߣ����ߣ�״̬

		chat *c=new chat(this);
		c->show();
		c->setWindowTitle(name+" "+list[1]);
		connect(this,SIGNAL(give(QString,QString,QString)),c,SLOT(get_ip_state(QString,QString,QString)));
		emit give(list[1],list[2],name);
		//QMessageBox::information(this,QString::fromLocal8Bit("����"),list[1],QMessageBox::Ok); 
	}
	else if(list[0]=="get_off_mess"){ //���������Ϣ
		QString string="first_myport";	
	    QString data=string+"/"+myid;  
		socket->write(data.toLatin1());  
		off_message *off=new off_message(this);
		off->show();
		off->setWindowTitle(QString::fromLocal8Bit("���������Ϣ"));
		connect(this,SIGNAL(offline_message(QString)),off,SLOT(message(QString)));
		emit offline_message(list[1]);
	}

}

void login::on_pushButton_clicked(){
	QString write="w";
	QString data=write+"/"+myid;
	socket->write(data.toLatin1()); 
}
