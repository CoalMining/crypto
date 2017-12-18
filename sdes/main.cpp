#include <cstdio>
#include "sdesEngine.h"

int main()
{
	sdesEngine sdes;

	uint8_t inVal,outVal;	
	if(!sdes.keyExpansion())
	{
		return -1;
	}
	fflush(stdin);
	std::cout<<"Enter the 8-bit data to encrypt value"<<std::endl;
	std::cin>>inVal;

	if(!sdes.encrypt8Bit(inVal,outVal))
	{
		std::cout<<"Error returned from encrypt8Bit function"<<std::endl;
		return -1;
	}

	std::cout<<"The encrypted value is "<<(int)outVal<<std::endl;

	return 0;
}