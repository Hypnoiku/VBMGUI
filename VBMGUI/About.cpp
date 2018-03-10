#include "About.h"

About::About(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void About::getVers(QString VBoxVer, QString VBoxSDKVer)
{
	ui.label_2->setText(VBoxVer);
	ui.label_3->setText(ui.label_3->text() + VBoxSDKVer);
}

About::~About()
{
}