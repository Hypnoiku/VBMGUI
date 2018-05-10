#include "err.h"

err::err()
{
	errMsgs[0] = "Error creating VirtualBox instance! 0x";
	errMsgs[1] = "Error getting VirtualBox machines! 0x";
	errMsgs[2] = "Error compacting HDD! 0x";
	errMsgs[3] = "VirtualBox COM interface is missing! Exiting!";
	errMsgs[4] = "Error getting VirtualBox metadata! 0x";
	errMsgs[5] = "Error starting VM! 0x";
}

std::string err::buildErrMsg(int type, HRESULT err)
{
	//Each line is seperated as is to prevent the control character '\x1' from
	//appearing and preventing any useful output
	std::stringstream errHex;
	errHex << std::hex << err;
	std::string errStr = errMsgs[type];
	errStr += errHex.str();
	errStr += " (";
	errStr += (int)err;
	errStr += ")";

	return errStr;
}

std::string err::getErrMsg(int type)
{
	return errMsgs[type];
}

err::~err()
{
}
