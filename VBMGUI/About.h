#pragma once

#include <QWidget>
#include "ui_About.h"

class About : public QWidget
{
	Q_OBJECT

public:
	About(QWidget *parent = Q_NULLPTR);
	void getVers(QString VBoxVer, QString VBoxSDKVer);
	~About();

private:
	Ui::About ui;
};
