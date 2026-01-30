#include "pch.h"
#include "textfmt.h"

void textfmt::fmt(char* buf, int buf_size, char* format, char** args, int argscount) {
    if (buf == nullptr || buf_size <= 0) {
        return; 
    }

    const char* p_format = format; 
    char* p_buf = buf;             
    int remaining_size = buf_size; 

    while (*p_format != '\0' && remaining_size > 1) {
        if (p_format[0] == '{' && p_format[1] >= '0' && p_format[1] <= '9' && p_format[2] == '}') {
            int arg_index = p_format[1] - '0'; 

            if (arg_index < argscount) {
                const char* arg_str = args[arg_index];
                int arg_len = strlen(arg_str);
                int len_to_copy = std::min(arg_len, remaining_size - 1);

                memcpy(p_buf, arg_str, len_to_copy);
                p_buf += len_to_copy;
                remaining_size -= len_to_copy;
            }
            p_format += 3;
        }
        else {
            *p_buf = *p_format;
            p_buf++;
            p_format++;
            remaining_size--;
        }
    }

    *p_buf = '\0';
}