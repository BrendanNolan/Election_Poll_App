#ifndef UNARYPREDICATE_H
#define UNARYPREDICATE_H

#include <functional>

template<class Arg> class UnaryPredicate : public std::unary_function<T, bool>
{
public:
    bool operator(const Arg& arg) const = 0;
};

#endif// UNARYPREDICATE_H
