//
// Created by mmas6 on 25.03.2020.
//

#include "lab5_exceptions.h"

const char* QueueOut::what()const noexcept {
    return "\tProhibited operation!\n"
           "\tNote: Your queue is full.\n";
}

const char* QueueEmpty::what()const noexcept {
    return "\tProhibited operation!\n"
           "\tNote: Your queue is empty.\n";
}