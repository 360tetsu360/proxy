#include "RaknetHandler.h"
#include <iostream>
#include <fstream>
RakNetHandler::RakNetHandler()
{
}

RakNetHandler::~RakNetHandler()
{
}
RakNet::RakPeerInterface* peer;
void RakNetHandler::Initialize(int port, int maxplayers, std::string name) {
    peer = RakNet::RakPeerInterface::GetInstance();
	RakNet::SocketDescriptor socket_desc(port, "127.0.0.1"); //defalt ip

    if (peer->Startup(maxplayers, &socket_desc, 1) == RakNet::RAKNET_STARTED) {
        peer->SetMaximumIncomingConnections(maxplayers);

        std::ostringstream motd;
        motd << "MCPE;" << name << ";" << 448 << ";" << "1.17.11" << ";0;" << maxplayers;
        std::string message = motd.str();

        message.insert(message.begin(), message.size());
        message.insert(message.begin(), 0x00);

        peer->SetOfflinePingResponse(message.c_str(), message.size());

        while (1) {
            RakNetHandler::Handle(peer);
        }
    }
}
void RakNetHandler::Handle(RakNet::RakPeerInterface* peer) {
    RakNet::Packet* packet;
    for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive()) {
        switch ((int)packet->data[0])
        {
        case 0xFE: //MCPE packet
            Player::get()->Handle(packet);
        }
    }
}