//
// Created by mmas6 on 25.03.2020.
//

#ifndef PROGA_LAB5_EXCEPTIONS_H
#define PROGA_LAB5_EXCEPTIONS_H

#include <exception>

class QueueException: public std::exception {
public:
    virtual const char* what() const noexcept= 0;
};

class QueueOut: public QueueException{
public:
    const char* what() const noexcept override;
};

class QueueEmpty: public QueueException{
public:
    const char* what() const noexcept override;
};

#endif //PROGA_LAB5_EXCEPTIONS_H
