#ifndef JVMS_COMMONTYPES_H
#define JVMS_COMMONTYPES_H

#include <cstdint>

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

enum AccessFlags {
    ACC_PUBLIC = 0x00001,
    ACC_FINAL = 0x0010,
    ACC_SUPER = 0x0020,
    ACC_INTERFACE = 0x0200,
    ACC_ABSTRACT = 0x0400,
    ACC_SYNTHETIC = 0x1000,
    ACC_ANNOTATION = 0x2000,
    ACC_ENUM = 0x4000,
};

#endif //JVMS_COMMONTYPES_H
