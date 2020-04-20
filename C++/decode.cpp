#include "decode.h"

#include <algorithm>
#include <iostream>


decode::decode(): FCode(0), FBaseCode(0)
{
}

std::string decode::toString() const
{
    std::string Res;
    uint8 Temp = FCode;
    for(int i = 0; i < 8; ++i)
    {
        Res.insert( 0, std::to_string(Temp & 1) + std::string(". ") );
//        if(Temp & 1)
//        {
//            Res.insert(0,"1. ");
//        }
//        else
//        {
//            Res.insert(0,"0. ");
//        }
        Temp >>= 1;
    }
    Res.resize(Res.length()-2);
    Res = "["+Res+"]";
    //std::cout << Res << std::endl;
    return Res;
}

bool decode::proc(decode::uint8 ABit,  const uint8_t CodeAlsen )
{
    FCode <<= 1; // младший бит в 0
    if (ABit) FCode |= 1; // младший бит в 1

    //printf( "byte: %d\n", FCode );

    return IsValid( CodeAlsen );
}

bool decode::IsValid( const uint8_t CodeAlsen )
{
    //TODO так правильнее
    auto Iter = std::find(std::begin(bauerCodeFullArray), std::end(bauerCodeFullArray), FCode);
    //auto Iter = std::find(bauerCodeFullArray, bauerCodeFullArray + 128, FCode);

    //TODO так правильнее
    if(Iter == std::end(bauerCodeFullArray))
    //if(Iter == (bauerCodeFullArray + 128))
    {
        FBaseCode = 0xff; // так ближе к коду максима (блок exept)

//        printf( "CodeAlsen: %d\n", CodeAlsen );
//        printf( "self.res: 0\n" );
//        printf( "byte: %d\n", FCode );
//        printf( "self.base: %d\n", FBaseCode );
//        printf( "\n" );
        return false;
    }

    auto IndexOfElem = std::distance(bauerCodeFullArray,Iter);
    long IndexOfRow = IndexOfElem / 8;
    //printf( "index: %d\n", (int)IndexOfRow );
    FBaseCode = bauerCode[IndexOfRow];
    //printf( "self.base: %d\n", FBaseCode );

//    printf( "CodeAlsen: %d\n", CodeAlsen );
    bool res = ( FBaseCode == CodeAlsen );
//    printf( "self.res: %d\n", (int)res );
//    printf( "byte: %d\n", FCode );
//    printf( "self.base: %d\n", FBaseCode );
//    printf( "\n" );
    return res;
}
