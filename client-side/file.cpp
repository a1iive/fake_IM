#include "file.h"

file::file(QWidget *parent)
	: QMainWindow(parent),
	ui(new Ui::file)
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
	//label_size->setText(QString::fromLocal8Bit("1312312131"));
	label_size->setGeometry(200,40,60,40);
	textEdit_name=new QTextEdit(this);
	textEdit_name->setGeometry(80, 40, 100, 30);
	textEdit_path=new QTextEdit(this);
	textEdit_path->setGeometry(80, 80, 200, 30);
	sendBtn=new QPushButton(this);
	sendBtn->setText(QString::fromLocal8Bit("����"));
	sendBtn->setGeometry(60, 130, 60, 25);
	closeBtn=new QPushButton(this);
	closeBtn->setGeometry(180, 130, 60, 25);
	closeBtn->setText(QString::fromLocal8Bit("����"));

	connect(closeBtn,SIGNAL(clicked()),this,SLOT(closeBtn_clicked()));
	connect(sendBtn,SIGNAL(clicked()),this,SLOT(sendBtn_clicked()));
	createAction();  
    createMenu();  
    createContentMenu();  
    this->resize(300,180);  
	//timer=new QTimer(this);
	//connect(ch->t1, SIGNAL(timeout()), this, SLOT(handleTimeout()));
}

file::~file()
{
	delete ui;
}

void file::createAction()  
{  
   //�������ļ�����  
   fileOpenAction = new QAction(QIcon(tr("images/open.ico")), QString::fromLocal8Bit("���ļ�"), this);  
   //���ô��ļ������Ŀ�ݼ�  
   fileOpenAction->setShortcut(tr("Ctrl + O"));  
   //���ô��ļ���������ʾ��Ϣ  
   fileOpenAction->setStatusTip(QString::fromLocal8Bit("��һ���ļ�"));  
   //�������ļ��������źźͲ�  
   connect(fileOpenAction, SIGNAL(triggered()), this, SLOT(fileOpenActionSlot()));  
   
}  

void file::createMenu()  
{  
    menu = this->menuBar()->addMenu(QString::fromLocal8Bit("ѡ���ļ�"));  
    menu->addAction(fileOpenAction);  
}  
  
void file::createContentMenu()  
{  
    this->addAction(fileOpenAction);  
    this->setContextMenuPolicy(Qt::ActionsContextMenu);  
}  
  
void file::fileOpenActionSlot()  
{  
    //QMessageBox::warning(this,tr("��ʾ"),tr("���ļ�"),QMessageBox::Yes|QMessageBox::No);  
    selectFile();  
}  
/**************************************** 
* Qt��ʹ���ļ�ѡ��Ի��������£� 
* 1. ����һ��QFileDialog���� 
* 2. ����·���������������� 
*****************************************/  
void file::selectFile()  
{  
    //�����ļ��Ի�����  
    QFileDialog *fileDialog = new QFileDialog(this);  
    //�����ļ��Ի������  
    fileDialog->setWindowTitle(QString::fromLocal8Bit("���ļ�"));  
    //����Ĭ���ļ�·��  
    fileDialog->setDirectory(".");  
    //�����ļ�������  
    //fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));  
    //���ÿ���ѡ�����ļ�,Ĭ��Ϊֻ��ѡ��һ���ļ�QFileDialog::ExistingFiles  
    fileDialog->setFileMode(QFileDialog::ExistingFiles);  
    //������ͼģʽ  
    fileDialog->setViewMode(QFileDialog::Detail);  
    //��ӡ����ѡ����ļ���·��  
	fileDialog->show();
	connect(fileDialog,SIGNAL( fileSelected ( const QString & )),this,SLOT(fs(const QString & )));
	
 
} 

void file::fs(const QString & fs){
	QString  file_name;  
	myfile.setFileName(fs);
	if (myfile.open(QIODevice::ReadOnly)) file_size=myfile.size();
	QFileInfo fi;
    fi = QFileInfo(fs);  
	file_name = fi.fileName();  
    textEdit_name->setText(file_name);
	textEdit_path->setText(fs);
	if(file_size<=1024)
	label_size->setText(QString::number(file_size,10,2)+"Byte");
	else {
		file_size=file_size/1024;
		label_size->setText(QString::number(file_size,10,2)+"KB");
	}
}
   
void file::closeBtn_clicked(){
	this->close();
}

void file::sendBtn_clicked(){
	emit send_file(textEdit_name->toPlainText(),textEdit_path->toPlainText());
}




