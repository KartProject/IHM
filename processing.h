#ifndef PROCESSING_H
#define PROCESSING_H

#include <QThread>

class Processing : public QThread
{
	Q_OBJECT

protected:
	void run();
};

#endif // PROCESSING_H
