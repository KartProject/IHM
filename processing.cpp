#include "processing.h"
#include <QThread>

void Processing::run()
{
	usleep(2000);
	progressBar->reset();
}
