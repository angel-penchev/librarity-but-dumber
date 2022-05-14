//
// Created by apenchev on 5/14/2022.
//

#ifndef LIBRARITY_BUT_DUMBER_EXCEPTION_H
#define LIBRARITY_BUT_DUMBER_EXCEPTION_H


#include <exception>

template<typename T>
class Exception : public std::exception {
public:
    T errorCode;
public:
    explicit Exception(T errorCode);

    T getErrorCode() const;

    virtual const char *getErrorMessage() const = 0;
};

template<typename T>
Exception<T>::Exception(T errorCode) : errorCode(errorCode) {}

template<typename T>
T Exception<T>::getErrorCode() const {
    return this->errorCode;
}


#endif //LIBRARITY_BUT_DUMBER_EXCEPTION_H
