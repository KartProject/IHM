#include "mainwindow.h"
#include <QApplication>
#include "customsplashscreen.h"
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	MainWindow *main_win = new MainWindow();
	QPixmap splashImage("C:\\Users\\Tentyfire\\Documents\\GitHub\\IHM\\Kart_splash_small.png");
	customSplashScreen* splash = new customSplashScreen(splashImage);
	splash->setMessageRect(QRect(150, 50, 415, 14), Qt::AlignLeft); // Setting the message position.

	QColor color(200, 200, 200);

	QFont splashFont;
	splashFont.setFamily("Arial");
	splashFont.setBold(true);
	splashFont.setPixelSize(12);
	splashFont.setStretch(125);

	splash->setFont(splashFont);
	splash->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::SplashScreen);
	splash->show();

	splash->showStatusMessage(QObject::tr("Initialisation…"),color);
	QThread::sleep(1);

	/* Some code here */

	splash->showStatusMessage(QObject::tr("Connexion avec le Karting…"),color);
	QThread::sleep(1);

	main_win->show();
	splash->close();
    return a.exec();
}
