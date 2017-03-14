#include "directsimul.h"
#include <QTimer>

DirectSimul::DirectSimul(QWidget *parent) :
	QWidget(parent)
{
	setupUi(this);
	calculation();
	distance_to_do = 0;
}
void DirectSimul::start_measures(){
	if(start->isEnabled()){
		calculation();
	}
}
void DirectSimul::calculation(){
	if(progressBar->value() < 100){
		label_3->setText(QString("%1").arg(gradiant->value()));
		label_4->setText(QString("%1").arg(slider->value()));
		refresh_time = 0;
		distance_to_do = (slider->value() * 25)/;
		QTimer::singleShot(10, this, SLOT(calculation()));
		QTimer::singleShot(200, this, SLOT(calculation()));
	}
	else{
		progressBar->valueChanged(0);
	}
}
void DirectSimul::refreshState(){
	if(refresh_time <= 20){

	}
}
