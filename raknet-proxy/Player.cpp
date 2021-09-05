#include "Player.h"
#include "PlayerData.h"
#include <iostream>
using namespace nlohmann;

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
                Reader r = Reader(RawPacket.data(), RawPacket.size());
                r.ReadByte();
                std::cout << "version:" << r.ReadBigEndian() << std::endl;
                uint32_t unknown = 0;
                r.ReadVarInt(unknown);
                std::cout << unknown << std::endl;
                int JWTlength = r.ReadUnInt();
                std::string JWTs = r.ReadString(JWTlength);
                HandleChain(JWTs);
                uint32_t test = r.ReadUnInt();
                std::string skin = r.ReadString(test);
                PlayerData pdata = PlayerData(skin);
                std::cout << pdata.PersonaPieces << std::endl;
            }
        }


        std::vector<uint8_t>().swap(buffer);
        for (auto item : packets)
            std::vector<byte>().swap(item);
        std::vector<std::vector<byte>>().swap(packets);
    }
}


void Player::HandleJWT(std::string JWTformat) {
    /*auto data = jwt::decode(JWTformat);
    for (auto& e : data.get_payload_claims()) {
        if (e.first == "extraData") {
            std::cout << e.second.to_json().get("XUID") << std::endl;
        }
        std::cout << e.first << " = " << e.second << std::endl;
    }*/
}

void Player::HandleChain(std::string ChainJson) {
    json chaindata = json::parse(ChainJson);
    for (auto jwts : chaindata["chain"])
    {
        HandleJWT(jwts);
    }
}
