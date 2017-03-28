#ifndef INTERFACEMODBUS_H
#define INTERFACEMODBUS_H

#include "ui_interfacemodbus.h"

class InterfaceModbus : public QWidget, private Ui::InterfaceModbus
{
	Q_OBJECT

public:
	explicit InterfaceModbus(QWidget *parent = 0);
};

#endif // INTERFACEMODBUS_H
