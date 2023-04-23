#pragma once
#ifndef DEBUG_HPP
#define DEBUG_HPP

#ifndef MY_DEBUG
  #define MY_DEBUG 1 // to disable debug, set this to 0 (in PlatformIO this is done automatically, depending on the build target)
#endif

#if MY_DEBUG > 0
    #define MYLOG(tag, ...)            \
        do                             \
        {                              \
            if (tag)                   \
                PRINTF("[%s] ", tag);  \
            PRINTF(__VA_ARGS__);       \
            PRINTF("\n");              \
        } while (0)
#else
    #define MYLOG(...)
#endif

#endif // DEBUG_HPP
