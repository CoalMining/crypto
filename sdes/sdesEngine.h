#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdint.h>

class sdesEngine
{
private:
	char *inKey;
	uint8_t K1,K2;

public:
	sdesEngine()
	{
		inKey = new (std::nothrow) char[10];
	}
	~sdesEngine(){}

	//these are the functions that are needed for Key generation
	bool getKey();	//reads 10 1's and 0's to char* inKey
	bool P10();		//permutation P10
	bool performLS(int position);	//shifts two halves inKey by position step
	bool P8(bool key1);	//permutation P8
	bool keyExpansion();
	bool showkey();
};
