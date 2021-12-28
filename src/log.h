#pragma once

#define LOG_DEBUG(...) log_print(L_DEBUG, __VA_ARGS__);
#define LOG_INFO(...) log_print(L_INFO, __VA_ARGS__);
#define LOG_ERROR(...) log_print(L_ERROR, __VA_ARGS__);

typedef enum {
        L_DEBUG,
        L_INFO,
        L_ERROR,
} LogLevel;

void log_print(LogLevel level, char const * format, ...);
void log_set_level(LogLevel level);
