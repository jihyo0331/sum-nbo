#include "sum_nbo.h"
#include <cstdio>
#include <cstdlib>
#include <cinttypes>
#include <netinet/in.h>
#include <cstring>

void usage(const char* prog) {
    std::printf("syntax : %s <file1> [<file2>...]\n", prog);
    std::printf("sample : %s a.bin b.bin c.bin\n", prog);
    std::exit(EXIT_FAILURE);
}

uint32_t read_value(const char* filename) {
    FILE* fp = std::fopen(filename, "rb");
    if (!fp) {
        std::perror(filename);
        std::exit(EXIT_FAILURE);
    }
    uint8_t buf[4];
    if (std::fread(buf, sizeof(buf), 1, fp) != 1) {
        std::fprintf(stderr, "Error reading file: %s\n", filename);
        std::fclose(fp);
        std::exit(EXIT_FAILURE);
    }
    std::fclose(fp);
    uint32_t net_order;
    std::memcpy(&net_order, buf, sizeof(net_order));
    return ntohl(net_order);
}

uint32_t* load_values(int argc, char* argv[], size_t& out_count) {
    out_count = static_cast<size_t>(argc - 1);
    uint32_t* values = new uint32_t[out_count];
    for (size_t i = 0; i < out_count; ++i) {
        values[i] = read_value(argv[i + 1]);
    }
    return values;
}

void print_result(const uint32_t* values, size_t count, uint64_t sum) {
    for (size_t i = 0; i < count; ++i) {
        std::printf("%" PRIu32 "(0x%08" PRIx32 ")", values[i], values[i]);
        if (i + 1 < count) {
            std::printf(" + ");
        }
    }
    std::printf(" = %" PRIu64 "(0x%08" PRIx64 ")\n", sum, sum);
}
