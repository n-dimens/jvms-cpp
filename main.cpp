#include <fstream>
#include <iostream>
#include <iomanip>
#include "boost/program_options.hpp"

#include "ClassFileReader.h"

using namespace std;
namespace opt = boost::program_options;

void parseOptions(int argc, char *argv[]);

// TODO: char*/string concatenation
void printClassAccessFlags(u2 value) {
    if (value.value & CLASS_ACC_PUBLIC) {
        cout << "public ";
    }
    if (value.value & CLASS_ACC_FINAL) {
        cout << "final ";
    }
    if (value.value & CLASS_ACC_SUPER) {
//        cout << " super";
    }
    if (value.value & CLASS_ACC_INTERFACE) {
        cout << "interface ";
    }
    if (value.value & CLASS_ACC_ABSTRACT) {
        cout << "abstract ";
    }
    if (value.value & CLASS_ACC_SYNTHETIC) {
        cout << "synthetic ";
    }
    if (value.value & CLASS_ACC_ANNOTATION) {
        cout << "annotation ";
    }
    if (value.value & CLASS_ACC_ENUM) {
        cout << "enum ";
    }
}

void printFieldAccessFlags(u2 value) {
    if (value.value & FIELD_ACC_PUBLIC) {
        cout << "public ";
    }
    if (value.value & FIELD_ACC_PRIVATE) {
        cout << "private ";
    }
    if (value.value & FIELD_ACC_PROTECTED) {
        cout << "protected ";
    }
    if (value.value & FIELD_ACC_STATIC) {
        cout << "static ";
    }
    if (value.value & FIELD_ACC_FINAL) {
        cout << "final ";
    }
    if (value.value & FIELD_ACC_VOLATILE) {
        cout << "volatile ";
    }
    if (value.value & FIELD_ACC_TRANSIENT) {
        cout << "transient ";
    }
    if (value.value & FIELD_ACC_SYNTHETIC) {
        cout << "synthetic ";
    }
    if (value.value & FIELD_ACC_ENUM) {
        cout << "enum ";
    }
}

void printMethodAccessFlags(u2 value) {
    if (value.value & METHOD_ACC_ABSTRACT) {
        cout << "abstract ";
    }
    if (value.value & METHOD_ACC_PUBLIC) {
        cout << "public ";
    }
    if (value.value & METHOD_ACC_PRIVATE) {
        cout << "private ";
    }
    if (value.value & METHOD_ACC_PROTECTED) {
        cout << "protected ";
    }
    if (value.value & METHOD_ACC_STATIC) {
        cout << "static ";
    }
    if (value.value & METHOD_ACC_FINAL) {
        cout << "final ";
    }
    if (value.value & METHOD_ACC_SYNCHRONIZED) {
        cout << "synchronized ";
    }
    if (value.value & METHOD_ACC_BRIDGE) {
        cout << "bridge ";
    }
    if (value.value & METHOD_ACC_VARARGS) {
        cout << "varargs ";
    }
    if (value.value & METHOD_ACC_NATIVE) {
        cout << "native ";
    }
    if (value.value & METHOD_ACC_STRICT) {
        cout << "strict ";
    }
    if (value.value & METHOD_ACC_SYNTHETIC) {
        cout << "synthetic ";
    }
}

void printUtf8(Utf8Info &utf8) {
    for (int i = 0; i < utf8.bytes.size(); i++) {
        cout << utf8.bytes[i].bytes[0];
    }
}

void printClass(const ClassFile *cf) {
    cout << "VERSION: " << cf->majorVersion.value << "." << cf->minorVersion.value << endl;

    auto thisClassInfo = (ClassInfo *) cf->constantPool[cf->thisClass.value - 1];
    auto thisClassNameInfo = (Utf8Info *) cf->constantPool[thisClassInfo->nameIndex.value - 1];

    printClassAccessFlags(cf->accessFlags);
    cout << "class ";
    printUtf8(*thisClassNameInfo);
    cout << " : ";

    if (cf->superClass.value == 0) {
        cout << "Object";
    } else {
        auto superClassInfo = (ClassInfo *) cf->constantPool[cf->superClass.value - 1];
        auto superClassNameInfo = (Utf8Info *) cf->constantPool[superClassInfo->nameIndex.value - 1];
        printUtf8(*superClassNameInfo);
    }

    if (!cf->interfaces.empty()) {
        cout << " implements ";
        for (const auto &interface : cf->interfaces) {
            auto interfaceInfo = (ClassInfo *) cf->constantPool[interface->nameIndex.value - 1];
            auto interfaceNameInfo = (Utf8Info *) cf->constantPool[interfaceInfo->nameIndex.value - 1];
            printUtf8(*interfaceNameInfo);
            cout << ", ";
        }
    }

    cout << " {\n";
    cout << "fields:\n";
    for (const auto &field : cf->fields) {
        cout << endl << "\t";
        printFieldAccessFlags(field->accessFlags);
        auto nameInfo = (Utf8Info *) cf->constantPool[field->nameIndex.value - 1];
        printUtf8(*nameInfo);
        auto descriptorInfo = (Utf8Info *) cf->constantPool[field->descriptorIndex.value - 1];
        printUtf8(*descriptorInfo);
        cout << endl;
    }

    cout << "methods:\n";
    for (const auto &method : cf->methods) {
        cout << endl << "\t";
        printMethodAccessFlags(method->accessFlags);
        auto nameInfo = (Utf8Info *) cf->constantPool[method->nameIndex.value - 1];
        printUtf8(*nameInfo);
        auto descriptorInfo = (Utf8Info *) cf->constantPool[method->descriptorIndex.value - 1];
        printUtf8(*descriptorInfo);

        for (const auto &attr : method->attributes) {
            cout << endl << "\t\t";
            auto attrNameInfo = (Utf8Info *) cf->constantPool[attr->nameIndex.value - 1];
            printUtf8(*attrNameInfo);
        }

        cout << endl;
    }

    cout << "}\n";
}

int main(int argc, char *argv[]) {
    parseOptions(argc, argv);

    ifstream classFileStream("./Compiler.class", ios::in | ios::binary);
    if (!classFileStream) {
        cout << "Couldn't open file.\n";
        exit(1);
    }

    ClassFile *cf = read(classFileStream);
    if (!cf) {
        exit(1);
    }

    classFileStream.close();
    printClass(cf);

    delete cf;
    return 0;
}

void parseOptions(int argc, char *argv[]) {
    opt::options_description desc("All options");
    desc.add_options()
            ("help", "produce help message");
    opt::variables_map vm;
    opt::store(opt::parse_command_line(argc, argv, desc), vm);
    opt::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        exit(1);
    }
}
