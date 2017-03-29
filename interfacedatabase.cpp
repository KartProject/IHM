#include "interfacedatabase.h"
#include <QCloseEvent>
#include <QtWidgets>

InterfaceDataBase::InterfaceDataBase(QWidget *parent) :
	QWidget(parent)
{
	setupUi(this);
}
void InterfaceDataBase::closeEvent(QCloseEvent *event) {
	QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Quitter?",
																tr("Êtes-vous sûr de vouloir quitter?\n"),
																QMessageBox::No | QMessageBox::Yes,
																QMessageBox::Yes);
	if (resBtn != QMessageBox::Yes) {
		event->ignore();
	} else {
		event->accept();
		this->close();
	}
}
