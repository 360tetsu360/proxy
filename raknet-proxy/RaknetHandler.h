#pragma once
#include <string>
#include <sstream>

#include <RakPeerInterface.h>
#include <RakNetTypes.h>
#include <BitStream.h>

#include "Zlib.h"
class RakNetHandler
{
public:
	RakNetHandler();
	~RakNetHandler();
	void Initialize(int port,int maxplayers,std::string name);
private:
	void Handle(RakNet::RakPeerInterface* peer);
};