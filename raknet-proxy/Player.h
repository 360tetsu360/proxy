#pragma once
#include "nlohmann/json.hpp"
#include "jwt-cpp/jwt.h"
#undef max
#undef min
#include <vector>
#include <RakPeerInterface.h>
#include <string>
#include "Zlib.h"
#include "Framer.h"
#include "Utils.h"
#include "Reader.h"


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

	void HandleChain(std::string ChainJson);
	void HandleJWT(std::string JWTformat);
};
