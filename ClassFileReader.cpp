#include <iostream>
#include <vector>

#include "CommonTypes.h"
#include "ClassFileReader.h"
#include "ConstantPool.h"

using namespace std;

u1 read_u1(istream &input);
void read_u1(istream &input, u1 &field);
u2 read_u2(istream &input);
void read_u2(istream &input, u2 &field);
void read_u4(istream &input, u4 &field);

vector<Constant *> &readConstantPool(std::istream &input, vector<Constant *> &constantPool) {
    int counter = 0;
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

    return constantPool;
}

ClassFile *read(std::istream &input) {
    if (!input) {
        cout << "Corrupted input stream";
        return nullptr;
    }

    auto result = new ClassFile();
    read_u4(input, result->magic);
    read_u2(input, result->minorVersion);
    read_u2(input, result->majorVersion);

    u2 constantPoolCount = read_u2(input);
    vector<Constant *> constantPool(constantPoolCount.value - 1);
    result->constantPool = readConstantPool(input, constantPool);

    read_u2(input, result->accessFlags);
    read_u2(input, result->thisClass);
    read_u2(input, result->superClass);

    u2 interfacesCount = read_u2(input);
    vector<ClassInfo *> interfaces(interfacesCount.value);
    for (auto &interface : interfaces) {
        interface = new ClassInfo();
        read_u2(input, interface->nameIndex);
    }
    result->interfaces = interfaces;

    u2 fieldsCount = read_u2(input);
    vector<Field *> fields(fieldsCount.value);
    for (auto &field : fields) {
        field = new Field();
        read_u2(input, field->accessFlags);
        read_u2(input, field->nameIndex);
        read_u2(input, field->descriptorIndex);
        u2 attributesCount = read_u2(input);
        vector<Attribute *> attributes(attributesCount.value);
        for (auto &attribute : attributes) {
            attribute = new Attribute();
            read_u2(input, attribute->nameIndex);
            read_u4(input, attribute->length);
            for (int i = 0; i < attribute->length.value; i++) {
                attribute->info.push_back(read_u1(input));
            }
        }
        field->attributes = attributes;
    }
    result->fields = fields;

    u2 methodsCount = read_u2(input);
    vector<Method *> methods(methodsCount.value);
    for (auto &method : methods) {
        method = new Method();
        read_u2(input, method->accessFlags);
        read_u2(input, method->nameIndex);
        read_u2(input, method->descriptorIndex);
        u2 attributesCount = read_u2(input);
        vector<Attribute *> attributes(attributesCount.value);
        for (auto &attribute : attributes) {
            attribute = new Attribute();
            read_u2(input, attribute->nameIndex);
            read_u4(input, attribute->length);
            for (int i = 0; i < attribute->length.value; i++) {
                attribute->info.push_back(read_u1(input));
            }
        }
        method->attributes = attributes;
    }
    result->methods = methods;

    u2 attributesCount = read_u2(input);
    vector<Attribute *> attributes(attributesCount.value);
    for (auto &attribute : attributes) {
        attribute = new Attribute();
        read_u2(input, attribute->nameIndex);
        read_u4(input, attribute->length);
        for (int i = 0; i < attribute->length.value; i++) {
            attribute->info.push_back(read_u1(input));
        }
    }
    result->attributes = attributes;

    input.peek();
    if (!input.eof()) {
        cout << "[ERROR] No end.\n";
        while (!input.eof()) {
            int last = read_u1(input).value;
            cout << ":" << last;
        }
        cout << endl;
        cout << "=======================\n";
    } else {
        cout << "SUCCESS\n";
        cout << "=======================\n";
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

ClassFile::~ClassFile() {
    for (auto &item : constantPool) {
        delete item;
    }

    for (auto &interface : interfaces) {
        delete interface;
    }

    for (auto &field : fields) {
        delete field;
    }

    for (auto &method : methods) {
        delete method;
    }

    for (auto &attribute : attributes) {
        delete attribute;
    }
}

Field::~Field() {
    for (auto &attribute : attributes) {
        delete attribute;
    }
}

Method::~Method() {
    for (auto &attribute : attributes) {
        delete attribute;
    }
}
