#include "Player.h"
#include <iostream>

Player::Player()
{
}

Player::~Player()
{
}

Player* instance;

Player* Player::get() {
    if (!instance) {
        instance = new Player();
    }
    return instance;
}
bool first = true;
void Player::Handle(RakNet::Packet* packet) {
    if (first == true) {
        this->ClientGuid = packet->guid;
        this->ClientAddress = packet->systemAddress;
    }
    if (this->ClientAddress == packet->systemAddress && this->ClientGuid == packet->guid) {
        if (this->Encryption) {
        }

        std::vector<uint8_t> dst(600000);
        int length = Zlib::getZlib()->Inflate(dst.data(), 0, dst.size(), packet->data, 1, packet->length); // decompress packet
        std::vector<uint8_t> buffer(dst.data(), dst.data() + length);
        std::vector<uint8_t>().swap(dst);
        std::vector<std::vector<byte>> packets = Framer::get()->GetPackets(buffer); 
        //do something with packets;

        for (auto RawPacket : packets)
        {
            switch ((int)RawPacket[0])
            {
            case 1: // login packet | id-1byte | protocol version - 4byte | Chain data JWT | Skin data JWT | 
                uint32_t size = 0;//
                int unkLength = Framer::get()->getVarint(RawPacket.data() + 5, size);
                int chainDataLength = Framer::get()->getVarint(RawPacket.data() + 5 + size, size);
                std::string ChainData = Framer::get()->readString(RawPacket.data() + 5 + size, chainDataLength - size);
                std::cout << ChainData << std::endl;
            }
        }


        std::vector<uint8_t>().swap(buffer);
        for (auto item : packets)
            std::vector<byte>().swap(item);
        std::vector<std::vector<byte>>().swap(packets);
    }
}
