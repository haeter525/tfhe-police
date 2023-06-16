#ifndef _DATA_H_
#define _DATA_H_

#include "binfhecontext-ser.h"
#include <cstdint>
#include <vector>

struct data_
{
	char name[8];
	int8_t caseNum;
	int32_t time;
};

struct dataCipher_
{
	lbcrypto::LWECiphertext nameCipher[8][8];
	lbcrypto::LWECiphertext caseCipher[8];
	lbcrypto::LWECiphertext timeCipher[32];
};


class DataBase
{
	private:
		std::vector <dataCipher_> __dataCipher;
		std::string __dirName;
		int __threads;
	public:
		DataBase(const char* dirName , int threads = 8);
		int fetch(lbcrypto::LWEPrivateKey sk , lbcrypto::BinFHEContext cc);
		int encrypt(lbcrypto::LWEPrivateKey sk , lbcrypto::BinFHEContext cc , const char* fileName);
		int query(lbcrypto::LWEPrivateKey sk , lbcrypto::BinFHEContext cc , const char* dirName);
		int decrypt();
		int counter();
		int insert();
};

#endif