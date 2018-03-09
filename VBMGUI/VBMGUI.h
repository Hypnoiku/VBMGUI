#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VBMGUI.h"
#include "VirtualBox.h"

class VBMGUI : public QMainWindow
{
	Q_OBJECT

public:
	VBMGUI(QWidget *parent = Q_NULLPTR);

public slots:
	void startVM();
	void compactHDD();

protected:
	void closeEvent(QCloseEvent *event);

private:
	Ui::VBMGUIClass ui;
	void progressBarStart(IProgress *progress);
};
