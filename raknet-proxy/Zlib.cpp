
#include "Zlib.h"
#include <iostream>
#include <assert.h>

#define CHUNK (1024 * 1024)

#define CHECK_ERR(err, msg) { \
    if (err != Z_OK) { \
        fprintf(stderr, "%s error: %d\n", msg, err); \
        exit(1); \
    } \
}

Zlib* instance;

Zlib::Zlib()
{
}
static alloc_func zalloc = (alloc_func)0;
static free_func zfree = (free_func)0;

void vucarrWrite(vucarr& out, const unsigned char* buf, size_t bufLen)
{
    out.insert(out.end(), buf, buf + bufLen);
}

size_t vucarrRead(const vucarr& in, unsigned char*& inBuf, size_t& inPosition)
{
    size_t from = inPosition;
    inBuf = const_cast<unsigned char*>(in.data()) + inPosition;
    inPosition += std::min((size_t)CHUNK, in.size() - from);
    return inPosition - from;
}

size_t Zlib::Inflate(uint8_t* dst, int dst_offset, uLong dst_size,const uint8_t* src, int src_offset, int src_size) {
    z_stream  stream;
    memset(&stream, 0, sizeof(z_stream));
    stream.next_in = (Bytef*)(src + src_offset);
    stream.avail_in = src_size;
    stream.next_out = dst + dst_offset;
    stream.avail_out = dst_size;

    // https://wiz-code.net/blog/2009/09/zlibdll-zlibnet-deflatestream.html
    inflateInit2(&stream, -MAX_WBITS);

    int result = inflate(&stream, 0);
    std::cout << result << std::endl;
    if (result == Z_OK || result == Z_STREAM_END) {
        inflateEnd(&stream);
        return stream.total_out;
    }
}

Zlib::~Zlib()
{
}

Zlib* Zlib::getZlib() {
    if (!instance) {
        instance = new Zlib();
    }
    return instance;
}