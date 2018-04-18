#include "thread_3.h"
#define TIMER_TIMEOUT (2*1000) 

thread_3::thread_3(chat *ch,QObject* par):QThread(par){
	
	cha=ch;
	//pro=new pro_spe(cha);
}

thread_3::~thread_3()
{
    
}

void thread_3::init()
{
	//connect(this, SIGNAL(update(int)), pro, SLOT(update(int)),Qt::DirectConnection); 
	timer=new QTimer(this);
	timer->start(1000);
	connect(timer, SIGNAL(timeout()), this, SLOT(handleTimeout()),Qt::DirectConnection); 

}

void thread_3::run()
{
	init();

	exec();

}


void thread_3::handleTimeout(){
	int i;
    i=cha->base_num/(cha->file_size/4088+1)*100;
	emit updata(i);
	timer->start(1000);
}