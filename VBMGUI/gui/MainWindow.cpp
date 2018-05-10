#include "MainWindow.h"
#include <comutil.h>
#include <comdef.h>
#include "VirtualBox.h"
#include <iostream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	if(virtualBox.error)
	{
		QMessageBox::critical(this, "Critical error", QString::fromStdString(errors.buildErrMsg(0, virtualBox.errorCode)));
	}
	else
	{
		virtualBox.getMachines();

		if (virtualBox.error)
		{
			QMessageBox::critical(this, "Critical error", QString::fromStdString(errors.buildErrMsg(1, virtualBox.errorCode)));
		}
		else
		{
			for (ULONG i = 0; i < virtualBox.machineAmount; i++)
			{
				ui.listWidget->addItem(QString::fromStdString(virtualBox.machineNames[i]));
			}
		}

		virtualBox.getMediums();

		if (virtualBox.error)
		{
			QMessageBox::critical(this, "Critical error", QString::fromStdString(errors.buildErrMsg(1, virtualBox.errorCode)));
		}
		else
		{
			for (ULONG i = 0; i < virtualBox.machineAmount; i++)
			{
				ui.listWidget_2->addItem(QString::fromStdString(virtualBox.mediumNames[i] + " - " += std::to_string(virtualBox.mediumSizes[i])));
			}
		}
	}
}

void MainWindow::startVM()
{
	IProgress *progress = virtualBox.startMachine(ui.listWidget->currentRow());

	if (virtualBox.error)
	{
		QMessageBox::critical(this, "Critical error", QString::fromStdString(errors.buildErrMsg(5, virtualBox.errorCode)));
	}

	progressBarStart(progress);
}

void MainWindow::compactHDD()
{
	IProgress *progress = virtualBox.compactMedium(ui.listWidget_2->currentRow());

	if(virtualBox.error)
	{
		QMessageBox::critical(this, "Critical error", QString::fromStdString(errors.buildErrMsg(2, virtualBox.errorCode)));
	}

	progressBarStart(progress);
}

void MainWindow::progressBarStart(IProgress *progress)
{
	/*ULONG *pBvalue = 0;

	progress->get_Percent(pBvalue);
	ui.progressBar->setValue((int)pBvalue);

	ui.progressBar->setMaximum(100);
	ui.progressBar->setMinimum(0);
	thread.create(progressBarPoll());
	thread.connect(this, SIGNAL(signalProgress(int)), ui.progressBar, SLOT(setValue(int)));*/
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	endApp();
}

void MainWindow::endApp()
{
	QApplication::quit();
}

void MainWindow::openAboutUI()
{
	std::string VBoxVer, VBoxSDKVer;
	virtualBox.getVBoxVers(VBoxVer, VBoxSDKVer);

	if (virtualBox.error == 1)
	{
		QMessageBox::critical(this, "Critical error", QString::fromStdString(errors.buildErrMsg(4, virtualBox.errorCode)));
	}
	else if(virtualBox.error == 2)
	{
		QMessageBox::critical(this, "Fatal error", QString::fromStdString(errors.getErrMsg(3)));
		QApplication::quit();
	}
	else
	{
		About *about = new About();
		about->getVers(QString::fromStdString(VBoxVer), QString::fromStdString(VBoxSDKVer));
		about->show();
	}
}

void MainWindow::openAboutQt()
{
	QMessageBox::aboutQt(this, "VBMGUI");
}