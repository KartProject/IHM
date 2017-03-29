#include "interfaceresults.h"
#include <QCloseEvent>
#include <QtWidgets>

InterfaceResults::InterfaceResults(QWidget *parent) :
	QWidget(parent)
{
	setupUi(this);
}
void InterfaceResults::closeEvent(QCloseEvent *event) {
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
