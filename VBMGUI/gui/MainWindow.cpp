#include "MainWindow.h"
#include <comutil.h>
#include <comdef.h>
#include "VirtualBox.h"
#include <QMessageBox>
#include <iomanip>
#include "pbTick.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

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
			for (int i = 0; i < virtualBox.machineAmount; i++)
			{
				ui.VMList->addItem(QString::fromStdString(virtualBox.machineNames[i]));
			}
		}

		virtualBox.getMediums();

		if (virtualBox.error)
		{
			QMessageBox::critical(this, "Critical error", QString::fromStdString(errors.buildErrMsg(1, virtualBox.errorCode)));
		}
		else
		{
			for (int i = 0; i < virtualBox.mediumAmount; i++)
			{
				std::string type = virtualBox.mediumSize.type[i];
				std::string maxType = virtualBox.mediumSize.maxType[i];
				std::stringstream size, maxSize;
				size << std::fixed << std::setprecision(2) << virtualBox.mediumSize.sizes[i];
				maxSize << std::fixed << std::setprecision(2) << virtualBox.mediumSize.maxSizes[i];

				QStringList itemStList;
				itemStList << QString::fromStdString(virtualBox.mediumNames[i]);
				itemStList << QString::fromStdString(size.str() + " " + type);
				itemStList << QString::fromStdString(maxSize.str() + " " + maxType);
				QTreeWidgetItem *item = new QTreeWidgetItem(itemStList);

				ui.HDDList->addTopLevelItem(item);
			}
		}
	}
}

void MainWindow::startVM()
{
	IProgress *progress = virtualBox.startMachine(ui.VMList->currentRow());

	if (virtualBox.error)
	{
		QMessageBox::critical(this, "Critical error", QString::fromStdString(errors.buildErrMsg(5, virtualBox.errorCode)));
	}

	progressBarStart(progress);
}

void MainWindow::compactHDD()
{
	IProgress *progress = virtualBox.compactMedium(ui.HDDList->indexOfTopLevelItem(ui.HDDList->currentItem()));

	if(virtualBox.error)
	{
		QMessageBox::critical(this, "Critical error", QString::fromStdString(errors.buildErrMsg(2, virtualBox.errorCode)));
	}

	progressBarStart(progress);
}

void MainWindow::progressBarStart(IProgress *progress)
{
	QThread *thread = new QThread();
	pbTick *tick = new pbTick(progress);
	tick->moveToThread(thread);
	ui.progressBar->setMaximum(100);
	ui.progressBar->setMinimum(0);
	ui.progressBar->setValue(0);

	connect(tick, SIGNAL(setPB(int)), ui.progressBar, SLOT(setValue(int)));

	tick->tick();
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
		endApp();
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
