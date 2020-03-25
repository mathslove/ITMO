//
// Created by mmas6 on 25.03.2020.
//

#include "lab5.h"

//Здание 2

const char* QueueException::what() const noexcept {
    return "\tProhibited operation!\n"
           "\tNote: Your queue is empty or full.";
}
