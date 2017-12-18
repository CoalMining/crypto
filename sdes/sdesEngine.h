#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdint.h>

class sdesEngine
{
private:
	char *inKey;
	uint8_t K1,K2;

	bool break8to4bits(uint8_t inData,uint8_t &firstHalf,uint8_t &secondHalf);
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

	bool encrypt8Bit(uint8_t inData,uint8_t &finalCrypto);
	uint8_t expand4to8(uint8_t input4Bits);
	uint8_t IP(uint8_t inData);
	uint8_t s0box(uint8_t inData);
	uint8_t s1box(uint8_t inData);
	bool P4(uint8_t ,uint8_t , uint8_t &retVal);
	bool fFunction(uint8_t secondHalfData,uint8_t num,uint8_t &P4Out);
	bool inverseIP(uint8_t inputVal,uint8_t &outputVal);
};
