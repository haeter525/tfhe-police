#include "data.h"
#include "encode.h"
#include <cstring>
#include <future>
#include "str_cmp.h"

#define DEBUG 0

DataBase::DataBase(const char* dirName , int threads)
{
	__dirName = std::string(dirName);
	__threads = threads;
}

int DataBase::fetch(lbcrypto::LWEPrivateKey sk, lbcrypto::BinFHEContext cc)
{
	char* fileName = NULL;
	asprintf(&fileName , "%s/length" , __dirName.c_str());
	FILE* fptr = fopen(fileName , "r");
	int length = 0;
	fscanf(fptr , "%d" , &length);
	for(int i = 0 ; i < length ; i++)
	{
		dataCipher_ temp;
		for(int j = 0 ; j < 64 ; j++)
		{
			asprintf(&fileName , "encData/%dN%02d" , i , j);
			lbcrypto::Serial::DeserializeFromFile(fileName , temp.nameCipher[j / 8][j % 8] , lbcrypto::SerType::BINARY);
		}
		for(int j = 0 ; j < 8 ; j++)
		{
			asprintf(&fileName , "encData/%dC%02d" , i , j);
			lbcrypto::Serial::DeserializeFromFile(fileName , temp.caseCipher[j] , lbcrypto::SerType::BINARY);
		}	
		for(int j = 0 ; j < 32 ; j++)
		{
			asprintf(&fileName , "encData/%dT%02d" , i , j);
			lbcrypto::Serial::DeserializeFromFile(fileName , temp.timeCipher[j] , lbcrypto::SerType::BINARY);
		}
		__dataCipher.push_back(temp);
	}
    return 0;
}

int DataBase::encrypt(lbcrypto::LWEPrivateKey sk , lbcrypto::BinFHEContext cc , const char* fileName)
{
	std::vector <data_> data;
	FILE* fptr = fopen(fileName , "r");
	if(fptr == nullptr)
	{
		std::cout << "Error when open file " << fileName << "\n";
		return 0;
	}
	for(int i = 0 , c = 0 ; (c = fgetc(fptr)) != EOF ; i++)
	{
		data_ temp;
		for(int j = 0 ; c != ',' ; j++)
		{
			temp.name[j] = c;
			c = fgetc(fptr);
		}
		fscanf(fptr , "%hhd,%d\n" , &(temp.caseNum) , &(temp.time));
		data.push_back(temp);
	}

	fclose(fptr);

	#if DEBUG

	for(auto i = data.begin() ; i != data.end() ; i++)
	{
		char temp[9] = {0};
		strncpy(temp , i -> name , 8);
		std::cout << temp << "\t" << int(i -> caseNum) << "\t" << i -> time << "\n";
	}

	#endif

	cc.BTKeyGen(sk);

	system("mkdir encData");

	fptr = fopen("lengh" , "wb");

	fprintf(fptr , "%zu" , data.size());

	fclose(fptr);

	std::vector <std::future <bool>> threads;
	// std::cout << data.size() << "\n";

	int blockSize = (data.size() - 1) / __threads;

	std::cout << "Data size : " << data.size() << "\n";
	std::cout << "Block size : " << blockSize << "\n";

	for(int i = 0 ; i < __threads ; i++)
	{
		threads.push_back(std::async([&](int i)
		{
			lbcrypto::LWECiphertext tempCipher;
			char* filename = NULL;
			int decTime[32] = {0};
			int decCase[8] = {0};
			int decName[64] = {0};
			decodeString(data[i].name , decName);
			for(int b = 0 ; b < blockSize ; b++)
			{
				if(b + i * blockSize >= data.size())
				{
					break;
				}
				for(int j = 0 ; j < 64 ; j++)
				{
					asprintf(&filename , "%s/%dN%02d" , __dirName.c_str() , b + i * blockSize , j);
					tempCipher = cc.Encrypt(sk , decName[j]);
					lbcrypto::Serial::SerializeToFile(filename , tempCipher , lbcrypto::SerType::BINARY);
				}
				decodeInt8(data[i].caseNum , decCase);
				for(int j = 0 ; j < 8 ; j++)
				{
					asprintf(&filename , "%s/%dC%02d" , __dirName.c_str() , b + i * blockSize , j);
					tempCipher = cc.Encrypt(sk , decCase[j]);
					lbcrypto::Serial::SerializeToFile(filename , tempCipher , lbcrypto::SerType::BINARY);
				}
				decodeInt32(data[i].time , decTime);
				for(int j = 0 ; j < 32 ; j++)
				{
					asprintf(&filename , "%s/%dT%02d" , __dirName.c_str() , b + i * blockSize , j);
					tempCipher = cc.Encrypt(sk , decTime[j]);
					lbcrypto::Serial::SerializeToFile(filename , tempCipher , lbcrypto::SerType::BINARY);
				}
			}
			return true;
		} , i));		
	}

	for(int i = 0 ; i < 8 ; i++)
	{
		threads[i].get();
	}

	return 0;
}

int DataBase::query(lbcrypto::LWEPrivateKey sk , lbcrypto::BinFHEContext cc , const char* dirName)
{
	char* fileName = NULL;
	bool check = false;
	lbcrypto::LWECiphertext tempCipher;
	for(int i = 0 ; i < __dataCipher.size() ; i++)
	{
		for(int j = 0 ; j < 8 ; j++)
		{
			for(int k = 0 ; k < 8 ; k++)
			{
				asprintf(&fileName , "%s/%dN%02d" , __dirName.c_str() , i , j * 8 + k);
				check = lbcrypto::Serial::DeserializeFromFile(fileName , __dataCipher[i].nameCipher[j][k] , lbcrypto::SerType::BINARY);
				if(check == false)
				{
					std::cout << "Error when deserial file, name :" << fileName;
				}
			}
		}
		for(int j = 0 ; j < 8 ; j++)
		{
			asprintf(&fileName , "%s/%dC%02d" , __dirName.c_str() , i , j);
			check = lbcrypto::Serial::DeserializeFromFile(fileName , __dataCipher[i].caseCipher[j] , lbcrypto::SerType::BINARY);
			if(check == false)
			{
				std::cout << "Error when deserial file, name :" << fileName;
			}
		}
		for(int j = 0 ; j < 32 ; j++)
		{
			asprintf(&fileName , "%s/%dT%02d" , __dirName.c_str() , i , j);
			check = lbcrypto::Serial::DeserializeFromFile(fileName , __dataCipher[i].timeCipher[j] , lbcrypto::SerType::BINARY);
			if(check == false)
			{
				std::cout << "Error when deserial file, name :" << fileName;
			}
		}
	}
	char* command = NULL;
	asprintf(&command , "unzip %s.zip" , dirName);
	system(command);

	lbcrypto::LWECiphertext qNameCipher[8][8];

	for(int i = 0 ; i < 8 ; i++)
	{
		for(int j = 0 ; j < 8 ; j++)
		{
			asprintf(&fileName , "%s/temp%d" , dirName , i * 8 + j);
			check = lbcrypto::Serial::DeserializeFromFile(fileName , qNameCipher[i][j] , lbcrypto::SerType::BINARY);
			if(check == false)
			{
				std::cout << "Error when deserial file, name :" << fileName << "\n";
			}
		}
	}
	asprintf(&command , "rm -f -R %s" , dirName);
	system(command);

	cc.BTKeyGen(sk);

	std::vector <std::future <bool>> threads;

	int blockSize = (__dataCipher.size() - 1) / __threads;

	system("mkdir result");
	
	for(int i = 0 ; i < __threads ; i++)
	{
		threads.push_back(std::async([&](int i)
		{
			lbcrypto::LWECiphertext checkCipher;
			lbcrypto::LWECiphertext tempCipher;
			for(int b = 0 ; b < blockSize ; b++)
			{
				if(b + i * blockSize >= __dataCipher.size())
				{
					break;
				}
				checkCipher = str_comp(__dataCipher[b + i * blockSize].nameCipher , qNameCipher , sk , cc);
				for(int j = 0 ; j < 64 ; j++)
				{
					tempCipher = cc.EvalBinGate(AND , checkCipher , __dataCipher[b + i * blockSize].nameCipher[j / 8][j % 8]);
					asprintf(&fileName , "result/%dN%02d" , b + i * blockSize , j);
					lbcrypto::Serial::SerializeToFile(fileName , tempCipher , lbcrypto::SerType::BINARY);
				}
				for(int j = 0 ; j < 8 ; j++)
				{
					tempCipher = cc.EvalBinGate(AND , checkCipher , __dataCipher[b + i * blockSize].caseCipher[j]);
					asprintf(&fileName , "result/%dC%02d" , b + i * blockSize , j);
					lbcrypto::Serial::SerializeToFile(fileName , tempCipher , lbcrypto::SerType::BINARY);
				}
				for(int j = 0 ; j < 32 ; j++)
				{
					tempCipher = cc.EvalBinGate(AND , checkCipher , __dataCipher[b + i * blockSize].caseCipher[j]);
					asprintf(&fileName , "result/%dT%02d" , b + i * blockSize , j);
					lbcrypto::Serial::SerializeToFile(fileName , tempCipher , lbcrypto::SerType::BINARY);
				}
			}
			return true;
		} , i));		
	}

	for(int i = 0 ; i < 8 ; i++)
	{
		threads[i].get();
	}

	return 0;
}
