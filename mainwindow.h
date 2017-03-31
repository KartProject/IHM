#ifndef MAINWINDOW_H
#include <QFile>
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "interfaceresults.h"
#include "interfacedatabase.h"
#include "directsimul.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	/*void paintEvent(QPaintEvent *);*/

public slots:
	//Windows
	void callDatabase();
	void callResults();
	void callDirectSimul();
	//Synchronize
	void gradientDialModify();
	void gradientLineModify();
	void changeUnitGradientDeg();
	void changeUnitGradientRad();
	void changeUnitGradientPourc();
	void startMeasuring();
	void verifyMeasure();
	void saving();
	void savingAs();
	void addPoint();
	void erasePoint();
	void openFile();

private:
	void addCustomPoint(int numLine, QString point_pos, QString gradient_pos);
	bool sleeping(int ms);
	void initTable();
	bool setPourcentageBar(int pourcent);
	int taches_progress;
	int selected_gradiant_unit;
	bool saved;
	void reinitLabelProcess();
	QTableWidgetItem* newItem(const QString& s);
	QString savingAsWindow();
	int scanTablePoints(double pointToScan);
	void closeEvent(QCloseEvent *event);
	QFile file_opened;
	InterfaceDataBase db_window;
	InterfaceResults results_window;
	DirectSimul simul_window;

private slots:
	void addPointToResults();
};

#endif // MAINWINDOW_H
