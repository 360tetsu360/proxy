#pragma once
#include <string>
#include <sstream>

#include <RakPeerInterface.h>
#include <RakNetTypes.h>
#include <BitStream.h>

#include "Zlib.h"
#include "Framer.h"
#include "Player.h"

class RakNetHandler
{
public:
	RakNetHandler();
	~RakNetHandler();
	void Initialize(int port,int maxplayers,std::string name);
	void Handle(RakNet::RakPeerInterface* peer);
	
private:
};