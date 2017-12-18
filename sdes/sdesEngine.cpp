#include "sdesEngine.h"

bool sdesEngine::getKey()
{
	if(inKey==NULL)
	{
		std::cout<<"Error in creating array for inKey"<<std::endl;
		return -1;
	}
	std::cout<<"Enter the 10-bit key as a sequence of 1's and 0's."<<std::endl;
	for(int i=0;i<10;i++)
		std::cin>>inKey[i];
	return true;
}

bool sdesEngine::P10()
{
	char *outKey = new (std::nothrow)char[10];

	if(outKey==NULL)
	{
		std::cout<<"Error in creating temp array for inkey in P10 function"<<std::endl;
		return false;
	}
	outKey[0] = inKey[2];
	outKey[1] = inKey[4];
	outKey[2] = inKey[1];
	outKey[3] = inKey[6];
	outKey[4] = inKey[3];
	outKey[5] = inKey[9];
	outKey[6] = inKey[0];
	outKey[7] = inKey[8];
	outKey[8] = inKey[7];
	outKey[9] = inKey[5];

	std::copy(outKey,outKey+10,inKey);
	// std::cout<<"Changed Inkey is "<<inKey<<std::endl;
	delete[] outKey;
	return true;
}

bool sdesEngine::performLS(int position)
{
	char *tempChar2 = new (std::nothrow) char[5];
	char* tempChar1 = new (std::nothrow) char[5];

	if(tempChar1==NULL || tempChar2==NULL)
	{
		std::cout<<"Error in creating array halves of shifted key"<<std::endl;
		return false;
	}

	//circular ls first five position of inKey for tempChar1
	for(int i=0;i<5;i++)
	{
		tempChar1[i] = inKey[(i+position)%5];
	}
	//circular ls second five position of inKey for tempChar2
	for(int i=0;i<5;i++)
	{
		tempChar2[i] = inKey[5+(i+position)%5];
	}
	std::copy(tempChar1,tempChar1+5,inKey);
	std::copy(tempChar2,tempChar2+5,inKey+5);
	// std::cout<<"Shifted first half is "<<tempChar1<<",nexthalf is "<<tempChar2<<std::endl;
	// std::cout<<"Combined is "<<inKey<<std::endl;

	delete[] tempChar2;
	delete[] tempChar1;

	return true;
}

bool sdesEngine::P8(bool key1)
{
	char *p8Temp = new char[8];

	p8Temp[0] = inKey[5];
	p8Temp[1] = inKey[2];
	p8Temp[2] = inKey[6];
	p8Temp[3] = inKey[3];
	p8Temp[4] = inKey[7];
	p8Temp[5] = inKey[4];
	p8Temp[6] = inKey[9];
	p8Temp[7] = inKey[8];

	uint8_t KeyReturnVal = 0;
	for(int i=0;i<8;i++)
	{
		KeyReturnVal<<=1;
		if(p8Temp[i]=='1')
			KeyReturnVal+=1;
		else if(p8Temp[i]!='0')
		{
			std::cout<<"Error in key Provided. Please check"<<std::endl;
			return false;
		}
	}
	if(key1) K1 = KeyReturnVal;
	else K2 = KeyReturnVal;

	return true;
}

bool sdesEngine::keyExpansion()
{
	if(!getKey())
		return false;
	if(!P10())
		return false;
	if(!performLS(1))
		return false;
	if(!P8(true))
		return false;
	if(!performLS(2))
		return false;
	if(!P8(false))
		return false;
	showkey();
	return true;
}

bool sdesEngine::showkey()
{
	std::cout<<"K1 = "<<(int)K1<<std::endl;
	std::cout<<"K2 = "<<(int)K2<<std::endl;
	return true;
}