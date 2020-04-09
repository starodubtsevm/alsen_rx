#include "decode.h"

#include <algorithm>

decode::decode(): FCode(0), FBaseCode(0)
{
}

std::string decode::toString() const
{
    std::string Res;
    uint8 Temp = FCode;
    for(int i = 0; i < 8; ++i)
    {
        if(Temp & 1) Res.insert(0,"1");
         else Res.insert(0,"0");
        Temp >>= 1;
    }
    return Res;
}

bool decode::proc(decode::uint8 ABit)
{
    FCode <<= 1; // младший бит в 0
    if (ABit) FCode |= 1; // младший бит в 1
    return IsValid();
}

bool decode::IsValid()
{
    auto Iter = std::find(bauerCodeFullArray, bauerCodeFullArray + 128, FCode);
    if(Iter == (bauerCodeFullArray + 128))
    {
        FBaseCode = 0;
        return false;
    }

    auto IndexOfElem = std::distance(bauerCodeFullArray,Iter);
    long IndexOfRow = IndexOfElem / 8;
    FBaseCode = bauerCode[IndexOfRow];
    return true;
}
