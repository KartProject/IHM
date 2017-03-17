#ifndef MAINWINDOW_H
#include <QFile>
#define MAINWINDOW_H

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	/*void paintEvent(QPaintEvent *);*/

public slots:
	void popupInvoc();
	void popupInvocDirectSimul();
	void gradientDialModify();
	void gradientLineModify();
	void changeUnitGradientDeg();
	void changeUnitGradientRad();
	void changeUnitGradientPourc();
	void start_measuring();
	void verify_measure();
	void saving();
	void saving_as();
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
	QString saving_as_window();
	int scan_table_points(double pointToScan);
	void closeEvent(QCloseEvent *event);
	QFile file_opened;
};

#endif // MAINWINDOW_H
