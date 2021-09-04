#pragma once
#include <BitStream.h>

class Utils
{
	Utils();
	~Utils();
public:
	static Utils* get();
	int VarUint32(RakNet::BitStream bstream ,int offset);
private:

};