#include "ByteMath.h"

ByteMath::ByteMath()
{

}

FLOAT ByteMath::dynConvert(LONG64 in)
{
	return (float)in;
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
