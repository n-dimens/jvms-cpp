#ifndef JVMS_CLASSFILEREADER_H
#define JVMS_CLASSFILEREADER_H

#include <iostream>

union u1 {
    char bytes[1];
    uint8_t value;
};

union u2 {
    char bytes[2];
    uint16_t value;
};

union u4 {
    char bytes[4];
    uint32_t value;
};

struct ClassFile {
    u4 magic;
    u2 minorVersion;
    u2 majorVersion;
};

ClassFile read(std::istream &input);

#endif //JVMS_CLASSFILEREADER_H
