#include "sum_nbo.h"
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        usage(argv[0]);
    }

    size_t count;
    uint32_t* values = load_values(argc, argv, count);

    uint64_t sum = 0;
    for (size_t i = 0; i < count; ++i) {
        sum += values[i];
    }

    print_result(values, count, sum);
    delete[] values;
    return EXIT_SUCCESS;
}
