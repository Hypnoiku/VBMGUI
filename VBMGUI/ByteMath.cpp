#include "ByteMath.h"

ByteMath::ByteMath()
{

}

FLOAT ByteMath::dynConvert(LONG64 in, std::string& byteType)
{
	int loops = 0;
	FLOAT conv = (float)in;

	while (conv > (float)1024 && loops < 4)
	{
		conv = conv / (float)1024;
		loops++;
	}

	switch(loops)
	{
		case 0: byteType = "bytes"; break;
		case 1: byteType = "KB"; break;
		case 2: byteType = "MB"; break;
		case 3: byteType = "GB"; break;
		case 4: byteType = "TB"; break;
	}

	return conv;
}

FLOAT ByteMath::bToKB(LONG64 in)
{
	return (float)in / (float)1024;
}

FLOAT ByteMath::bToMB(LONG64 in)
{
	return ((float)in / (float)1024) / (float)1024;
}

FLOAT ByteMath::bToGB(LONG64 in)
{
	return (((float)in / (float)1024) / (float)1024) / (float)1024;
}

FLOAT ByteMath::bToTB(LONG64 in)
{
	return ((((float)in / (float)1024) / (float)1024) / (float)1024) / (float)1024;
}

ByteMath::~ByteMath()
{

}
