#include "off_message.h"  
#include "ui_off_message.h"  

off_message::off_message(QWidget *parent) :  
    QMainWindow(parent),  
    ui(new Ui::off_message)  
{  
    ui->setupUi(this); 
	ui->textEdit->setReadOnly(true);
	this->setAttribute(Qt::WA_DeleteOnClose);

  
}  
  
off_message::~off_message()  
{  
    delete ui;  
}  

void off_message::on_pushButton_clicked(){
	this->close();
}

void off_message::message(QString data){
	ui->textEdit->setText(data);  
}