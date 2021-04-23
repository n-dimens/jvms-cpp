#include <iostream>
#include "boost/program_options.hpp"

namespace opt = boost::program_options;

int main(int argc, char *argv[]) {
    opt::options_description desc("All options");
    desc.add_options()
            ("help", "produce help message");
    opt::variables_map vm;
    opt::store(opt::parse_command_line(argc, argv, desc), vm);
    opt::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    return 0;
}
