#include "VBMGUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	VBMGUI w;
	w.show();
	return a.exec();
}
