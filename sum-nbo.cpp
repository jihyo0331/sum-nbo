#include <cstddef>      // for size_t
#include <cstdint>      // for uint32_t, uint64_t
#include <cstdio>       // for printf, perror
#include <cstdlib>      // for exit, EXIT_FAILURE, EXIT_SUCCESS
#include <netinet/in.h> // for ntohl

void usage(const char *prog) {
    printf("syntax : %s <file1> [<file2>...]\n", prog);
    printf("sample : %s a.bin b.bin c.bin\n", prog);
    exit(EXIT_FAILURE);
}

uint32_t read_value(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror(filename);
        exit(EXIT_FAILURE);
    }

    uint8_t buf[4];
    if (fread(buf, sizeof(buf), 1, fp) != 1) {
        printf("Error reading file: %s\n", filename);
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    fclose(fp);

    uint32_t net_order = *reinterpret_cast<uint32_t*>(buf);
    return ntohl(net_order);
}

uint32_t* load_values(int argc, char *argv[], size_t &out_count) {
    out_count = static_cast<size_t>(argc - 1);
    uint32_t *values = new uint32_t[out_count];
    for (size_t i = 0; i < out_count; ++i) {
        values[i] = read_value(argv[i + 1]);
    }
    return values;
}

void print_result(const uint32_t *values, size_t count, uint64_t sum) {
    for (size_t i = 0; i < count; ++i) {
        printf("%" PRIu32 "(0x%08" PRIx32 ")", values[i], values[i]);
        if (i + 1 < count) {
            printf(" + ");
        }
    }
    printf(" = %" PRIu64 "(0x%08" PRIx64 ")\n", sum, sum);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        usage(argv[0]);
    }

    size_t count;
    uint32_t *values = load_values(argc, argv, count);

    uint64_t sum = 0;
    for (size_t i = 0; i < count; ++i) {
        sum += values[i];
    }

    print_result(values, count, sum);
    delete[] values;
    return EXIT_SUCCESS;
}
