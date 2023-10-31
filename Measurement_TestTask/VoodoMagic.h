#pragma once

#include <functional>
#include <iostream>

#if defined(__i386__) || defined(_M_IX96)
    #define ARCH_X86
#elif defined(__x86_64__) || defined(_M_X64)
    #define ARCH_X64
#else
    #error "Undefined CPU architecture
#endif

#ifdef ARCH_X64
    typedef unsigned long long uint_ptr;
#else
    typedef unsigned int uint_ptr;
#endif 


template<typename T, typename... U>
uint_ptr GetFuncAddress(std::function<T(U...)> f)
{
    typedef T(fn_type)(U...);
    fn_type** fn_ptr = f.template target<fn_type*>();
    return (uint_ptr)*fn_ptr;
}

template<typename T, typename... U>
bool FunctionsEquals(const std::function<T(U...)>& f1, const std::function<T(U...)>& f2)
{
    auto adr1 = GetFuncAddress(f1);
    auto adr2 = GetFuncAddress(f2);
    return adr1 == adr2;
}
