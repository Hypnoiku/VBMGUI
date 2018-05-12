#pragma once

#include <VirtualBox.h>
#include <QThread>

class pbTick : public QObject
{
	Q_OBJECT

public:
	pbTick::pbTick(IProgress *progress);
	void pbTick::tick();
	~pbTick();

signals:
	void setPB(int);
	
private:
	IProgress * progress;
};
