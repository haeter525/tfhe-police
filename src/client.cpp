#include <iostream>
#include <getopt.h>
#include "function.h"

int main(int argc , char* argv[])
{
	int c = 0;
	option opt[] = 
	{
		{"help" , 0 , NULL , 'h'} , 
		{"keygen" , 0 , NULL , 'k'} , 
		{"name" , 1 , NULL , 'n'} , 
		{"decrypt" , 1 , NULL , 'd'} , 
        {"encrypt" , 1 , NULL , 'e'}
	};
	while((c = getopt_long(argc , argv , "hn:d:ke:" , opt , NULL)) != -1)
	{
		switch(c)
		{
			case 'h':
				help();
				break;
			case 'k':
				keygen();
				break;
			case 'n':
				encryptName(optarg);
				break;
			case 'd':
				decrypt(optarg);
				break;
            case 'e':
				encrypt(optarg);
				break;
			case '?':
				std::cout << "unknown argument.\n";
				break;
			default:
				std::cout << "unknown error.\n";
		}
	}
	return 0;
}