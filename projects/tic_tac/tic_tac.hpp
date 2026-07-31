#ifndef TIC_TAC_HPP
#define TIC_TAC_HPP

#include <cstddef>

struct Tic_tac {
    int *data;
    std::size_t size;
    std::size_t capacity;
};

void tic_tac_init(Tic_tac &s, std::size_t capacity);
void tic_tac_push(Tic_tac &s, int value);
bool tic_tac_pop(Tic_tac &s, int &value);
bool tic_tac_peek(const Tic_tac &s, int &value);
bool tic_tac_is_empty(const Tic_tac &s);
void tic_tac_destroy(Tic_tac &s);

#endif
