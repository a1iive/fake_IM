#ifndef FILE_REV_H
#define FILE_REV_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QFileDialog>
#include <QtCore/QDebug>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QFileInfo>
#include "ui_file_rev.h"
 

namespace Ui{
	class file_rev;
}

class file_rev : public QMainWindow
{
	Q_OBJECT

public:
	file_rev(QWidget *parent = 0);
	~file_rev();
private slots:  
    void fileOpenActionSlot();//���ļ�������Ӧ�Ĳۺ���  
private:  
    void createAction();     //��������  
    void createMenu();       //�����˵�  
    void createContentMenu();//���������Ĳ˵�  
    void selectFile();       //����ѡ���ļ��Ի���  
signals:
	void save_file(QString,QString);
	
private slots:
    void fs(const QString & );
	void saveBtn_clicked();
	void closeBtn_clicked();
	void file_name(QString,int);
private:  
    QAction *fileOpenAction; //����һ��QActionָ�룬���ļ����� 
	QLabel *label_name;
    QLabel *label_path;
	QLabel *label_size;
	QTextEdit* textEdit_name;     //����һ���ı����ȡ�ļ���
	QTextEdit* textEdit_path;     //����һ���ı����ȡ�ļ�·��
	QPushButton * saveBtn;   //����һ��ȷ�����հ�ť
	QPushButton * closeBtn;  //����һ��ȷ�����Ͱ�ť
    QMenu *menu;             //����һ��QMenuָ��  
	QString filename;
	double file_size;
	Ui::file_rev *ui;
};

#endif // FILE_H
