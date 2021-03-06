#ifndef INTERFACERESULTS_H
#define INTERFACERESULTS_H

#include "ui_interfaceresults.h"

class InterfaceResults : public QWidget, private Ui::InterfaceResults
{
	Q_OBJECT

public:
	explicit InterfaceResults(QWidget *parent = 0);
	void addValue(QTableWidgetItem *new_gradient, QTableWidgetItem *new_km_point, QTableWidgetItem *new_voltage, QTableWidgetItem *new_couple, QTableWidgetItem *new_power);
	QTableWidgetItem* newItem(const QString& s);

private:
	void closeEvent(QCloseEvent *event);
	void initTable();
};

#endif // INTERFACERESULTS_H
