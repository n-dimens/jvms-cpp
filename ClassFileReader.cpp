#include <iostream>
#include "ClassFileReader.h"

using namespace std;

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
    return result;
}

template<class T>
void reverse(T *bytes, int size);

void read_u1(istream &input, u1 &field) {
    input.read(field.bytes, 1);
//    reverse(field.bytes, 1);
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


