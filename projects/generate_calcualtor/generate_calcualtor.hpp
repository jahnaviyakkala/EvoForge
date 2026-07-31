#ifndef GENERATE_CALCUALTOR_HPP
#define GENERATE_CALCUALTOR_HPP

#include <cstddef>

struct Generate_calcualtor {
    int *data;
    std::size_t size;
    std::size_t capacity;
};

void generate_calcualtor_init(Generate_calcualtor &s, std::size_t capacity);
void generate_calcualtor_push(Generate_calcualtor &s, int value);
bool generate_calcualtor_pop(Generate_calcualtor &s, int &value);
bool generate_calcualtor_peek(const Generate_calcualtor &s, int &value);
bool generate_calcualtor_is_empty(const Generate_calcualtor &s);
void generate_calcualtor_destroy(Generate_calcualtor &s);

#endif
