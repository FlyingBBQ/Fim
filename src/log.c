#include "log.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>

static LogLevel g_log_level = L_INFO;

static char const *
log_level_to_string(LogLevel level)
{
    const char * log_level_names[] = {
            "DEBUG",
            "INFO",
            "ERROR"
    };
    assert(level < sizeof(log_level_names));
    return log_level_names[level];
}

void
log_print(LogLevel level, char const * format, ...)
{
        if (level < g_log_level) {
                return;
        }
        va_list ap;
        printf("[%-5s ] ", log_level_to_string(level));
        va_start(ap, format);
        vprintf(format, ap);
        va_end(ap);
        printf("\n");
        fflush(stdout);
}

void
log_set_level(LogLevel level)
{
        g_log_level = level;
}
