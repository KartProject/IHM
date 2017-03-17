#include "directsimul.h"
#include <QTimer>

DirectSimul::DirectSimul(QWidget *parent) :
	QWidget(parent)
{
	setupUi(this);
	distance_to_do = 0;
	total_distance = 0;
	refresh_time = 0;
	connect(start, SIGNAL(clicked()), this, SLOT(start_measures()));
	//connect()
}
void DirectSimul::start_measures(){
	if(start->isEnabled()){
		calculation();
	}
}
void DirectSimul::calculation(){
	if(progressBar->value() < 100){
		label_3->setText(QString("%1").arg(gradiant->value()));
		refresh_time = 0;
		total_distance = total_distance + ((slider->value() * 25)/18000);
		distance_to_do = (((double)slider->value() * 100.0)/18000.0);
		QTimer::singleShot(10, this, SLOT(refreshState()));
	}
	else{
		progressBar->setValue(0);
	}
}
void DirectSimul::refreshState(){
	if(refresh_time < 20 && progressBar->value() < 100){
		label_4->setText(QString("%1").arg(distance_to_do/20.0 + label_4->text().toDouble()));
		refresh_time++;
		progressBar->setValue(round((label_4->text().toDouble()/distance->value())*100.0));
		QTimer::singleShot(10, this, SLOT(refreshState()));
	}
	else if(progressBar->value() < 100){
		calculation();
	}
}
