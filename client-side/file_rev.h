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
    void fileOpenActionSlot();//打开文件动作对应的槽函数  
private:  
    void createAction();     //创建动作  
    void createMenu();       //创建菜单  
    void createContentMenu();//创建上下文菜单  
    void selectFile();       //弹出选择文件对话框  
signals:
	void save_file(QString,QString);
	
private slots:
    void fs(const QString & );
	void saveBtn_clicked();
	void closeBtn_clicked();
	void file_name(QString,int);
private:  
    QAction *fileOpenAction; //创建一个QAction指针，打开文件动作 
	QLabel *label_name;
    QLabel *label_path;
	QLabel *label_size;
	QTextEdit* textEdit_name;     //创建一个文本框读取文件名
	QTextEdit* textEdit_path;     //创建一个文本框读取文件路径
	QPushButton * saveBtn;   //创建一个确定接收按钮
	QPushButton * closeBtn;  //创建一个确定发送按钮
    QMenu *menu;             //创建一个QMenu指针  
	QString filename;
	double file_size;
	Ui::file_rev *ui;
};

#endif // FILE_H
