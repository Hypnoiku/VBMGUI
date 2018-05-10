#pragma once

#include <sstream>
#include <string>
#include <comdef.h>

class err
{
public:
	err();
	~err();
	std::string err::buildErrMsg(int type, HRESULT err);
	std::string err::getErrMsg(int type);

private:
	std::string errMsgs[1024];
};
