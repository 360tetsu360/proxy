#include "RaknetHandler.h"
#include <iostream>
#include <fstream>
RakNetHandler::RakNetHandler()
{
}

RakNetHandler::~RakNetHandler()
{
}
void RakNetHandler::Initialize(int port, int maxplayers, std::string name) {
	RakNet::RakPeerInterface* peer = RakNet::RakPeerInterface::GetInstance();
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

void getpackets(std::vector<byte> buffer) {
    for (auto i : buffer) {
        std::cout << "0x" << std::hex << (int)i << ", ";
    }
}
uint64_t decode_unsigned_varint(const uint8_t* const data,uint32_t& decoded_bytes,int& size)
{
    int i = 0;
    uint64_t decoded_value = 0;
    int shift_amount = 0;
    int sizev = 0;
    do
    {
        sizev++;
        decoded_value |= (uint64_t)(data[i] & 0x7F) << shift_amount;
        shift_amount += 7;
    } while ((data[i++] & 0x80) != 0);
    size = sizev;
    decoded_bytes = i;
    return decoded_value;
}
std::vector<std::vector<byte>> getPackets(std::vector<uint8_t> buffer) {
    int offset = 0;
    std::vector<std::vector<byte>> packets;
    while (offset < buffer.size()) {
        uint32_t length = 0;
        int size = 0;
        int packetlength = decode_unsigned_varint(buffer.data() + offset, length,size);
        offset += length;
        std::vector<byte> packet(buffer.data() + offset,buffer.data() + offset + packetlength);
        offset += packetlength;
        packets.push_back(packet);
    }
    return packets;
}
int getBigEndian(uint8_t* buffer) {
    return (int)buffer[0] | (int)buffer[1] << 8 | (int)buffer[2] << 16 | (int)buffer[3] << 24;
}
bool a = false;
void RakNetHandler::Handle(RakNet::RakPeerInterface* peer) {
    RakNet::Packet* packet;
    for (packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive()) {
        switch ((int)packet->data[0])
        {
        case 0xFE: //MCPE packet
            //
            std::vector<uint8_t> dst(600000);
            int length = Zlib::getZlib()->Inflate(dst.data(), 0, dst.size(), packet->data, 1, packet->length);
            std::vector<uint8_t> buffer(dst.data(), dst.data() + length);
            std::vector<std::vector<byte>> packets = getPackets(buffer);
            std::vector<uint8_t>().swap(dst);
        }
    }
}