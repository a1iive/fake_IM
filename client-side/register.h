//register.h  
#ifndef REGISTER_H  
#define REGISTER_H  
  
#include <QtWidgets/QMainWindow>  
#include <QtNetwork/QTcpSocket>  
#include <QMessageBox>  
namespace Ui {  
class Register;  
}  
  
class Register : public QMainWindow  
{  
    Q_OBJECT  
  
public:  
    explicit Register(QWidget *parent = 0);  
    ~Register();  
protected:   
    void connectServer();  //—∞«Ûsocket¡¨Ω” 
private slots:  
  
    void on_pushButton_Sure_clicked();  
	void readMessages();  
  
  
private:  
    Ui::Register *ui;  
    QTcpSocket *socket;  
};  
  
#endif // REGISTER_H  