#pragma once
#include <zlib.h>
#include <zconf.h>
#define NOMINMAX
#include <Windows.h>
#include <vector>
#include <algorithm>

typedef std::vector<unsigned char> vucarr;

class Zlib
{
	Zlib();
	~Zlib();
public:
	static Zlib* getZlib();
	size_t Inflate(uint8_t* dst, int dst_offset, uLong dst_size,const uint8_t* src, int src_offset, int src_size);
private:
	z_stream m_stream;
};