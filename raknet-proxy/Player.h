#pragma once
#include <vector>
#include <RakPeerInterface.h>
#include <string>
#include "Zlib.h"
#include "Framer.h"

class Player
{
	Player();
	~Player();
public:
	static Player* get();
	void Handle(RakNet::Packet* packet);

private:
	RakNet::SystemAddress ClientAddress;
	RakNet::RakNetGUID ClientGuid;
	bool Encryption = false;
	std::string skin_Base64;
};
