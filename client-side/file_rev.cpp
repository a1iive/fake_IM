#include "file_rev.h"

file_rev::file_rev(QWidget *parent)
	: QMainWindow(parent),
	ui(new Ui::file_rev)
{
	ui->setupUi(this);
	this->setAttribute(Qt::WA_DeleteOnClose);
	label_name=new QLabel(this);
	label_name->setText(QString::fromLocal8Bit("文件名:"));
	label_name->setGeometry(30,40,60,30);
	label_path=new QLabel(this);
	label_path->setText(QString::fromLocal8Bit("文件路径:"));
	label_path->setGeometry(20,80,60,30);
	label_size=new QLabel(this);
	label_size->setGeometry(200,40,60,40);
	textEdit_name=new QTextEdit(this);
	textEdit_name->setGeometry(80, 40, 100, 30);
	textEdit_path=new QTextEdit(this);
	textEdit_path->setGeometry(80, 80, 200, 30);
	saveBtn=new QPushButton(this);
	saveBtn->setText(QString::fromLocal8Bit("接收"));
	saveBtn->setGeometry(60, 130, 60, 25);
	closeBtn=new QPushButton(this);
	closeBtn->setGeometry(180, 130, 60, 25);
	closeBtn->setText(QString::fromLocal8Bit("返回"));
	connect(closeBtn,SIGNAL(clicked()),this,SLOT(closeBtn_clicked()));
	connect(saveBtn,SIGNAL(clicked()),this,SLOT(saveBtn_clicked()));
	createAction();  
    createMenu();  
    createContentMenu();  
    this->resize(300,180);  
}

file_rev::~file_rev()
{
	delete ui;
}

void file_rev::createAction()  
{  
   //创建打开文件动作  
   fileOpenAction = new QAction(QIcon(tr("images/open.ico")), QString::fromLocal8Bit("选择保存路径"), this);  
   //设置打开文件动作的快捷键  
   fileOpenAction->setShortcut(tr("Ctrl + O"));  
   //设置打开文件动作的提示信息  
   fileOpenAction->setStatusTip(QString::fromLocal8Bit("打开一个文件"));  
   //关联打开文件动作的信号和槽  
   connect(fileOpenAction, SIGNAL(triggered()), this, SLOT(fileOpenActionSlot()));  
   
}  

void file_rev::createMenu()  
{  
    menu = this->menuBar()->addMenu(QString::fromLocal8Bit("选择文件夹"));  
    menu->addAction(fileOpenAction);  
}  
  
void file_rev::createContentMenu()  
{  
    this->addAction(fileOpenAction);  
    this->setContextMenuPolicy(Qt::ActionsContextMenu);  
}  
  
void file_rev::fileOpenActionSlot()  
{  
    //QMessageBox::warning(this,tr("提示"),tr("打开文件"),QMessageBox::Yes|QMessageBox::No);  
    selectFile();  
}  
/**************************************** 
* Qt中使用文件选择对话框步骤如下： 
* 1. 定义一个QFileDialog对象 
* 2. 设置路径、过滤器等属性 
*****************************************/  
void file_rev::selectFile()  
{  
    //定义文件对话框类  
    QFileDialog *fileDialog = new QFileDialog(this);  
    //定义文件对话框标题  
    fileDialog->setWindowTitle(QString::fromLocal8Bit("选择文件夹"));  
    //设置默认文件路径  
    fileDialog->setDirectory(".");  
    //设置文件过滤器  
    //fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));  
    //设置文件夹级别
    fileDialog->setFileMode(QFileDialog::Directory);  
    //设置视图模式  
    fileDialog->setViewMode(QFileDialog::Detail);  
    //打印所有选择的文件的路径  
	fileDialog->show();
	connect(fileDialog,SIGNAL( fileSelected ( const QString & )),this,SLOT(fs(const QString & )));
	
 
} 

void file_rev::fs(const QString & fs){
	QString path=fs+"/"+filename;
    
	textEdit_path->setText(path);
}
void file_rev::file_name(QString filename,int filesize){
	file_rev::filename=filename;
	textEdit_name->setText(filename);
	file_size=filesize;
	if(file_size<=1024)
	label_size->setText(QString::number(file_size,10,2)+"Byte");
	else {
		file_size=file_size/1024;
		label_size->setText(QString::number(file_size,10,2)+"KB");
	}
}
   
void file_rev::closeBtn_clicked(){
	this->close();
}

void file_rev::saveBtn_clicked(){
	emit save_file(textEdit_name->toPlainText(),textEdit_path->toPlainText());
}