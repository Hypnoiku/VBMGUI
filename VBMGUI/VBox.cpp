#include "VBox.h"
#include "VirtualBox_i.c"

VBox::VBox()
{
	CoInitialize(NULL);

	rc = CoCreateInstance(CLSID_VirtualBoxClient,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IVirtualBoxClient,
		(void**)&virtualBoxClient);
	if(FAILED(rc))
	{
		error = 1;
		errorCode = rc;
		return;
	}

	rc = virtualBoxClient->get_VirtualBox(&virtualBox);
	if (FAILED(rc))
	{
		error = 1;
		errorCode = rc;
		return;
	}
}

void VBox::getMachines()
{
	resetError();

	SAFEARRAY *machinesArray = NULL;

	rc = virtualBox->get_Machines(&machinesArray);
	if (SUCCEEDED(rc))
	{
		rc = SafeArrayAccessData(machinesArray, (void **)&machines);
		if (SUCCEEDED(rc))
		{
			machineNames = new std::string[machinesArray->rgsabound[0].cElements];
			machineAmount = machinesArray->rgsabound[0].cElements;

			for (ULONG i = 0; i < machinesArray->rgsabound[0].cElements; ++i)
			{
				BSTR str;

				rc = machines[i]->get_Name(&str);
				if (SUCCEEDED(rc))
				{
					machineNames[i] = _com_util::ConvertBSTRToString(str);
					SysFreeString(str);
				}
				else
				{
					error = 1;
					errorCode = rc;
				}
			}
		}
		else
		{
			error = 1;
			errorCode = rc;
		}

		SafeArrayUnaccessData(machinesArray);
		SafeArrayDestroy(machinesArray);
	}
	else
	{
		error = 1;
		errorCode = rc;
	}
}

void VBox::getMediums()
{
	resetError();

	ByteMath bm;

	SAFEARRAY *mediumArray = NULL;

	rc = virtualBox->get_HardDisks(&mediumArray);
	if (SUCCEEDED(rc))
	{
		rc = SafeArrayAccessData(mediumArray, (void **)&mediums);

		if (SUCCEEDED(rc))
		{
			mediumNames = new std::string[mediumArray->rgsabound[0].cElements];
			mediumSizes = new FLOAT[mediumArray->rgsabound[0].cElements];
			mediumMaxSizes = new FLOAT[mediumArray->rgsabound[0].cElements];
			mediumAmount = mediumArray->rgsabound[0].cElements;

			for (ULONG i = 0; i < mediumArray->rgsabound[0].cElements; ++i)
			{
				BSTR str;
				LONG64 size = 0;
				LONG64 maxSize = 0;

				rc = mediums[i]->get_Name(&str);
				rc = mediums[i]->get_Size(&size);
				rc = mediums[i]->get_LogicalSize(&maxSize);

				if (SUCCEEDED(rc))
				{
					mediumNames[i] = _com_util::ConvertBSTRToString(str);
					mediumSizes[i] = bm.bToGB(size);
					mediumMaxSizes[i] = bm.bToGB(maxSize);
					SysFreeString(str);
				}else
				{
					error = 1;
					errorCode = rc;
				}
			}
		}
		else
		{
			error = 1;
			errorCode = rc;
		}

		SafeArrayUnaccessData(mediumArray);
		SafeArrayDestroy(mediumArray);
	}
	else
	{
		error = 1;
		errorCode = rc;
	}
}

IProgress* VBox::startMachine(int position)
{
	resetError();

	HRESULT rc;
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
			machines[position]->LaunchVMProcess(session, _com_util::ConvertStringToBSTR("gui"), NULL, &progress);
			SafeArrayUnaccessData(machinesArray);
		}
		else
		{
			error = 1;
			errorCode = rc;
		}

		SafeArrayDestroy(machinesArray);
	}
	else
	{
		error = 1;
		errorCode = rc;
	}

	return progress;
}

IProgress* VBox::compactMedium(int position)
{
	resetError();

	HRESULT rc;
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
			rc = mediums[position]->Compact(&progress);
			if (FAILED(rc))
			{
				error = 1;
				errorCode = rc;
			}
			SafeArrayUnaccessData(mediumArray);
		}
		else
		{
			error = 1;
			errorCode = rc;
		}

		SafeArrayDestroy(mediumArray);
	}
	else
	{
		error = 1;
		errorCode = rc;
	}

	return progress;
}

void VBox::getVBoxVers(std::string &VBoxVerStr, std::string &VBoxSDKVerStr)
{
	resetError();

	HRESULT rc;
	BSTR VBoxVer;
	BSTR VBoxSDKVer;
	if (virtualBox != NULL)
	{
		rc = virtualBox->get_Version(&VBoxVer);
		rc = virtualBox->get_APIVersion(&VBoxSDKVer);
	}

	if (FAILED(rc))
	{
		error = 1;
		errorCode = rc;
	}
	else if (virtualBox == NULL)
	{
		error = 2;
	}
	else
	{
		VBoxVerStr = _com_util::ConvertBSTRToString(VBoxVer);
		VBoxSDKVerStr = _com_util::ConvertBSTRToString(VBoxSDKVer);
	}
}

void VBox::resetError()
{
	error = 0;
	errorCode = NULL;
}

VBox::~VBox()
{
	if(virtualBox != NULL)
	{
		virtualBox->Release();
	}
	if(virtualBoxClient != NULL)
	{
		virtualBoxClient->Release();
	}
}
