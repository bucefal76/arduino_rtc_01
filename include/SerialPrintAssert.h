#ifndef SERIAL_PRINT_ASSERT_HPP
#define SERIAL_PRINT_ASSERT_HPP

#include <Arduino.h>
#include "ModuleConfig.hpp"

#ifdef USE_SERIAL

#define RUNTIME_ASSERT(condition)                   \
    if (false == condition)                         \
    {                                               \
        Serial.print(F("ASRT: " __FILE__ ", @: ")); \
        Serial.println(__LINE__);                   \
        while (true)                                \
            ;                                       \
    }

#define RUNTIME_PTR_CHECK(pointer)                  \
    if (nullptr == pointer)                         \
    {                                               \
        Serial.print(F("ASRT: " __FILE__ ", @: ")); \
        Serial.println(__LINE__);                   \
        while (true)                                \
            ;                                       \
    }

#else

#define RUNTIME_ASSERT(condition) \
    if (false == condition)       \
    {                             \
        while (true)              \
            ;                     \
    }

#define RUNTIME_PTR_CHECK(pointer) \
    if (nullptr == pointer)        \
    {                              \
        while (true)               \
            ;                      \
    }

#endif

#endif