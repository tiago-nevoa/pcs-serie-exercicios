#include <stdio.h>

void format_with_leading_zero(int value, char *str) {
    if (value < 10) {
        str[0] = '0';         // Coloca o zero à esquerda
        str[1] = '0' + value; // Converte o valor para caractere
    } else {
        str[0] = '0' + (value / 10); // Extrai o primeiro dígito
        str[1] = '0' + (value % 10); // Extrai o segundo dígito
    }
    str[2] = '\0'; // Termina a string com o caractere nulo
}
