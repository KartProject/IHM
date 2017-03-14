#include "ccourbe.h"
#include <QMouseEvent>
#include <QRect>
#include <QList>
#include <QPainter>
#include <QPaintEvent>
#include <QPrintDialog>

CCourbe::CCourbe(QWidget *parent) :
	QWidget(parent),
	mode(Construction)
{
	spline = new CBezier(this) ;
	setMouseTracking(true);
}

CCourbe::~CCourbe()
{
	delete spline ;
}

void CCourbe::mouseMoveEvent(QMouseEvent *event)
{
	QPoint point ;
	point.setX(LX(event->x()));
	point.setY(LY(event->y()));
	emit posChange(point, points.count());
	if ( points.isEmpty() )
		return ;
	if ( mode == Construction ) {
		points.removeLast();
		points << point ;
	}
	if ( mode == Modification ) {
		if ( itPoint == points.end() )
			return ;
		(*itPoint).setX(point.x());
		(*itPoint).setY(point.y());
	}
	update();
}

void CCourbe::mousePressEvent(QMouseEvent *event)
{
	QPoint point ;
	point.setX(LX(event->x()));
	point.setY(LY(event->y()));

	if ( mode == Construction ) {
		if ( !points.isEmpty() )
			points.removeLast();
		points << point ;
		if ( event->button() == Qt::LeftButton )
			points << point ;
		if ( event->button() == Qt::RightButton ) {
			itPoint = points.end() ;
			mode = Modification ;
		}
	}
	if ( mode == Modification ) {
		if ( event->button() == Qt::LeftButton ) {
			QList<QPoint>::iterator	it ;
			for ( it = points.begin() ; it != points.end() ; ++it ) {
				if ( poignee(*it).contains(point) )
					itPoint = it ;
			}
		}
	}
	update();
}

void CCourbe::mouseReleaseEvent(QMouseEvent *event)
{
	if ( mode == Modification ) {
		if ( event->button() == Qt::LeftButton )
			itPoint = points.end() ;
	}
}

QRect CCourbe::poignee(const QPoint &point)
{
	int size = 10 ;
	int x = point.x() - LX(size / 2) ;
	int y = point.y() - LY(size / 2) ;

	return QRect(x, y, size, size) ;
}

void CCourbe::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event) ;

	QPainter paint(this) ;
	dessine(paint) ;
}

void CCourbe::dessine(QPainter &paint, bool final)
{
	paint.save();
	paint.setWindow(0, 0, LARGEURVUE, HAUTEURVUE);

	QList<QPoint>::iterator it ;
	QPoint pt ;

	if ( !final ) {
		for ( it = points.begin() ; it != points.end() ; ++it ) {
			paint.setPen(Qt::SolidLine);
			paint.setBrush(it == itPoint ? Qt::red : Qt::blue);
			paint.drawRect(poignee(*it));
			paint.setPen(Qt::DotLine);
			paint.setPen(Qt::lightGray);
			if ( !pt.isNull() ) {
				paint.drawLine(pt, *it);
				spline->traceCourbe(paint, points, isFormGen) ;
			}
			pt = *it ;
		}
	}
	paint.restore();
}

void CCourbe::raz()
{
	points.clear();
	mode = Construction ;
	update() ;
	emit posChange(QPoint(0,0), 0);
}

void CCourbe::changeTypeCourbe(bool bezier, bool formGen)
{
	isBezier = bezier ;
	isFormGen = formGen ;

	delete spline ;
	if ( isBezier )
		spline = new CBezier ;
	else
		spline = new CBSpline ;
	update() ;
}

QString CCourbe::typeCourbe()
{
	QString s ;
	if ( isBezier ) {
		s = "courbe de Bézier - " ;
		if ( isFormGen )
			s += "Formule générale" ;
		else
			s += "Méthode des barycentres (sur 4 points max.)" ;
	}
	else {
		s = "courbe B-Spline (polynômes de Reisenfeld) - " ;
		if ( isFormGen )
			s += "Formule générale m = 3" ;
		else
			s += "Cas particulier m = 2" ;
	}
	return s ;
}

void CCourbe::imprime()
{
	QPrinter printer ;
	QPrintDialog* dlg = new QPrintDialog(&printer, this) ;
	if ( dlg->exec() != QDialog::Accepted )
		return ;
	QPainter paint ;
	if ( !paint.begin(&printer) )
		return ;
	int marge = (int)(0.1 * printer.width()) ;		// marge 10%
	int w = (int)(0.8 * printer.width()) ;			// zone impression 80%
	int h = (int)(height() * (double)w / width()) ;	// hauteur prop.

	paint.drawText(marge, 50, typeCourbe()) ;
	paint.drawText(marge, 75, QString("(%1 points)").arg(points.size())) ;
	paint.drawRect(marge, 100, w, h) ;
	paint.setViewport(marge, 100, w, h) ;

	dessine(paint, false) ;
	paint.end() ;
}
