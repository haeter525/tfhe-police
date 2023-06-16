#include <cstdint>

#ifndef _ENCODE_H_
#define _ENCODE_H_

int decodeString(char name[8] , int* ret);

int encodeString(int* dec , char* name);

int decodeInt8(int8_t n , int* ret);

int8_t encodeInt8(int* dec);

int decodeInt32(int32_t n , int* ret);

int32_t encodeInt32(int* dec);

#endif