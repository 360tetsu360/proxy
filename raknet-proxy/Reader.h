#pragma once
#include <string>
#include "Utils.h"
#include "Framer.h"

class Reader
{
public:
	Reader();
	Reader(uint8_t* data, size_t length);
	Reader(size_t length);
	~Reader();
	
	uint8_t* Read(size_t length);
	uint8_t* absoluteRead(size_t length);
	uint8_t* absoluteRead(size_t pos,size_t length);

	int64_t ReadVarInt(uint32_t& length);
	int ReadInt();
	uint32_t ReadUnInt();
	int ReadBigEndian();
	int16_t ReadShort();
	uint16_t ReadUnShort();
	uint8_t ReadByte();
	std::string ReadString(size_t length);

	template <typename T>
	inline auto* ReadCustom();

	void SetPosition(size_t offset);
	void Skip(size_t size);

	void Delete();
	uint8_t* data;
	size_t size = 0;
	size_t offset = 0;
private:
};