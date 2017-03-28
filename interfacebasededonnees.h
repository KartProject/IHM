#ifndef INTERFACEBASEDEDONNEES_H
#define INTERFACEBASEDEDONNEES_H

#include "ui_interfacebasededonnees.h"

class InterfaceBaseDeDonnees : public QWidget, private Ui::InterfaceBaseDeDonnees
{
	Q_OBJECT

public:
	explicit InterfaceBaseDeDonnees(QWidget *parent = 0);
};

#endif // INTERFACEBASEDEDONNEES_H
