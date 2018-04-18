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
	
	int file_size,get_file_size;//��Ϊ���ͷ� ����Ϊ���շ�
protected:   
    void init(); //��ʼ�������׽���
	void initudp(); //��ʼ��udp�׽���
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
	void chat_with(); //�����ı�����

	void send_file(QString,QString);//��һ�δ����ļ� �������Ѱ��Է��˿�
	void file_first();//��һ�δ����ļ� �ȴ����ļ���
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
	void first_return();  //��һ�ν����ļ���������
	void file_name_get(QString,int); //�����մ��ڴ����ļ������ļ���С��Ϣ
	void to_thread(int,int,QString,QString);
	void to_thread_r(int,int,QString,QString);
	void to_pro_spe();
	//void to_pro_spe_t(int);
	void to_pro_spe_r();
private:  
    Ui::chat *ui;  
	QTcpSocket *from_socket;//��Ϊ��������ͻ��˽���
	QTcpSocket *to_socket;  //��Ϊ�ͻ�����ͻ��˽���
	
	QTcpSocket *socket;//�������Ҫ�������׽���
	QTcpServer *server;
	QUdpSocket *udp_send; //���������ļ���Ϣ
	QUdpSocket *udp_read; //���������ļ���Ϣ
	QString ip,state;
	QFile myfile;
	QFile myfile_r;
	int port;//�ͻ��˶Է��˿ں�
	int myport;  //���˿ں�
	QString if_con,name,get_port;//�Ƿ���ͻ��˽������� �����ͻ���ID���Ƿ��ÿͻ��˶Եȷ��˿ں�
	QString file_name,file_path;//��Ϊ���ͷ���������ļ������ļ�·��
	QString get_file_name; //��Ϊ���շ���������ļ���
	//int file_size,get_file_size;//��Ϊ���ͷ� ����Ϊ���շ�
	QByteArray send_data,ack_data;
	int num,page_num;
	int num_read,page_num_read;
	pro_spe *pro_r;
	int pro_num;
	//mythread *thread_send;
	//mythread_r *thread_rev;
};  
  
#endif // CHAT_H  