#include "Reader.h"
#include <iostream>
Reader::Reader()
{
}

Reader::~Reader()
{
}

Reader::Reader(uint8_t* data, size_t length) {
	this->data = data;
	this->size = length;
}

Reader::Reader(size_t length) {
	this->size = length;
	this->data = (uint8_t*)malloc(length);
}


uint8_t* Reader::Read(size_t length) {
	if (this->offset + length <= this->size) {
		uint8_t* re = this->data + offset;
		this->offset += length;
		return re;
	}
	else {
		return nullptr;
	}
}

uint8_t* Reader::absoluteRead(size_t length) {
	if (this->offset + length < this->size) {
		return this->data + offset;
	}
	else {
		return nullptr;
	}
}

uint8_t* Reader::absoluteRead(size_t pos, size_t length) {
	if (pos + length < this->size) {
		return this->data + pos;
	}
	else
	{
		return nullptr;
	}
}

void Reader::SetPosition(size_t offset) {
	this->offset = offset;
}

void Reader::Delete() {
	delete data;
}

int64_t Reader::ReadVarInt(uint32_t& length) {
	int64_t ret = Framer::get()->getVarint(this->data + this->offset, length);
	this->offset += length;
	return ret;
}

int Reader::ReadInt() {
	uint8_t* Address = Read(sizeof(int));
	if (Address == nullptr)
		return 0;
	return *reinterpret_cast<int*>(Address);
}

uint32_t Reader::ReadUnInt() {
	uint8_t* Address = Read(sizeof(int));
	if (Address == nullptr)
		return 0;
	return *reinterpret_cast<uint32_t*>(Address);
}

int Reader::ReadBigEndian() {
	uint8_t* Address = Read(sizeof(int));
	if (Address == nullptr)
		return 0;
	return Utils::get()->readBigEndian(Address);
}

int16_t Reader::ReadShort() {
	uint8_t* Address = Read(sizeof(int16_t));
	if (Address == nullptr)
		return 0;
	return *reinterpret_cast<int16_t*>(Address);
}

uint16_t Reader::ReadUnShort() {
	uint8_t* Address = Read(sizeof(uint16_t));
	if (Address == nullptr)
		return 0;
	return *reinterpret_cast<uint16_t*>(Address);
}

uint8_t Reader::ReadByte() {
	uint8_t* Address = Read(sizeof(uint8_t));
	if (Address == nullptr)
		return 0;
	return *reinterpret_cast<uint8_t*>(Address);
}

std::string Reader::ReadString(size_t length) {
	uint8_t* Address = Read(length);
	if (Address == nullptr)
		return "";
	return std::string((char*)Address,length);
}

template <typename T>
inline auto* Reader::ReadCustom() {
	uint8_t* Address = Read(sizeof(T));
	if (Address == nullptr)
		assert("aaaaaa!!!!");
	return *reinterpret_cast<T*>(Address);
};

void Reader::Skip(size_t size) {
	this->offset += size;
}