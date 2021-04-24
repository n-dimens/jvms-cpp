#ifndef JVMS_CONSTANTPOOL_H
#define JVMS_CONSTANTPOOL_H

#include <vector>
#include "CommonTypes.h"

enum ConstantPoolTag {
    CONSTANT_Class = 7,
    CONSTANT_Fieldref = 9,
    CONSTANT_Methodref = 10,
    CONSTANT_InterfaceMethodref = 11,
    CONSTANT_String = 8,
    CONSTANT_Integer = 3,
    CONSTANT_Float = 4,
    CONSTANT_Long = 5,
    CONSTANT_Double = 6,
    CONSTANT_NameAndType = 12,
    CONSTANT_Utf8 = 1,
    CONSTANT_MethodHandle = 15,
    CONSTANT_MethodType = 16,
    CONSTANT_InvokeDynamic = 18
};

struct Constant {
    ConstantPoolTag tag;
};

struct ClassInfo : public Constant {
    u2 nameIndex;

    ClassInfo() : Constant() {
        tag = CONSTANT_Class;
    }
};

struct FieldRefInfo : public Constant {
    u2 classIndex;
    u2 nameAndTypeIndex;

    FieldRefInfo() : Constant() {
        tag = CONSTANT_Fieldref;
    }
};

struct MethodRefInfo : public Constant {
    u2 classIndex;
    u2 nameAndTypeIndex;

    MethodRefInfo() : Constant() {
        tag = CONSTANT_Methodref;
    }
};

struct InterfaceMethodRefInfo : public Constant {
    u2 classIndex;
    u2 nameAndTypeIndex;

    InterfaceMethodRefInfo() : Constant() {
        tag = CONSTANT_InterfaceMethodref;
    }
};

struct StringInfo : public Constant {
    u2 stringIndex;

    StringInfo() : Constant() {
        tag = CONSTANT_String;
    }
};

struct IntegerInfo : public Constant {
    u4 bytes;

    IntegerInfo() : Constant() {
        tag = CONSTANT_Integer;
    }
};

struct LongInfo : public Constant {
    u4 highBytes;
    u4 lowBytes;

    LongInfo() : Constant() {
        tag = CONSTANT_Long;
    }
};

struct FloatInfo : public Constant {
    u4 bytes;

    FloatInfo() : Constant() {
        tag = CONSTANT_Float;
    }
};

struct DoubleInfo : public Constant {
    u4 highBytes;
    u4 lowBytes;

    DoubleInfo() : Constant() {
        tag = CONSTANT_Double;
    }
};

struct NameAndTypeInfo : public Constant {
    u2 nameIndex;
    u2 descriptorIndex;

    NameAndTypeInfo() : Constant() {
        tag = CONSTANT_NameAndType;
    }
};

struct Utf8Info : public Constant {
    u2 length;
    std::vector<u1> bytes;

    Utf8Info() : Constant() {
        tag = CONSTANT_Utf8;
    }
};

struct MethodHandleInfo : public Constant {
    u1 referenceKind;
    u2 referenceIndex;

    MethodHandleInfo() : Constant() {
        tag = CONSTANT_MethodHandle;
    }
};

struct MethodTypeInfo : public Constant {
    u2 descriptorIndex;

    MethodTypeInfo() : Constant() {
        tag = CONSTANT_MethodType;
    }
};

struct InvokeDynamicInfo : public Constant {
    u2 bootstrapMethodAttrIndex;
    u2 nameAndTypeIndex;

    InvokeDynamicInfo() : Constant() {
        tag = CONSTANT_InvokeDynamic;
    }
};

const char *getTagLabel(ConstantPoolTag value);

#endif //JVMS_CONSTANTPOOL_H
