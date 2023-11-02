#pragma once

#include <functional>

using Callback = std::function<void(void)>;

template<typename T>
using SingleArgumentCallback = std::function<void(T)>;

template<typename T>
using ReturnValueCallback = std::function<T(void)>;

template<typename R, typename Arg>
using ReturnValueSingleArgumentCallback = std::function<R(Arg)>;