#pragma once
#include "Zlib.h"
#include <Windows.h>
#include <vector>


class Framer
{
	Framer();
	~Framer();
public:
	static Framer* get();
	uint64_t getVarint(const uint8_t* const data, uint32_t& decoded_bytes);
	std::vector<std::vector<uint8_t>> GetPackets(std::vector<uint8_t> buffer);
private:

};