#include <QThread>
#ifndef SLEEPTHREAD_H
#define SLEEPTHREAD_H


class SleeperThread : public QThread
{
public:
	static void msleep(unsigned long msecs)
	{
		QThread::msleep(msecs);
	}
};

#endif
