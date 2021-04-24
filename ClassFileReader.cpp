#include <iostream>
#include <vector>

#include "ClassFileReader.h"
#include "ConstantPool.h"

using namespace std;

u1 read_u1(istream &input);
void read_u1(istream &input, u1 &field);
u2 read_u2(istream &input);
void read_u2(istream &input, u2 &field);
void read_u4(istream &input, u4 &field);

ClassFile read(std::istream &input) {
    if (!input) {
        cout << "Corrupted input stream";
        return ClassFile{};
    }

    ClassFile result{};
    read_u4(input, result.magic);
    read_u2(input, result.minorVersion);
    read_u2(input, result.majorVersion);

    u2 constantPoolCount = read_u2(input);
    cout << "CST SIZE: " << constantPoolCount.value << endl;

    int counter = 0;
    vector<Constant *> constantPool(constantPoolCount.value - 1);
    while (counter < constantPool.size()) {
        auto tag = (ConstantPoolTag) read_u1(input).value;
        switch (tag) {
            case CONSTANT_Class: {
                auto poolItem = new ClassInfo();
                read_u2(input, poolItem->nameIndex);
                constantPool[counter] = poolItem;
                break;
            }
            case CONSTANT_Fieldref: {
                auto poolItem = new FieldRefInfo();
                read_u2(input, poolItem->classIndex);
                read_u2(input, poolItem->nameAndTypeIndex);
                constantPool[counter] = poolItem;
                break;
            }
            case CONSTANT_Methodref: {
                auto poolItem = new MethodRefInfo();
                read_u2(input, poolItem->classIndex);
                read_u2(input, poolItem->nameAndTypeIndex);
                constantPool[counter] = poolItem;
                break;
            }
            case CONSTANT_InterfaceMethodref: {
                auto poolItem = new InterfaceMethodRefInfo();
                read_u2(input, poolItem->classIndex);
                read_u2(input, poolItem->nameAndTypeIndex);
                constantPool[counter] = poolItem;
                break;
            }
            case CONSTANT_String: {
                auto poolItem = new StringInfo();
                read_u2(input, poolItem->stringIndex);
                constantPool[counter] = poolItem;
                break;
            }
            case CONSTANT_Integer: {
                auto poolItem = new IntegerInfo();
                read_u4(input, poolItem->bytes);
                constantPool[counter] = poolItem;
                break;
            }
            case CONSTANT_Float: {
                auto poolItem = new FloatInfo();
                read_u4(input, poolItem->bytes);
                constantPool[counter] = poolItem;
                break;
            }
            case CONSTANT_Long: {
                auto poolItem = new LongInfo();
                read_u4(input, poolItem->highBytes);
                read_u4(input, poolItem->lowBytes);
                constantPool[counter] = poolItem;
                break;
            }
            case CONSTANT_Double: {
                auto poolItem = new DoubleInfo();
                read_u4(input, poolItem->highBytes);
                read_u4(input, poolItem->lowBytes);
                constantPool[counter] = poolItem;
                break;
            }
            case CONSTANT_NameAndType: {
                auto poolItem = new NameAndTypeInfo();
                read_u2(input, poolItem->nameIndex);
                read_u2(input, poolItem->descriptorIndex);
                constantPool[counter] = poolItem;
                break;
            }
            case CONSTANT_Utf8: {
                auto poolItem = new Utf8Info();
                read_u2(input, poolItem->length);
                for (int i = 0; i < poolItem->length.value; i++) {
                    poolItem->bytes.push_back(read_u1(input));
                }
                constantPool[counter] = poolItem;
                break;
            }
            case CONSTANT_MethodHandle: {
                auto poolItem = new MethodHandleInfo();
                read_u1(input, poolItem->referenceKind);
                read_u2(input, poolItem->referenceIndex);
                constantPool[counter] = poolItem;
                break;
            }
            case CONSTANT_MethodType: {
                auto poolItem = new MethodTypeInfo();
                read_u2(input, poolItem->descriptorIndex);
                constantPool[counter] = poolItem;
                break;
            }
            case CONSTANT_InvokeDynamic: {
                auto poolItem = new InvokeDynamicInfo();
                read_u2(input, poolItem->bootstrapMethodAttrIndex);
                read_u2(input, poolItem->nameAndTypeIndex);
                constantPool[counter] = poolItem;
                break;
            }
        }
        counter++;
    }

    for (auto &item : constantPool) {
        delete item;
    }

    return result;
}

template<class T>
void reverse(T *bytes, int size);

u1 read_u1(istream &input) {
    u1 result;
    read_u1(input, result);
    return result;
}

void read_u1(istream &input, u1 &field) {
    input.read(field.bytes, 1);
}

u2 read_u2(istream &input) {
    u2 result;
    read_u2(input, result);
    return result;
}

void read_u2(istream &input, u2 &field) {
    input.read(field.bytes, 2);
    reverse(field.bytes, 2);
}

void read_u4(istream &input, u4 &field) {
    input.read(field.bytes, 4);
    reverse(field.bytes, 4);
}

template<class T>
void reverse(T *bytes, int size) {
    T result[size];
    for (int i = size; i > 0; i--) {
        result[size - i] = bytes[i - 1];
    }

    for (int i = 0; i < size; i++) {
        bytes[i] = result[i];
    }
}


