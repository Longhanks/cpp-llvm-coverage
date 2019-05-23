#include "util.h"

bool LLVMCoverage::isPositive(int i) {
    if (i > 0) {
        std::cout << "[LOG] " << i << " is positive\n";
        return true;
    }
    std::cout << "[LOG] " << i << " is not positive\n";
    return false;
}
