#ifndef INTERFACERESULTS_H
#define INTERFACERESULTS_H

#include "ui_interfaceresults.h"

class InterfaceResults : public QWidget, private Ui::InterfaceResults
{
	Q_OBJECT

public:
	explicit InterfaceResults(QWidget *parent = 0);
};

#endif // INTERFACERESULTS_H
