#include <stdio.h>
#include <stdarg.h>
#include <string.h>

size_t int_to_string(unsigned value, int base, char buffer[], size_t buffer_size);
size_t float_to_string(float value, char buffer[], size_t buffer_size);

size_t flag_select(char flag, va_list arguments, char *buffer, size_t buffer_size) {
    if (flag == 'c') {
        buffer[0] = (char)va_arg(arguments, int); // 'char' é promovido para 'int'
        return 1;
    }   
    else if (flag == 's') { 
        const char *str = va_arg(arguments, const char*);
        int len = strlen(str);
        if (len >= buffer_size) {
            return 0; // O buffer não é suficiente
        }
        strncpy(buffer, str, buffer_size - 1);
        buffer[buffer_size - 1] = '\0'; // Garantir que a string é terminada por nulo
        return len;
    }
    else if (flag == 'd') {
        return int_to_string(va_arg(arguments, unsigned int), 10, buffer, buffer_size);
    }
    else if (flag == 'x') {
        return int_to_string(va_arg(arguments, unsigned int), 16, buffer, buffer_size);
    }
    else if (flag == 'f') {
        return float_to_string(va_arg(arguments, double), buffer, buffer_size); // float é promovido para double
    }
    else if (flag == '%') {
        buffer[0] = '%';
        return 1;
    }
    return 0;
}
