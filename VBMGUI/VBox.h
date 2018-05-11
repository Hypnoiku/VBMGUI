#pragma once

#include "VirtualBox.h"
#include <string>
#include <comutil.h>
#include "ByteMath.h"

class VBox
{
public:
	std::string* machineNames;
	std::string* mediumNames;
	FLOAT* mediumSizes;
	FLOAT* mediumMaxSizes;
	int machineAmount;
	int mediumAmount;
	HRESULT errorCode;
	int error;
	
	VBox();
	void VBox::getMachines();
	void VBox::getMediums();
	IProgress* VBox::startMachine(int position);
	IProgress* VBox::compactMedium(int position);
	void VBox::getVBoxVers(std::string &VBoxVerStr, std::string &VBoxSDKVerStr);
	~VBox();

private:
	IVirtualBox * virtualBox;
	ISession *session;
	IVirtualBoxClient *virtualBoxClient;
	HRESULT rc;
	IMachine * *machines;
	IMedium **mediums;

	void VBox::resetError();
};

