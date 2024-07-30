#ifndef ARGUMENTPARSER_HPP
#define ARGUMENTPARSER_HPP

namespace ArgumentParser {
    void Parse(const int& argc, char** argv);

    extern unsigned int image_width;
    extern unsigned int samples_per_pixel;
    extern unsigned int max_depth;
}

#endif