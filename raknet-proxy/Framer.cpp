#include "Framer.h"


Framer::Framer()
{
}

Framer::~Framer()
{
}

Framer* instance;

Framer* Framer::get() {
    if (!instance) {
        instance = new Framer();
    }
    return instance;
}

std::vector<std::vector<uint8_t>> Framer::GetPackets(std::vector<uint8_t> buffer) {
    int offset = 0;
    std::vector<std::vector<byte>> packets;
    while (offset < buffer.size()) {
        uint32_t length = 0;
        int packetlength = getVarint(buffer.data() + offset, length);
        offset += length;
        std::vector<byte> packet(buffer.data() + offset, buffer.data() + offset + packetlength);
        offset += packetlength;
        packets.push_back(packet);
    }
    return packets;
}

uint64_t Framer::getVarint(const uint8_t* const data, uint32_t& decoded_bytes) {
    int i = 0;
    uint64_t decoded_value = 0;
    int shift_amount = 0;
    do
    {
        decoded_value |= (uint64_t)(data[i] & 0x7F) << shift_amount;
        shift_amount += 7;
    } while ((data[i++] & 0x80) != 0);
    decoded_bytes = i;
    return decoded_value;
}


std::string Framer::readString(const uint8_t* const data,int length) {
    return std::string(data, data + length);
}
