#include <iostream>
#include "options.hpp"
#include "replace.hpp"

int main(int argc, char *argv[])
{
    Options options(argc, argv);
    Replace(options).replace();
    return 0;
}
