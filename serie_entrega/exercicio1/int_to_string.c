#include <stdio.h>
#include <string.h>

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
