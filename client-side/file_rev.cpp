#include "file_rev.h"

file_rev::file_rev(QWidget *parent)
	: QMainWindow(parent),
	ui(new Ui::file_rev)
{
	ui->setupUi(this);
	this->setAttribute(Qt::WA_DeleteOnClose);
	label_name=new QLabel(this);
	label_name->setText(QString::fromLocal8Bit("�ļ���:"));
	label_name->setGeometry(30,40,60,30);
	label_path=new QLabel(this);
	label_path->setText(QString::fromLocal8Bit("�ļ�·��:"));
	label_path->setGeometry(20,80,60,30);
	label_size=new QLabel(this);
	label_size->setGeometry(200,40,60,40);
	textEdit_name=new QTextEdit(this);
	textEdit_name->setGeometry(80, 40, 100, 30);
	textEdit_path=new QTextEdit(this);
	textEdit_path->setGeometry(80, 80, 200, 30);
	saveBtn=new QPushButton(this);
	saveBtn->setText(QString::fromLocal8Bit("����"));
	saveBtn->setGeometry(60, 130, 60, 25);
	closeBtn=new QPushButton(this);
	closeBtn->setGeometry(180, 130, 60, 25);
	closeBtn->setText(QString::fromLocal8Bit("����"));
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
   //�������ļ�����  
   fileOpenAction = new QAction(QIcon(tr("images/open.ico")), QString::fromLocal8Bit("ѡ�񱣴�·��"), this);  
   //���ô��ļ������Ŀ�ݼ�  
   fileOpenAction->setShortcut(tr("Ctrl + O"));  
   //���ô��ļ���������ʾ��Ϣ  
   fileOpenAction->setStatusTip(QString::fromLocal8Bit("��һ���ļ�"));  
   //�������ļ��������źźͲ�  
   connect(fileOpenAction, SIGNAL(triggered()), this, SLOT(fileOpenActionSlot()));  
   
}  

void file_rev::createMenu()  
{  
    menu = this->menuBar()->addMenu(QString::fromLocal8Bit("ѡ���ļ���"));  
    menu->addAction(fileOpenAction);  
}  
  
void file_rev::createContentMenu()  
{  
    this->addAction(fileOpenAction);  
    this->setContextMenuPolicy(Qt::ActionsContextMenu);  
}  
  
void file_rev::fileOpenActionSlot()  
{  
    //QMessageBox::warning(this,tr("��ʾ"),tr("���ļ�"),QMessageBox::Yes|QMessageBox::No);  
    selectFile();  
}  
/**************************************** 
* Qt��ʹ���ļ�ѡ��Ի��������£� 
* 1. ����һ��QFileDialog���� 
* 2. ����·���������������� 
*****************************************/  
void file_rev::selectFile()  
{  
    //�����ļ��Ի�����  
    QFileDialog *fileDialog = new QFileDialog(this);  
    //�����ļ��Ի������  
    fileDialog->setWindowTitle(QString::fromLocal8Bit("ѡ���ļ���"));  
    //����Ĭ���ļ�·��  
    fileDialog->setDirectory(".");  
    //�����ļ�������  
    //fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));  
    //�����ļ��м���
    fileDialog->setFileMode(QFileDialog::Directory);  
    //������ͼģʽ  
    fileDialog->setViewMode(QFileDialog::Detail);  
    //��ӡ����ѡ����ļ���·��  
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