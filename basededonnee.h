#ifndef BASEDEDONNEE_H
#define BASEDEDONNEE_H

#include "ui_basededonnee.h"

class BaseDeDonnee : public QWidget, private Ui::BaseDeDonnee
{
	Q_OBJECT

public:
	explicit BaseDeDonnee(QWidget *parent = 0);
	void paintEvent(QPaintEvent *);
	void pushButton_clicked();
};

#endif // BASEDEDONNEE_H
