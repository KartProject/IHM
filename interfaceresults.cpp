#include "interfaceresults.h"
#include <QCloseEvent>
#include <QtWidgets>

InterfaceResults::InterfaceResults(QWidget *parent) :
	QWidget(parent)
{
	setupUi(this);
	initTable();
}
void InterfaceResults::closeEvent(QCloseEvent *event)
{
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
void InterfaceResults::addValue(QTableWidgetItem *new_gradient, QTableWidgetItem *new_km_point, QTableWidgetItem *new_voltage, QTableWidgetItem *new_couple, QTableWidgetItem *new_power)
{
	Qt::SortOrder the_order = measures->horizontalHeader()->sortIndicatorOrder();
	int the_column = measures->horizontalHeader()->sortIndicatorSection();
	int new_point = measures->rowCount();
	measures->setRowCount(new_point+1);
	measures->setSortingEnabled(false);
	measures->setRowHeight(new_point, 22) ;
	measures->setItem(new_point, 0, new_km_point);
	measures->setItem(new_point, 1, new_gradient);
	measures->setItem(new_point, 2, new_voltage);
	measures->setItem(new_point, 3, new_couple);
	measures->setItem(new_point, 4, new_power);
	measures->repaint() ;
	measures->setSortingEnabled(true);
	measures->sortByColumn(the_column, the_order);
}
QTableWidgetItem* InterfaceResults::newItem(const QString& s){
	QTableWidgetItem* item = new QTableWidgetItem;
	item->setFlags(item->flags() ^ Qt::ItemIsEditable);
	item->setData(Qt::DisplayRole, s.toDouble());
	return item;
}
void InterfaceResults::initTable()
{
	measures->clear() ;

	measures->setColumnCount(5) ;
	measures->setColumnWidth(0, 325) ;
	measures->setColumnWidth(1, 325) ;
	measures->setColumnWidth(2, 325) ;
	measures->setColumnWidth(3, 325) ;
	measures->setColumnWidth(4, 325) ;
	measures->verticalHeader()->setVisible(false) ;
	measures->setAlternatingRowColors(true) ;

	QStringList	titles ;
	titles << "Points Kilométrique(km)" << "Pentes (%)" << "Vitesse" << "Courant" << "Puissance";
	measures->setHorizontalHeaderLabels(titles) ;
	measures->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch) ;
	measures->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Interactive) ;

	measures->setSelectionBehavior(QAbstractItemView::SelectRows) ;
	measures->horizontalHeader()->setSortIndicatorShown(true);
	measures->setSortingEnabled(true);
	measures->sortByColumn(0, Qt::AscendingOrder);
}
