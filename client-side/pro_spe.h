//pro_spe.h  
#ifndef PRO_SPE_H  
#define PRO_SPE_H  
#include <QtWidgets/QMainWindow>  
#include <QtNetwork/QTcpSocket>  
#include <QtNetwork>
#include<chat.h>
#include <QtCore>
class chat;
namespace Ui {  
class pro_spe;  
}  
  
class pro_spe : public QMainWindow  
{  
    Q_OBJECT  
  
public:  
    explicit pro_spe(QWidget *parent = 0);  
    ~pro_spe(); 
  
private slots:  
	void update();
	//void update_t(int);
	void on_pushButton_clicked();
private:  
    Ui::pro_spe *ui; 
	

};  
  
#endif // PRO_SPE_H  