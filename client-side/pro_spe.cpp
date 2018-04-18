#include"pro_spe.h"  

#include "ui_pro_spe.h" 

pro_spe::pro_spe(QWidget *parent) :  
    QMainWindow(parent),  
    ui(new Ui::pro_spe)  
{  
	ui->setupUi(this);  
	
	this->setAttribute(Qt::WA_DeleteOnClose);
	ui->pushButton->setEnabled(false);
    
}  
  
pro_spe::~pro_spe()  
{    
    delete ui;  
}  

void pro_spe::update(){
	ui->label->setText(QString::fromLocal8Bit("´«ÊäÍê³É"));
	ui->pushButton->setEnabled(true);
}

/*void pro_spe::update_t(int i){

	ui->label_3->setText(QString::number(i,10));
}
*/

void pro_spe::on_pushButton_clicked(){
	this->close();
}
