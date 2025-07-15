#ifndef SUM_NBO_H
#define SUM_NBO_H

#include <cstddef>
#include <cstdint>

void usage(const char* prog);
uint32_t read_value(const char* filename);
uint32_t* load_values(int argc, char* argv[], size_t& out_count);
void print_result(const uint32_t* values, size_t count, uint64_t sum);

#endif // SUM_NBO_H
