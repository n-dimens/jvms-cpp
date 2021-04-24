#ifndef JVMS_CLASSFILEREADER_H
#define JVMS_CLASSFILEREADER_H

#include <iostream>
#include <vector>
#include "CommonTypes.h"
#include "ConstantPool.h"

struct Attribute {
    u2 nameIndex;
    u4 length;
    std::vector<u1> info;
};

struct Field {
    u2 accessFlags;
    u2 nameIndex;
    u2 descriptorIndex;
    std::vector<Attribute *> attributes;
    ~Field();
};

struct Method {
    u2 accessFlags;
    u2 nameIndex;
    u2 descriptorIndex;
    std::vector<Attribute *> attributes;
    ~Method();
};

struct ClassFile {
    u4 magic;
    u2 minorVersion;
    u2 majorVersion;
    std::vector<Constant *> constantPool;
    u2 accessFlags;
    u2 thisClass;
    u2 superClass;
    std::vector<ClassInfo *> interfaces;
    std::vector<Field *> fields;
    std::vector<Method *> methods;
    std::vector<Attribute *> attributes;
    ~ClassFile();
};

ClassFile *read(std::istream &input);

#endif //JVMS_CLASSFILEREADER_H
