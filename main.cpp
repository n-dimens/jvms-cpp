#include <fstream>
#include <iostream>
#include <iomanip>
#include "boost/program_options.hpp"

#include "ClassFileReader.h"

using namespace std;
namespace opt = boost::program_options;

void parseOptions(int argc, char *argv[]);

// TODO: char*/string concatenation
void printAccessFlags(u2 value) {
    if (value.value & ACC_PUBLIC) {
        cout << "PUBLIC";
    }
    if (value.value & ACC_FINAL) {
        cout << " FINAL";
    }
    if (value.value & ACC_SUPER) {
        cout << " SUPER";
    }
    if (value.value & ACC_INTERFACE) {
        cout << " INTERFACE";
    }
    if (value.value & ACC_ABSTRACT) {
        cout << " ABSTRACT";
    }
    if (value.value & ACC_SYNTHETIC) {
        cout << " SYNTHETIC";
    }
    if (value.value & ACC_ANNOTATION) {
        cout << " ANNOTATION";
    }
    cout << endl;
}

int main(int argc, char *argv[]) {
    parseOptions(argc, argv);

    ifstream classFileStream("./MainKt.class", ios::in | ios::binary);
    if (!classFileStream) {
        cout << "Couldn't open file.\n";
        exit(1);
    }

    ClassFile *cf = read(classFileStream);
    if (!cf) {
        exit(1);
    }

    classFileStream.close();

    cout << std::setw(20) << "MAGIC: " << hex << cf->magic.value << endl
         << std::setw(20) << "VERSION: " << dec << cf->majorVersion.value << "." << cf->minorVersion.value << endl
         << std::setw(20) << "CONSTANT POOL SIZE: " << cf->constantPool.size() << endl
         << std::setw(20) << "INTERFACES COUNT: " << cf->interfaces.size() << endl
         << std::setw(20) << "ACCESS FLAGS: ";
    printAccessFlags(cf->accessFlags);

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
