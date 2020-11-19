/**
 * @file    All.cpp
 * @brief   All implementations.
 */

/* header files */
#include "ADNode.hpp"
#include "ADValue.hpp"
#include "AutoDiffer.hpp"
#include "Parser.hpp"

template <class T>
void ADValue<T>::print_hello() const {
    printf("Hello\n");
}

template <class T>
void Parser<T>::print_hello() const {
    printf("Hello\n");
}

template <class T>
void ADNode<T>::print_hello() const {
    printf("Hello\n");
}

template <class T>
void AutoDiffer<T>::print_hello() const {
    printf("Hello\n");
}

