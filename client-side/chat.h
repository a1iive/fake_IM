//chat.h  
#ifndef CHAT_H  
#define CHAT_H  
  #include <QThread>
#include <QtWidgets/QMainWindow>  
#include <QtWidgets>
#include <QtNetwork/QTcpServer>  
#include <QtNetwork/QTcpSocket> 
#include <QtNetwork>
#include <QtCore>
#include <file.h>
#include <file_rev.h>
#include <mythread.h>
#include <mythread_r.h>
#include <thread_3.h>
#include <pro_spe.h>
#include <QString>
#include <QMutex>
class pro_spe;
namespace Ui {  
class chat;  
}  
  
class chat : public QMainWindow  
{  
    Q_OBJECT  
  
public:  
    explicit chat(QWidget *parent = 0);  
    ~chat();  
	QUdpSocket *udp_send_t;
    int base_num,next_num;
    QTimer *timer;
	
	int file_size,get_file_size;//作为发送方 和作为接收方
protected:   
    void init(); //初始化服务套接字
	void initudp(); //初始化udp套接字
	void connect_server();
	void send_file_data();
	void save_file_data();
private slots:
	void fsocket_Read_Data();
	void fsocket_Disconnected();
	void tsocket_Read_Data();
	void tsocket_Disconnected();
	void on_sendbtn_clicked();
	void on_filebtn_clicked();
	void server_New_Connect();
	void get_ip_state(QString,QString,QString);
	void read_server();
	void chat_with(); //聊天文本传输

	void send_file(QString,QString);//第一次传输文件 向服务器寻求对方端口
	void file_first();//第一次传输文件 先传送文件名
	void readPendingDatagrams();
	void readPendingDatagrams_r();
	void readdatagram();
	void return_first();
	//void handleTimeout();
	void save_first(QString,QString);

	void information(int);
	void file_over();
	void save_over();

	//void handleTimeout_1();
	void from_rth();
signals:
	void start_chat();
	void start_file();
	void first_return();  //第一次接收文件返回内容
	void file_name_get(QString,int); //给接收窗口传递文件名，文件大小信息
	void to_thread(int,int,QString,QString);
	void to_thread_r(int,int,QString,QString);
	void to_pro_spe();
	//void to_pro_spe_t(int);
	void to_pro_spe_r();
private:  
    Ui::chat *ui;  
	QTcpSocket *from_socket;//作为服务器与客户端交流
	QTcpSocket *to_socket;  //作为客户端与客户端交流
	
	QTcpSocket *socket;//向服务器要东西的套接字
	QTcpServer *server;
	QUdpSocket *udp_send; //用来发送文件信息
	QUdpSocket *udp_read; //用来接收文件信息
	QString ip,state;
	QFile myfile;
	QFile myfile_r;
	int port;//客户端对方端口号
	int myport;  //本端口号
	QString if_con,name,get_port;//是否与客户端建立连接 、本客户端ID、是否获得客户端对等方端口号
	QString file_name,file_path;//作为发送方，所存的文件名、文件路径
	QString get_file_name; //作为接收方，所存的文件名
	//int file_size,get_file_size;//作为发送方 和作为接收方
	QByteArray send_data,ack_data;
	int num,page_num;
	int num_read,page_num_read;
	pro_spe *pro_r;
	int pro_num;
	//mythread *thread_send;
	//mythread_r *thread_rev;
};  
  
#endif // CHAT_H  