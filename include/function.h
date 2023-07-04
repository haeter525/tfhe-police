#ifndef _FUNCTION_H_
#define _FUNCTION_H_

struct nameCipher {
	lbcrypto::LWECiphertext nc[8][5];
};

int fetchName(nameCipher* myCipher);
int encryptName (char *name);
int query();
void help();
int keygen();
int encrypt(const char* dirName);
int decrypt(const char* dirName);
int add();

#endif