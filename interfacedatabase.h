#ifndef INTERFACEBASEDEDONNEES_H
#define INTERFACEBASEDEDONNEES_H

#include "ui_interfacebasededonnees.h"

class InterfaceDataBase : public QWidget, private Ui::InterfaceBaseDeDonnees
{
	Q_OBJECT

public:
	explicit InterfaceDataBase(QWidget *parent = 0);

private:
	void closeEvent(QCloseEvent *event);
};

#endif // INTERFACEBASEDEDONNEES_H
