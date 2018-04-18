#ifndef FILE_H
#define FILE_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QFileDialog>
#include <QtCore/QDebug>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/qprogressbar.h>
#include <QFileInfo>
#include "ui_file.h"
#include <chat.h>
 #include <QtCore>

namespace Ui{
	class file;
}

class file : public QMainWindow
{
	Q_OBJECT

public:
	file(QWidget *parent = 0);
	~file();
private slots:  
    void fileOpenActionSlot();//���ļ�������Ӧ�Ĳۺ���  
private:  
    void createAction();     //��������  
    void createMenu();       //�����˵�  
    void createContentMenu();//���������Ĳ˵�  
    void selectFile();       //����ѡ���ļ��Ի���  
signals:
	void send_file(QString,QString);
private slots:
    void fs(const QString & );
	void sendBtn_clicked();
	void closeBtn_clicked();
private:  
    QAction *fileOpenAction; //����һ��QActionָ�룬���ļ����� 
	QLabel *label_name;
    QLabel *label_path;
	QLabel *label_size;
	QTextEdit* textEdit_name;     //����һ���ı����ȡ�ļ���
	QTextEdit* textEdit_path;     //����һ���ı����ȡ�ļ�·��
	QPushButton * sendBtn;   //����һ��ȷ�����Ͱ�ť
	QPushButton * closeBtn;  //����һ��ȷ�����Ͱ�ť
    QMenu *menu;             //����һ��QMenuָ��  

	QFile myfile;
	double file_size;
	Ui::file *ui;
	//QTimer *timer;
	
};

#endif // FILE_H
