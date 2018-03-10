#include "MainWindow.h"
#include <comutil.h>
#include <comdef.h>
#include "VirtualBox.h"
#include "VirtualBox_i.c"
#include <iostream>
#include <QMessageBox>
#include <string>

IVirtualBox *virtualBox;
ISession *session;
IVirtualBoxClient *virtualBoxClient;

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	/* Initialize the COM subsystem. */
	CoInitialize(NULL);

	HRESULT rc;
	/* Instantiate the VirtualBox root object. */
	rc = CoCreateInstance(CLSID_VirtualBoxClient, /* the VirtualBoxClient object */
		NULL,                   /* no aggregation */
		CLSCTX_INPROC_SERVER,   /* the object lives in the current process */
		IID_IVirtualBoxClient,  /* IID of the interface */
		(void**)&virtualBoxClient);
	if (SUCCEEDED(rc))
	{
		rc = virtualBoxClient->get_VirtualBox(&virtualBox);
		if (SUCCEEDED(rc))
		{
			SAFEARRAY *machinesArray = NULL;

			rc = virtualBox->get_Machines(&machinesArray);
			if (SUCCEEDED(rc))
			{
				IMachine **machines;

				rc = SafeArrayAccessData(machinesArray, (void **)&machines);
				if (SUCCEEDED(rc))
				{
					for (ULONG i = 0; i < machinesArray->rgsabound[0].cElements; ++i)
					{
						BSTR str;

						rc = machines[i]->get_Name(&str);
						if (SUCCEEDED(rc))
						{
							ui.label->setText(QString(_com_util::ConvertBSTRToString(str)));
							ui.listWidget->addItem(QString(_com_util::ConvertBSTRToString(str)));
							SysFreeString(str);
						}
					}

					SafeArrayUnaccessData(machinesArray);
				}

				SafeArrayDestroy(machinesArray);
			}

			SAFEARRAY *mediumArray = NULL;
			
			rc = virtualBox->get_HardDisks(&mediumArray);
			if (SUCCEEDED(rc))
			{
				IMedium **mediums;

				rc = SafeArrayAccessData(mediumArray, (void **)&mediums);
				if (SUCCEEDED(rc))
				{
					for (ULONG i = 0; i < mediumArray->rgsabound[0].cElements; ++i)
					{
						BSTR str;
						LONG64 size = 0;

						rc = mediums[i]->get_Name(&str);
						rc = mediums[i]->get_Size(&size);

						if (SUCCEEDED(rc))
						{
							ui.label->setText(QString(_com_util::ConvertBSTRToString(str)));
							ui.listWidget_2->addItem(QString(((std::string)_com_util::ConvertBSTRToString(str) + " - " + std::to_string(size)).c_str()));
							SysFreeString(str);
						}
					}

					SafeArrayUnaccessData(mediumArray);
				}

				SafeArrayDestroy(mediumArray);
			}
		}
		else
			QMessageBox::critical(this, "Critical error", QString("Error creating VirtualBox instance!rc = 0x" && rc));
	}
}

void MainWindow::startVM()
{
	HRESULT rc;
	int pos = ui.listWidget->currentRow();
	IProgress *progress;
	ULONG *pBvalue = 0;
	SAFEARRAY *machinesArray = NULL;

	rc = virtualBox->get_Machines(&machinesArray);
	if (SUCCEEDED(rc))
	{
		IMachine **machines;
		rc = SafeArrayAccessData(machinesArray, (void **)&machines);
		if (SUCCEEDED(rc))
		{
			rc = virtualBoxClient->get_Session(&session);
			machines[ui.listWidget->currentRow()]->LaunchVMProcess(session, _com_util::ConvertStringToBSTR("gui"), NULL, &progress);
			SafeArrayUnaccessData(machinesArray);
		}

		SafeArrayDestroy(machinesArray);
	}

	progressBarStart(progress);
}

void MainWindow::compactHDD()
{
	HRESULT rc;
	int pos = ui.listWidget_2->currentRow();
	IProgress *progress;
	ULONG *pBvalue = 0;
	SAFEARRAY *mediumArray = NULL;

	rc = virtualBox->get_HardDisks(&mediumArray);
	if (SUCCEEDED(rc))
	{
		IMedium **mediums;

		rc = SafeArrayAccessData(mediumArray, (void **)&mediums);
		if (SUCCEEDED(rc))
		{
			rc = mediums[pos]->Compact(&progress);
			if (FAILED(rc))
			{
				QMessageBox::critical(this, "Critical error", QString("Error compacting HDD!rc = 0x" + rc));
			}
			SafeArrayUnaccessData(mediumArray);
		}

		SafeArrayDestroy(mediumArray);
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
	virtualBox->Release();
	virtualBoxClient->Release();
	QApplication::quit();
}

void MainWindow::openAboutUI() {
	HRESULT rc;
	BSTR VBoxVer;
	BSTR VBoxSDKVer;
	if (virtualBox != NULL)
	{
		rc = virtualBox->get_Version(&VBoxVer);
		rc = virtualBox->get_APIVersion(&VBoxSDKVer);
	}

	if (FAILED(rc) || virtualBox == NULL)
	{
		QMessageBox::critical(this, "Fatal error", QString("VirtualBox COM interface is missing! Exiting!"));
		QApplication::quit();
	}

	About *about = new About();
	about->getVers(QString(_com_util::ConvertBSTRToString(VBoxVer)), QString(_com_util::ConvertBSTRToString(VBoxSDKVer)));
	about->show();
}