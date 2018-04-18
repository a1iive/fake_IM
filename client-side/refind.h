//refind.h  
#ifndef REFIND_H  
#define REFIND_H  
  
#include <QtWidgets/QMainWindow>  
#include <QtNetwork/QTcpSocket>  
#include <QMessageBox>  
namespace Ui {  
class refind;  
}  
  
class refind : public QMainWindow  
{  
    Q_OBJECT  
  
public:  
    explicit refind(QWidget *parent = 0);  
    ~refind();  
protected:   
    void connectServer();   //—∞«Ûsocket¡¨Ω”
private slots:  
  
    void on_surebtn_clicked();  
	void readMessages();  
  
  
private:  
    Ui::refind *ui;  
    QTcpSocket *socket;  
};  
  
#endif // REGISTER_H  