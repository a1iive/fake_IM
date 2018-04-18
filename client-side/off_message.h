//off_message.h  
#ifndef OFF_MESSAGE_H  
#define OFF_MESSAGE_H  
  
#include <QtWidgets/QMainWindow>  


namespace Ui {  
class off_message;  
}  
  
class off_message : public QMainWindow  
{  
    Q_OBJECT  
  
public:  
    explicit off_message(QWidget *parent = 0);  
    ~off_message();  

private slots:  
    void on_pushButton_clicked();  
	void message(QString);

private:  
    Ui::off_message *ui;  

};  
  
#endif // OFF_MESSAGE_H  