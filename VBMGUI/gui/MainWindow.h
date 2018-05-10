#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "VirtualBox.h"
#include "About.h"
#include "VBox.h"
#include "err.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	VBox virtualBox;

	MainWindow(QWidget *parent = Q_NULLPTR);

public slots:
	void startVM();
	void compactHDD();
	void openAboutUI();
	void openAboutQt();

protected:
	void closeEvent(QCloseEvent *event);

private:
	Ui::MainWindowClass ui;
	void progressBarStart(IProgress *progress);
	void MainWindow::endApp();
	err errors;
};
