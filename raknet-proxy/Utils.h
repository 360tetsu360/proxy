#pragma once
#include <BitStream.h>
#include <string>
#include <vector>
class Utils
{
	Utils();
	~Utils();
public:
	static Utils* get();
	bool encode_base64(const std::vector<unsigned char>& src, std::string& dst);
	bool decode_base64(const std::string& src, std::vector<unsigned char>& dst);
private:

};