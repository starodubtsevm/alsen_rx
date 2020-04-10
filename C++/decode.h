#ifndef DECODE_H
#define DECODE_H

#include <vector>
#include <string>

class decode
{
public:
    using uint8 = unsigned char;

    decode();
    uint8 Code() const { return FCode; }
    uint8 BaseCode() const { return FBaseCode; }
    std::string toString() const;

    bool proc(uint8 ABit);
private:
    const uint8 bauerCode[16] = { 0x01, 0x1F, 0x2C, 0x32, 0x4A, 0x54, 0x67, 0x79, 0x86, 0x98, 0xAB, 0xB5, 0xCD, 0xD3, 0xE0, 0xFE };
    // полная таблица кодов бауэра - 128 значений
    // "плоский" массив
    const uint8 bauerCodeFullArray[128] =
    {
        0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, //12
        0x1f, 0x3e, 0x7c, 0xf8, 0xf1, 0xE3, 0xC7, 0x8f, //13
        0x2C, 0x58, 0xB0, 0x61, 0xC2, 0x85, 0x0B, 0x16, //0
        0x32, 0X64, 0xC8, 0x91, 0x23, 0x46, 0x8C, 0x19, //1
        0x4A, 0x94, 0x29, 0x52, 0xA4, 0x49, 0x92, 0x25, //2
        0x54, 0xA8, 0x51, 0xA2, 0x45, 0x8A, 0x15, 0x2A, //3
        0x67, 0xCE, 0x9D, 0x3B, 0x76, 0xEC, 0xD9, 0xB3, //4
        0x79, 0xF2, 0xE5, 0xCB, 0x97, 0x2F, 0x5E, 0xBC, //5
        0x86, 0x0D, 0x1A, 0x34, 0x68, 0xD0, 0xA1, 0x43, //6
        0x98, 0x31, 0x62, 0xC4, 0x89, 0x13, 0x26, 0x4C, //7
        0xAB, 0x57, 0xAE, 0x5D, 0xBA, 0x75, 0xEA, 0xD5, //8
        0xB5, 0x6B, 0xD6, 0xAD, 0x5B, 0xB6, 0x6D, 0xDA, //9
        0xCD, 0x9B, 0x37, 0x6E, 0xDC, 0xB9, 0x73, 0xE6, //10
        0xD3, 0xA7, 0x4F, 0x9E, 0x3D, 0x7A, 0xF4, 0xE9, //11
        0xE0, 0xc1, 0x83, 0x07, 0x0E, 0x1c, 0x38, 0x70, //14
        0xFE, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f  //15
    };

    uint8 FCode;
    uint8 FBaseCode;
    bool IsValid();
};

#endif // DECODE_H