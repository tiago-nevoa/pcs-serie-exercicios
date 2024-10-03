#include <stdio.h>
#include <stdarg.h>
#include <string.h>

size_t float_to_string(float value, char buffer[], size_t buffer_size) {
    // Formatação simples para float
    int result_size = snprintf(buffer, buffer_size, "%.2f", value);
    return (result_size < 0 || (size_t)result_size >= buffer_size) ? 0 : (size_t)result_size;
}

size_t int_to_string(unsigned value, int base, char buffer[], size_t buffer_size) {
    // Verificar se a base é válida (2, 8, 10 ou 16)
    if (base != 2 && base != 8 && base != 10 && base != 16) {
        return 0;
    }

    // Prefixos para as bases 2, 8 e 16
    const char *prefix = "";
    if (base == 2) {
        prefix = "0b";
    } else if (base == 8) {
        prefix = "0";
    } else if (base == 16) {
        prefix = "0x";
    }

    // Determinar o comprimento do prefixo
    size_t prefix_len = strlen(prefix);

    // Criar um buffer temporário para armazenar o valor convertido
    char temp[65];  // 64 bits binários e o caractere nulo
    int i = 0;

    // Converter o número para a base desejada
    do {
        int digit = value % base;
        temp[i++] = (digit < 10) ? ('0' + digit) : ('a' + (digit - 10));
        value /= base;
    } while (value > 0 && i < sizeof(temp));

    // Verificar se o buffer é suficiente para o prefixo e o valor convertido
    size_t value_len = i;  // Tamanho do valor convertido (invertido no temp)
    if (prefix_len + value_len + 1 > buffer_size) {
        return 0;  // O buffer não é suficiente
    }

    // Copiar o prefixo para o buffer
    strcpy(buffer, prefix);

    // Copiar o valor convertido, invertendo a ordem dos dígitos
    for (int j = 0; j < value_len; ++j) {
        buffer[prefix_len + j] = temp[value_len - j - 1];
    }

    // Adicionar o caractere nulo no final
    buffer[prefix_len + value_len] = '\0';

    // Retornar o comprimento da string gerada (sem o caractere nulo)
    return prefix_len + value_len;
}

int flag_select(char flag, va_list arguments, char *buffer, size_t buffer_size) {
    if (flag == 'c') {
        buffer[0] = (char)va_arg(arguments, int); // 'char' é promovido para 'int' nas funções variádicas
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

int main() {
    char buffer[100];
    mini_snprintf(buffer, sizeof(buffer), "Hello %s, number: %d, hex: %x, percent: %%", "world", 123, 255);
    printf("%s\n", buffer); // Deve imprimir: Hello world, number: 123, hex: 0xff, percent: %
    return 0;
}
