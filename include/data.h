#ifndef _DATA_H_
#define _DATA_H_

#include "binfhecontext-ser.h"
#include <vector>

struct data_
{
	char name[9];
	int caseNum;
	int location;
	int time;
};

struct dataCipher_
{
	lbcrypto::LWECiphertext nameCipher[8][5];
	lbcrypto::LWECiphertext caseCipher[3];
	lbcrypto::LWECiphertext locationCipher[8];
	lbcrypto::LWECiphertext timeCipher[13];
};

lbcrypto::LWECiphertext count[10];

pthread_t tid[8];
pthread_mutex_t lock;
int numThreads = 8;
int dataIdx[8] = {0,1,2,3,4,5,6,7}; /* assigned to counter threads */
int blockSize;
int num;/*data size */

std::vector <dataCipher_> tempdata;
lbcrypto::LWEPrivateKey secretKey;
lbcrypto::BinFHEContext cryptoContext;
lbcrypto::LWEPrivateKey sk;
lbcrypto::BinFHEContext cc;
lbcrypto::LWECiphertext qNameCipher[8][5];



class DataBase
{
	private:
		std::vector <dataCipher_> __dataCipher;
		std::string __dirName;
	public:
		DataBase(const char* dirName);
		int fetch();
		std::vector <dataCipher_> get();
		//int encrypt(lbcrypto::LWEPrivateKey sk , lbcrypto::BinFHEContext cc , const char* fileName);
		//int query(lbcrypto::LWEPrivateKey sk , lbcrypto::BinFHEContext cc , const char* dirName);
};

#endif