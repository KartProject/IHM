#ifndef OPENINGAPP_H
#define OPENINGAPP_H

#include "ui_openingapp.h"

class OpeningApp : public QDialog, private Ui::OpeningApp
{
	Q_OBJECT

public:
	explicit OpeningApp(QWidget *parent = 0);
};

#endif // OPENINGAPP_H
