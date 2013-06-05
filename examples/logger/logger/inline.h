#ifndef LOGGER_INLINE_H
#define LOGGER_INLINE_H

#include <stdio.h>

//#define LOG_DEBUG

extern inline void log_error(char* str);
extern inline void log_info(char* str);
extern inline void log_debug(char* str);

inline void log_error(char* str)
{
    fprintf(stderr, "%s\n", str);
}

inline void log_info(char* str)
{
    fprintf(stdout, "%s\n", str);
}

inline void log_debug(char* str)
{
#ifdef LOG_DEBUG
    log_info(str);
#endif
}

#endif /* LOGGER_INLINE_H */
