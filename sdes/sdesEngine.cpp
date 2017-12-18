#include "sdesEngine.h"

bool sdesEngine::getKey()
{
	if(inKey==NULL)
	{
		std::cout<<"Error in creating array for inKey"<<std::endl;
		std::cout<<"Error in "<<__FILE__<<" at "<<__LINE__<<std::endl;	
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
		std::cout<<"Error in "<<__FILE__<<" at "<<__LINE__<<std::endl;	
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
		std::cout<<"Error in "<<__FILE__<<" at "<<__LINE__<<std::endl;	
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
		std::cout<<p8Temp[i]<<" ";
		if(p8Temp[i]=='1')
			KeyReturnVal+=1;
		else if(p8Temp[i]!='0')
		{
			std::cout<<"Error in "<<__FILE__<<" at "<<__LINE__<<std::endl;	
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
bool sdesEngine::break8to4bits(uint8_t inData,uint8_t &firstHalf,uint8_t &secondHalf)
{
	uint8_t tempInData = inData;
	uint8_t checker = 128;

	if(inData>255)
	{
		std::cout<<"Error in "<<__FILE__<<" at "<<__LINE__<<std::endl;
		return false;
	}
	firstHalf = 0;
	for(int i=0;i<4;i++)
	{
		firstHalf<<=1;
		if(checker&tempInData)
			firstHalf+=1;
		checker>>=1;
	}
	secondHalf = 0;
	for(int i=0;i<4;i++)
	{
		secondHalf<<=1;
		if(checker&tempInData)
			secondHalf+=1;
		checker>>=1;
	}
	return true;
}
uint8_t sdesEngine::expand4to8(uint8_t input4Bits)
{
	//for the input4Bits only the lower 4-bits are of concern
	uint8_t returnVal = 0;

	uint8_t *posBits = new uint8_t[4];
	uint8_t checker = 8;
	for(int i=0;i<4;i++)
	{
		if(input4Bits&checker) posBits[i] = 1;
		else posBits[i] = 0;
		checker>>=1;
	}

	returnVal+=posBits[3];
	returnVal<<=1;
	returnVal+=posBits[0];
	returnVal<<=1;
	returnVal+=posBits[1];
	returnVal<<=1;
	returnVal+=posBits[2];
	returnVal<<=1;
	returnVal+=posBits[1];
	returnVal<<=1;
	returnVal+=posBits[2];
	returnVal<<=1;
	returnVal+=posBits[3];
	returnVal<<=1;
	returnVal+=posBits[0];

	delete[] posBits;
	return returnVal;
}

uint8_t sdesEngine::IP(uint8_t inData)
{
	uint8_t *posBits = new uint8_t[10];
	uint8_t returnVal = 0;

	uint8_t checker = 128;
	for(int i=0;i<8;i++)
	{
		if(inData&checker) posBits[i] = 1;
		else posBits[i] = 0;
		checker>>=1;
	}

	returnVal+=posBits[1];
	returnVal<<=1;
	returnVal+=posBits[5];
	returnVal<<=1;
	returnVal+=posBits[2];
	returnVal<<=1;
	returnVal+=posBits[0];
	returnVal<<=1;
	returnVal+=posBits[3];
	returnVal<<=1;
	returnVal+=posBits[7];
	returnVal<<=1;
	returnVal+=posBits[4];
	returnVal<<=1;
	returnVal+=posBits[6];

	delete[] posBits;
	return returnVal;
}

uint8_t sdesEngine::s0box(uint8_t inData)
{
	switch (inData)
	{
		case 0:
			return 1;
		case 1:
			return 3;
		case 2:
			return 2;
		case 3:
			return 2;
		case 4:
			return 3;
		case 5:
			return 1;
		case 6:
			return 2;
		case 7:
			return 0;
		case 8:
			return 0;
		case 9:
			return 3;
		case 10:
			return 2;
		case 11:
			return 1;
		case 12:
			return 1;
		case 13:
			return 3;
		case 14:
			return 3;
		case 15:
			return 2;
		default:
			std::cout<<"Error in "<<__FILE__<<" at "<<__LINE__<<std::endl;	
			return -1;
	}
}

uint8_t sdesEngine::s1box(uint8_t inData)
{
	switch (inData)
	{
		case 0:
			return 0;
		case 1:
			return 2;
		case 2:
			return 1;
		case 3:
			return 0;
		case 4:
			return 2;
		case 5:
			return 1;
		case 6:
			return 3;
		case 7:
			return 3;
		case 8:
			return 3;
		case 9:
			return 2;
		case 10:
			return 0;
		case 11:
			return 1;
		case 12:
			return 1;
		case 13:
			return 0;
		case 14:
			return 0;
		case 15:
			return 3;
		default:
			std::cout<<"Error in "<<__FILE__<<" at "<<__LINE__<<std::endl;	
			return -1;
	}
}
bool sdesEngine::P4(uint8_t firstNo,uint8_t secondNo,uint8_t &returnVal)
{
	if(firstNo<0 || secondNo<0 || firstNo>3 || secondNo>3)
	{
		std::cout<<"Error in "<<__FILE__<<" at "<<__LINE__<<std::endl;	
		return false;
	}
	uint8_t* posBits  = new uint8_t[4];
	uint8_t checker = 2;

	//...
	for(int i=0;i<2;i++)
	{
		if(checker&firstNo)
			posBits[i] = 1;
		else
			posBits[i] = 0;
		checker>>=1;
	}
	checker = 2;

	//...
	for(int i=2;i<4;i++)
	{
		if(checker&secondNo)
			posBits[i] = 1;
		else
			posBits[i] = 0;
		checker>>=1;
	}

	returnVal = 0;
	returnVal+=posBits[1];
	returnVal<<=1;
	returnVal+=posBits[3];
	returnVal<<=1;
	returnVal+=posBits[2];
	returnVal<<=1;
	returnVal+=posBits[0];

	return true;
}
bool sdesEngine::encrypt8Bit(uint8_t inData,uint8_t &finalCrypto)
{
	uint8_t retVal;
	uint8_t myFirst4Bits,mySecond4Bits;		//first = upperNibble
	uint8_t dataConv = IP(inData);

	if(!break8to4bits(dataConv,myFirst4Bits,mySecond4Bits))
	{
		std::cout<<"Error in "<<__FILE__<<" at "<<__LINE__<<std::endl;		
		return false;
	}
	//std::cout<<" "<<(int)myFirst4Bits<<" "<<(int)mySecond4Bits<<std::endl;

	uint8_t P4Out;
	if(!fFunction(mySecond4Bits,1,P4Out))
	{
		std::cout<<"Error in "<<__FILE__<<" at "<<__LINE__<<std::endl;
		return false;
	}

	uint8_t xorred4Bit = P4Out^myFirst4Bits;

	//these two steps seems unnecessary if we manage with arguments in following operations
	// uint8_t swapped = (mySecond4Bits<<4)+xorred4Bit;
	// break8to4bits(swapped,myFirst4Bits,mySecond4Bits);	

	if(!fFunction(xorred4Bit,2,P4Out))
	{
		std::cout<<"Error in "<<__FILE__<<" at "<<__LINE__<<std::endl;
		return false;
	}
	uint8_t xorred4Bit2 = P4Out^mySecond4Bits;
	uint8_t inputToInvIp = (xorred4Bit2<<4)+xorred4Bit;

	inverseIP(inputToInvIp,retVal);

	finalCrypto = retVal;

	return true;
}

bool sdesEngine::inverseIP(uint8_t inputVal,uint8_t &outputVal)
{
	uint8_t *posBits = new uint8_t[8];
	uint8_t checker = 128;

	for(int i=0;i<8;i++)
	{
		if(checker&inputVal)
			posBits[i]=1;
		else
			posBits[i] = 0;
		checker>>=1;
	}

	outputVal = 0;
	outputVal+=posBits[3];
	outputVal<<=1;
	outputVal+=posBits[0];
	outputVal<<=1;
	outputVal+=posBits[2];
	outputVal<<=1;
	outputVal+=posBits[4];
	outputVal<<=1;
	outputVal+=posBits[6];
	outputVal<<=1;
	outputVal+=posBits[1];
	outputVal<<=1;
	outputVal+=posBits[7];
	outputVal<<=1;
	outputVal+=posBits[5];

	return true;
}


bool sdesEngine::fFunction(uint8_t secondHalfData,uint8_t num,uint8_t &P4Out)
{
	//num defines if K1 or K2 is to be used
	uint8_t expanded = expand4to8(secondHalfData);
	uint8_t xorred = (num==1)?(K1^expanded):(K2^expanded);

	uint8_t s0Input,s1Input;
	break8to4bits(xorred,s0Input,s1Input);

	uint8_t _2Bit1 = s0box(s0Input);
	uint8_t _2Bit2 = s1box(s1Input);
	if(_2Bit2<0 || _2Bit1<0 )
	{
		std::cout<<"Input to SBOX was illegal number "<<std::endl;
		return false;
	}

	if(!P4(_2Bit1,_2Bit2,P4Out))
	{
		std::cout<<"Error in performing P4"<<std::endl;
		return false;
	}
	return true;
}