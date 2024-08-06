#include "Utility/ArgumentParser.hpp"
#include "Utility/Helper.hpp"
#include <stdexcept>

unsigned int ArgumentParser::image_width = 800;
unsigned int ArgumentParser::samples_per_pixel = 100;
unsigned int ArgumentParser::max_depth = 50;

void ArgumentParser::Parse(const int& argc, char** argv) {

    if (argc > 8) {
        throw std::runtime_error("Too many input parameters.");
    }

    std::vector<std::string> args;
    for (int i = 1; i < argc; i++) {
        args.emplace_back(argv[i]);
    }

    for (int i = 0; i < args.size(); i++) {
        const auto& arg = args[i];
        if (arg == "-w" || arg == "-W" || arg == "-Width") {
            image_width = std::stoi(args[++i]);
            continue;
        }
        if (arg == "-s" || arg == "-S" || arg == "-Samples") {
            samples_per_pixel = std::stoi(args[++i]);
            continue;
        }
        if (arg == "-d" || arg == "-D" || arg == "-Depth") {
            max_depth = std::stoi(args[++i]);
            continue;
        }

        throw std::runtime_error("Parameter not found.");
    }
}