#ifndef DIRECTSIMUL_H
#define DIRECTSIMUL_H

#include "ui_directsimul.h"

class DirectSimul : public QWidget, private Ui::DirectSimul
{
	Q_OBJECT

public:
	explicit DirectSimul(QWidget *parent = 0);
};

#endif // DIRECTSIMUL_H
