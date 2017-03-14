#include "mainwindow.h"
#include "basededonnee.h"
#include "directsimul.h"
#include <QtWidgets>
#include <QRect>
/*#include <QPainter>
#include <QPaintEvent>*/
#include <cmath>
#include "processing.h"
#ifdef Q_OS_WIN
#include <windows.h> // for Sleep
#endif

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	QIcon icone = QIcon();
	icone.addFile("C:/Users/Tentyfire/Desktop/kart.ico");
	setWindowIcon(icone);
	//file:///C:/Users/Tentyfire/Desktop/kart.ico
	setupUi(this);
	initTable();
	connect(show_bdd_button, SIGNAL(clicked()), this, SLOT(popupInvoc()));
	connect(start_measures, SIGNAL(clicked()), this, SLOT(start_measuring()));
	connect(gradient_slide, SIGNAL(sliderReleased()), this, SLOT(gradientDialModify()));
	connect(gradient_slide, SIGNAL(sliderMoved(int)), this, SLOT(gradientDialModify()));
	connect(gradient_spin_box, SIGNAL(valueChanged(double)), this, SLOT(gradientLineModify()));
	connect(gradient_degrees,SIGNAL(clicked()),this,SLOT(changeUnitGradientDeg()));
	connect(gradient_pourcent,SIGNAL(clicked()),this,SLOT(changeUnitGradientPourc()));
	connect(gradient_radian,SIGNAL(clicked()),this,SLOT(changeUnitGradientRad()));
	connect(save,SIGNAL(triggered()),this,SLOT(saving()));
	connect(save_as,SIGNAL(triggered()),this,SLOT(saving_as()));
	connect(add_point,SIGNAL(clicked()),this,SLOT(addPoint()));
	connect(erase_point, SIGNAL(clicked()), this, SLOT(erasePoint()));
	taches_progress = 1;
	selected_gradiant_unit = 1;
	saved = 0;
	/*QPaintEvent e(QRect(5,5,500,500));
	paintEvent(&e);*/
}
QTableWidgetItem* MainWindow::newItem(const QString& s){
	QTableWidgetItem* item = new QTableWidgetItem;
	item->setFlags(item->flags() ^ Qt::ItemIsEditable);
	item->setData(Qt::DisplayRole, s.toDouble());
	return item;
}
void MainWindow::popupInvocDirectSimul(){
	DirectSimul *popupDirectSimul = new DirectSimul(this);
	popupDirectSimul->setWindowFlags(Qt::Window);
	popupDirectSimul->show();
}
int MainWindow::scan_table_points(double pointToScan){
	QList<QTableWidgetItem *> ItemList = measures->findItems(QString("%1").arg(pointToScan), Qt::MatchExactly);
	if(ItemList.count()){
		int index;
		for (index = 0;index < ItemList.count();index++) {
			if(ItemList.at(index)->column() == 0){
				QMessageBox::StandardButton reply;
				reply = QMessageBox::question(this, "Remplacer?", "Le point kilométrique existe déjà! Le remplacer avec la nouvelle pente?",
				QMessageBox::Yes|QMessageBox::No);
				if (reply == QMessageBox::Yes) {
					measures->removeRow(ItemList.at(index)->row());
					return 2;
				} else {
					return 0;
				}
			}
		}
		return 1;
	}
	return 1;
}
void MainWindow::addPoint(){
	if(point->value() > distance->value()){
		QMessageBox::warning(this, "Attention!", "Attention! Le point kilométrique ne sera pas pris en compte, augmentez donc la distance du parcours");
	}
	int actionToDo = scan_table_points((double)point->value());
	if(actionToDo){
		Qt::SortOrder the_order = measures->horizontalHeader()->sortIndicatorOrder();
		int the_column = measures->horizontalHeader()->sortIndicatorSection();
		int new_point;
		if(actionToDo == 2){
			new_point = points->text().toInt()-1;
		}
		else{
			new_point = points->text().toInt();
		}
		measures->setRowCount(new_point+1) ;
		measures->setSortingEnabled(false);
		measures->setRowHeight(new_point, 22) ;
		measures->setItem(new_point, 0, newItem(QString("%1").arg((double)point->value())));
		double the_gradient = (double)gradient_spin_box->value();
		if(gradient_slide->maximum() == 158){
			qreal value = gradient_spin_box->value();
			double value2 = qTan(value)*100;
			the_gradient = value2;
		}
		else if(gradient_slide->maximum() == 900){
			qreal value = gradient_spin_box->value()*(M_PI/180.0);
			double value2 = qTan(value)*100;
			the_gradient = value2;
		}
		points->setText(QString("%1").arg(new_point + 1));
		measures->setItem(new_point, 1, newItem(QString("%1").arg(the_gradient)));
		measures->repaint() ;
		measures->setSortingEnabled(true);
		measures->sortByColumn(the_column, the_order);
	}
}
void MainWindow::reinitLabelProcess(){
	progressLabel->setText("Appuyez sur \"Démarer\" pour lancer la simulation");
}
QString MainWindow::saving_as_window(){
	QString fichier = QFileDialog::getSaveFileName(this,
		tr("Enregistrer Sous..."),
		QDir::homePath(),
		"Fichiers CSV (*.csv);;Tout les fichiers (*.*)"
	);
	return fichier;
}
void MainWindow::saving_as(){
	QString filename = saving_as_window();
	QFile file( filename );
	if ( file.open(QIODevice::ReadWrite) ){
		QTextStream stream( &file );
		stream << "Point kilométrique (km);Pente (%)" << endl;
		for(int i = 0;i < measures->rowCount();i++){
			stream << measures->item(i,0)->text() << ";" << measures->item(i,1)->text() << endl;
		}
		setWindowTitle("MAJENI - Karting Simulator - ");
		saved = 1;
	}
	else{
		setWindowTitle("MAJENI - Karting Simulator - ");
	}

}
void MainWindow::saving(){
	if(!saved){
		QString filename = saving_as_window();
		saved = 1;
		QFile file( filename );
		if ( file.open(QIODevice::ReadWrite) ){
			QTextStream stream( &file );
			stream << "Point kilométrique (km);Pente (%)" << endl;
			stream << "1;2" << endl;
			setWindowTitle("MAJENI - Karting Simulator - ");
			saved = 1;
		}
	}
	setWindowTitle("MAJENI - Karting Simulator");
}
void MainWindow::start_measuring(){
	QTimer::singleShot(2000, this, SLOT(verify_measure()));
	taches_progress = 1;
	progressLabel->setText(QString::number(taches_progress) + "/" + QString::number(1*2) + " Envoi des données...");
}
void MainWindow::verify_measure(){
	if(round((double)((50.0/1.0)+progressBar->value())) > 100){
		progressBar->setValue(100);
		progressLabel->setText("Appuyez sur \"Démarer\" pour lancer la simulation");
	}
	else{
		progressBar->setValue(round((double)((double)taches_progress * ((double)50.0/1.0))));
	}
	if(progressBar->value() < 100){
		QTimer::singleShot(2000, this, SLOT(verify_measure()));
		taches_progress++;
		if(taches_progress % 2 == 1){
			progressLabel->setText(QString::number(taches_progress) + "/" + QString::number(1*2) + " Envoi des données...");
		}
		else{
			progressLabel->setText(QString::number(taches_progress) + "/" + QString::number(1*2) + " Reception de la simulation...");
		}
	}
	else{
		progressBar->reset();
		progressLabel->setText("Appuyez sur \"Démarer\" pour lancer la simulation");
	}
}
bool MainWindow::setPourcentageBar(int pourcent) //return "true" if success and "false" if error
{
	int actualPourcent = progressBar->value();
	if(pourcent > 0){
		if(pourcent > 100){
			return false;
		}
	}
	else{
		return false;
	}
	for(int i = actualPourcent + 1;i < pourcent;i++){
		progressBar->setValue(actualPourcent + i);
		sleeping(15);
	}
	return true;
}
bool MainWindow::sleeping(int ms) //return "true" if success and "false" if error
{
	if(ms < 0){
		return false;
	}

#ifdef Q_OS_WIN
	Sleep(uint(ms));
	return true;
#else
	struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
	nanosleep(&ts, NULL);
	return true;
#endif

}
void MainWindow::initTable()
{
	measures->clear() ;

	measures->setColumnCount(2) ;
	measures->setColumnWidth(0, 325) ;
	measures->setColumnWidth(1, 325) ;
	measures->verticalHeader()->setVisible(false) ;
	measures->setAlternatingRowColors(true) ;

	QStringList	titles ;
	titles << "Points Kilométrique(km)" << "Pentes (%)" ;
	measures->setHorizontalHeaderLabels(titles) ;
	measures->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch) ;
	measures->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Interactive) ;

	measures->setSelectionBehavior(QAbstractItemView::SelectRows) ;
	measures->horizontalHeader()->setSortIndicatorShown(true);
	measures->setSortingEnabled(true);
	measures->sortByColumn(0, Qt::AscendingOrder);
}
void MainWindow::erasePoint(){
	QModelIndexList indexes =  measures->selectionModel()->selectedRows();
	int countRow = indexes.count();

	bool flagDif = false;
	for( int i = countRow; i > 1; i--)
		if (indexes.at(i-1).row()-1 != indexes.at(i-2).row())
		   flagDif = true;
	int new_point = points->text().toInt();
	if (!flagDif)
		measures->model()->removeRows(indexes.at(0).row(),countRow,QModelIndex());
	else
		for( int i = countRow; i > 0; i--)
			measures->model()->removeRow( indexes.at(i-1).row(), QModelIndex());
	measures->setRowCount(new_point - countRow) ;
	points->setText(QString("%1").arg(new_point - countRow));
}
/*void MainWindow::paintEvent(QPaintEvent *){
	QPainter painter(this);
	//painter.setViewport(50, 50, 50, 50);
	qreal xc = width() * 0.5;
	qreal yc = height() * 0.5;

	painter.setPen(Qt::black);

	// draw the cross lines.
	painter.drawLine(xc, rect().top(), xc, rect().bottom());
	painter.drawLine(rect().left(), yc, rect().right(), yc);

	painter.setBrush(Qt::white);
	painter.setPen(Qt::blue);

	// Draw a 13x17 rectangle rotated to 45 degrees around its center-point
	// in the center of the canvas.

	// translates the coordinate system by xc and yc
	painter.translate(xc, yc);

	// then rotate the coordinate system by 45 degrees
	painter.rotate(45);

	// we need to move the rectangle that we draw by rx and ry so it's in the center.
	qreal rx = -(13 * 0.5);
	qreal ry = -(17 * 0.5);
	painter.drawRect(QRect(rx, ry, 13, 17));
	QRectF rectangle(10.0, 20.0, 80.0, 60.0);
	int startAngle = 30 * 16;
	int spanAngle = 120 * 16;
}*/

void MainWindow::popupInvoc(){
	BaseDeDonnee *popup = new BaseDeDonnee(this);
	popup->setWindowFlags(Qt::Window);
	popup->show();
}
void MainWindow::gradientDialModify(){
	double divide_spin;
	setWindowTitle("MAJENI - Karting Simulator*");
	saved = 0;
	if(gradient_degrees->isChecked()){
		divide_spin = 10;
	}
	else{
		divide_spin = 100;
	}
	gradient_spin_box->setValue(gradient_slide->value()/divide_spin);
}
void MainWindow::gradientLineModify(){
	setWindowTitle("MAJENI - Karting Simulator*");
	saved = 0;
	int multiple_spin;
	if(gradient_degrees->isChecked()){
		multiple_spin = 10;
	}
	else{
		multiple_spin = 100;
	}
	gradient_slide->setValue((int)(gradient_spin_box->value()*multiple_spin));
}
void MainWindow::changeUnitGradientRad(){
	if(gradient_radian->isChecked() && (selected_gradiant_unit != 3)){
		setWindowTitle("MAJENI - Karting Simulator*");
		saved = 0;
		selected_gradiant_unit = 3;
		double range = M_PI/2.0;
		if(gradient_slide->maximum() == 900){
			gradient_spin_box->setValue((double)(gradient_spin_box->value())*(M_PI/180.0));
		}
		else{
			qreal value = gradient_spin_box->value();
			double value2= qAtan(value/100);
			gradient_spin_box->setValue(value2);
		}
		gradient_spin_box->setRange(-range,range);
		gradient_slide->setRange(-158, 158);
	}
}
void MainWindow::changeUnitGradientDeg(){
	if(gradient_degrees->isChecked() && (selected_gradiant_unit != 2)){
		setWindowTitle("MAJENI - Karting Simulator*");
		saved = 0;
		selected_gradiant_unit = 2;
		if(gradient_slide->maximum() == 158){
			double range = 90;
			gradient_spin_box->setRange(-range,range);
			gradient_slide->setRange(-900, 900);
			gradient_spin_box->setValue((double)(gradient_spin_box->value())*(180.0/M_PI));
		}
		else{
			qreal value = gradient_spin_box->value();
			double value2 = qAtan(value/100)*(180.0/M_PI);
			gradient_spin_box->setValue(value2);
			double range = 90;
			gradient_spin_box->setRange(-range,range);
			gradient_slide->setRange(-900, 900);
		}
		//gradient_slide->setValue(round((((double)(gradient_spin_box->value()))*(180.0/M_PI))));
	}
}
void MainWindow::changeUnitGradientPourc(){
	if(gradient_pourcent->isChecked() && (selected_gradiant_unit != 1)){
		setWindowTitle("Karting Simulator*");
		saved = 0;
		selected_gradiant_unit = 1;
		double range = 10000;
		gradient_spin_box->setRange(-range,range);
		bool is_actual_rad = 0;
		if(gradient_slide->maximum() == 158){
			is_actual_rad = 1;
		}
		gradient_slide->setRange(-1000000, 1000000);
		if(is_actual_rad){
			qreal value = gradient_spin_box->value();
			double value2 = qTan(value)*100;
			gradient_spin_box->setValue(value2);
		}
		else{
			qreal value = gradient_spin_box->value()*(M_PI/180.0);
			double value2 = qTan(value)*100;
			gradient_spin_box->setValue(value2);
		}
	}
}
