#pragma once

#include <comutil.h>

class ByteMath
{
public:
	ByteMath();
	FLOAT ByteMath::dynConvert(LONG64 in);
	FLOAT ByteMath::bToKB(LONG64 in);
	FLOAT ByteMath::bToMB(LONG64 in);
	FLOAT ByteMath::bToGB(LONG64 in);
	FLOAT ByteMath::bToTB(LONG64 in);
	~ByteMath();
};

