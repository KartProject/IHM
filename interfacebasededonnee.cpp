#include "basededonnee.h"
#include <QPainter>
#include <QPaintEvent>


BaseDeDonnee::BaseDeDonnee(QWidget *parent) :
	QWidget(parent)
{
	setupUi(this);
	QPaintEvent e(QRect(5,5,50,50));
	paintEvent(&e);
}
void BaseDeDonnee::pushButton_clicked()
{
	update();
}

void BaseDeDonnee::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
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
}
