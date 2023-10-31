#pragma once

#include <functional>

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


template<typename R, typename... Args>
uint_ptr GetFuncAddress(std::function<R(Args...)> f)
{
    typedef R(fn_type)(Args...);
    fn_type** fn_ptr = f.template target<fn_type*>();
    return reinterpret_cast<uint_ptr>(*fn_ptr);
}

template<typename R, typename... Args>
bool FunctionsEquals(const std::function<R(Args...)>& f1, const std::function<R(Args...)>& f2)
{
    auto adr1 = GetFuncAddress(f1);
    auto adr2 = GetFuncAddress(f2);
    return adr1 == adr2;
}
