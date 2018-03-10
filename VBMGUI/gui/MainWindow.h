#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "VirtualBox.h"
#include "About.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);

public slots:
	void startVM();
	void compactHDD();
	void openAboutUI();

protected:
	void closeEvent(QCloseEvent *event);

private:
	Ui::MainWindowClass ui;
	void progressBarStart(IProgress *progress);
	void MainWindow::endApp();
};
