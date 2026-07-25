#ifndef CALCULAOR_USER_HPP
#define CALCULAOR_USER_HPP

#include <cstddef>

struct Calculaor_user {
    int *data;
    std::size_t size;
    std::size_t capacity;
};

void calculaor_user_init(Calculaor_user &s, std::size_t capacity);
void calculaor_user_push(Calculaor_user &s, int value);
bool calculaor_user_pop(Calculaor_user &s, int &value);
bool calculaor_user_peek(const Calculaor_user &s, int &value);
bool calculaor_user_is_empty(const Calculaor_user &s);
void calculaor_user_destroy(Calculaor_user &s);

#endif
