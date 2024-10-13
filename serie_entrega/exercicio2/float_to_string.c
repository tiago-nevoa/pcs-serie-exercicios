#include <stdio.h>
#include <string.h>

size_t int_to_string(unsigned value, int base, char buffer[], size_t buffer_size);

size_t float_to_string(float value, char buffer[], size_t buffer_size) {
    // Multiplicador para obter 6 casas decimais
    const int multiplier = 1000000;

    // Verifica o sinal
    int sign = (value < 0) ? -1 : 1;
    value *= sign;

    // Separa a parte inteira e a parte fracionária
    unsigned int int_part = (unsigned int)value;
    unsigned int frac_part = (unsigned int)((value - int_part) * multiplier);

    size_t total_size = 0;

    // Adiciona sinal se necessário
    if (sign == -1) {
        if (total_size + 1 >= buffer_size) return 0; // Verifica espaço no buffer
        buffer[total_size++] = '-';
    }

    // Converte a parte inteira para string
    size_t int_size = int_to_string(int_part, 10, buffer + total_size, buffer_size - total_size);
    if (int_size == 0) return 0; // Erro na conversão
    total_size += int_size;

    // Adiciona o ponto decimal
    if (total_size + 1 >= buffer_size) return 0; // Verifica espaço no buffer
    buffer[total_size++] = '.';

    // Converte a parte fracionária para string
    size_t frac_size = int_to_string(frac_part, 10, buffer + total_size, buffer_size - total_size);
    if (frac_size == 0) return 0; // Erro na conversão
    total_size += frac_size;

    // Preenche com zeros até completar 6 casas decimais, se necessário
    while (frac_size < 6) {
        if (total_size + 1 >= buffer_size) return 0; // Verifica espaço no buffer
        buffer[total_size++] = '0';
        frac_size++;
    }

    // Adiciona o terminador da string
    buffer[total_size] = '\0';

    return total_size; // Retorna o tamanho da string gerada
}

// int main() {
//     char buffer[50];
//     float value = -123.456789;

//     size_t size = float_to_string(value, buffer, sizeof(buffer));
//     if (size > 0) {
//         printf("Resultado: %s\n", buffer);
//     } else {
//         printf("Buffer insuficiente.\n");
//     }

//     return 0;
// }
