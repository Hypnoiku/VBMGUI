#include "pbTick.h"

pbTick::pbTick(IProgress *progress)
{
	this->progress = progress;
}

void pbTick::tick()
{
	BOOL completed = false;
	progress->get_Completed(&completed);
	ULONG percent = 0;

	while(!completed)
	{
		progress->get_Percent(&percent);
		emit setPB((int)percent);

		QThread::sleep(1);
		progress->get_Completed(&completed);
	}

	emit setPB(100);
}

pbTick::~pbTick()
{
	progress->Release();
}
