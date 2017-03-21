#ifndef DIRECTSIMUL_H
#define DIRECTSIMUL_H

#include "ui_directsimul.h"

class DirectSimul : public QWidget, private Ui::DirectSimul
{
	Q_OBJECT

public:
	explicit DirectSimul(QWidget *parent = 0);

private slots:
	void calculation();
	void startMeasures();
	void refreshState();

private:
	double distance_to_do;
	int refresh_time;
	double total_distance;
};

#endif // DIRECTSIMUL_H
