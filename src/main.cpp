#include "util.h"

int main(int argc, char *argv[]) {
    std::cout << argv[0] << '\n';
    if (LLVMCoverage::isPositive(argc)) {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
