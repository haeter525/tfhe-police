#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include "binfhecontext-ser.h"

struct nameCipher {
	lbcrypto::LWECiphertext nc[8][5];
};

int fetchName(nameCipher* myCipher);
int encryptName (char *name);
int query();
int keygen();
int encrypt(const char* dirName);
int decrypt(const char* dirName);
int add();

#endif