#ifndef JVMS_CLASSFILEREADER_H
#define JVMS_CLASSFILEREADER_H

#include <iostream>
#include <vector>
#include "CommonTypes.h"
#include "ConstantPool.h"

struct ClassFile {
    u4 magic;
    u2 minorVersion;
    u2 majorVersion;
    std::vector<Constant *> constantPool;
    u2 accessFlags;
    u2 thisClass;
    u2 superClass;
    std::vector<ClassInfo *> interfaces;
    ~ClassFile();
};

ClassFile* read(std::istream &input);

#endif //JVMS_CLASSFILEREADER_H
