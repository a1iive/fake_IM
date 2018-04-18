//login.h  
#ifndef LOGIN_H  
#define LOGIN_H  
  
#include <QtWidgets/QMainWindow>  
#include <QtNetwork/QTcpSocket>  
#include <QStringListModel>
#include <QListView>
#include <QMessageBox>  
#include <QDialogButtonBox>
#include"chat.h"
#include "off_message.h" 
namespace Ui {  
class login;  
}  
  
class login : public QMainWindow  
{  
    Q_OBJECT  
  
public:  
    explicit login(QWidget *parent = 0);  
    ~login();  
protected:   
    void connectServer();   //与服务器的连接
	void firstwrite();      //获取好友列表

signals:
	void closelogin();
	void give(QString,QString,QString); //给聊天窗口聊天对象的id、状态、ip信息
	void offline_message(QString);
private slots:  
    void texts(const QModelIndex &);
    void readMessages();
	void on_pushButton_clicked();

private:  
    Ui::login *ui;  
	QString name;
    QTcpSocket *socket;  
	QStringListModel *model; 
	//int myport;
};  
  
#endif // LOGIN_H  