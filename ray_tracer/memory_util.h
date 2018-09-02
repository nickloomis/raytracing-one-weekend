#ifndef RAY_TRACER_MEMORY_UTIL_H_
#define RAY_TRACER_MEMORY_UTIL_H_

#include <memory>

// make_unique is copy-pasted from
// https://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique
// and avoids the need for C++14 in the toolchain.
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

#endif  // RAY_TRACER_MEMORY_UTIL_H_