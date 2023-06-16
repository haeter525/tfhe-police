#include "encode.h"
#include <stdio.h>

int decodeString(char name[8] , int* ret)
{
	for(int i = 0 ; i < 8 ; i++)
	{
		int temp = 1;
		for(int j = 0 ; j < 8 ; j++)
		{
			ret[i * 8 + 7 - j] = (name[i] & temp) / temp;
			temp <<= 1;
		}
	}
	return 0;
}

int encodeString(int* dec , char* name)
{
	for(int i = 0 ; i < 8 ; i++)
	{
		char temp = dec[i * 8];
		for(int j = 1 ; j < 8 ; j++)
		{
			temp <<= 1;
			temp += dec[i * 8 + j];
			// printf("%d\n" , temp);
		}
		name[i] = temp;
	}
	return 0;
}

int decodeInt8(int8_t n , int* ret)
{
	int8_t temp = 1;
	for(int i = 0 ; i < 8 ; i++)
	{
		ret[7 - i] = (n & temp) / temp;
		temp <<= 1;
	}
	return 0;
}

int8_t encodeInt8(int* dec)
{
	int8_t temp = dec[0];
	for(int i = 1 ; i < 8 ; i++)
	{
		temp <<= 1;
		temp += dec[i];
	}
	return temp;
}

int decodeInt32(int32_t n , int* ret)
{
	int32_t temp = 1;
	for(int i = 0 ; i < 32 ; i++)
	{
		ret[31 - i] = (n & temp) / temp;
		temp <<= 1;
	}
	return 0;
}

int32_t encodeInt32(int* dec)
{
	int32_t temp = dec[0];
	for(int i = 1 ; i < 32 ; i++)
	{
		temp <<= 1;
		temp += dec[i];
	}
	return temp;
}