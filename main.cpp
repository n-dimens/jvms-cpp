#include <fstream>
#include <iostream>
#include "boost/program_options.hpp"

#include "ClassFileReader.h"

using namespace std;
namespace opt = boost::program_options;

void parseOptions(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    parseOptions(argc, argv);

    ifstream classFileStream("/home/svgorbunov/projects/jvms-cpp/MainKt.class", ios::in | ios::binary);
    if (!classFileStream) {
        cout << "Couldn't open file.\n";
        exit(1);
    }

    ClassFile cf = read(classFileStream);
    classFileStream.close();

    cout << "MAGIC: 0x" << hex << cf.magic.value << endl
         << "VERSION: " << dec << cf.majorVersion.value << "." << cf.minorVersion.value << endl;

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
