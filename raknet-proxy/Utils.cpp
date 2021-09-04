#include "Utils.h"

Utils::Utils()
{
}

Utils::~Utils()
{
}

Utils* instance;
Utils* Utils::get() {
    if (!instance) {
        instance = new Utils();
    }
    return instance;
}

int Utils::VarUint32(RakNet::BitStream bstream, int offset) {
    return 0;
}