#include "decode.h"

#include <algorithm>
#include <iostream>


decode::decode()
    : FCode(0),
      FBaseCode(0)
{
}

std::string decode::toString() const
{
    std::string Res;
    uint8 Temp = FCode;
    for(int i = 0; i < 8; ++i)
    {
        Res.insert( 0, std::to_string(Temp & 1) + std::string(". ") );
        Temp >>= 1;
    }
    Res.resize(Res.length()-2);
    Res = "["+Res+"]";
    return Res;
}

bool decode::proc(decode::uint8 ABit,  const uint8_t CodeAlsen )
{
    FCode <<= 1; // младший бит в 0
    if (ABit) FCode |= 1; // младший бит в 1

    FIsValid = IsValid( CodeAlsen );
    return FIsValid;
}

bool decode::IsValid( const uint8_t CodeAlsen )
{
    auto Iter = std::find(std::begin(bauerCodeFullArray), std::end(bauerCodeFullArray), FCode);
    if(Iter == std::end(bauerCodeFullArray))
    {
        FBaseCode = 0xff; // так ближе к коду максима (блок exept)
        return false;
    }

    auto IndexOfElem = std::distance(bauerCodeFullArray,Iter);
    long IndexOfRow = IndexOfElem / 8;
    FBaseCode = bauerCode[IndexOfRow];

    bool res = ( FBaseCode == CodeAlsen );
    return res;
}
