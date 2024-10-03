#include <stdarg.h>
#include <string.h>
#include <stdio.h>

size_t flag_select(char flag, va_list arguments, char *buffer, size_t buffer_size);

size_t mini_snprintf(char *buffer, size_t buffer_size, const char *format, ...) {
    size_t counter = 0;
    va_list arguments;

    va_start(arguments, format);
    size_t i = 0, buffer_pos = 0;
    while (format[i] != '\0' && buffer_pos < buffer_size - 1) { // Evitar buffer overflow
        if (format[i] == '%') {
            i++;
            if (format[i] != '\0') {
                int len = flag_select(format[i], arguments, buffer + buffer_pos, buffer_size - buffer_pos);
                if (len == 0) {
                    break; // Erro ao processar a flag ou buffer insuficiente
                }
                buffer_pos += len;
                counter += len;
            }
        } else {
            buffer[buffer_pos++] = format[i];
            counter++;
        }
        i++;
    }

    buffer[buffer_pos] = '\0'; // Garantir que o buffer é terminado com nulo
    va_end(arguments);
    return counter;
}

// int main() {
//     char buffer[100];
//     mini_snprintf(buffer, sizeof(buffer), "Hello %s, number: %d, hex: %x, percent: %%", "world", 123, 255);
//     printf("%s\n", buffer); // Deve imprimir: Hello world, number: 123, hex: 0xff, percent: %
//     return 0;
// }
