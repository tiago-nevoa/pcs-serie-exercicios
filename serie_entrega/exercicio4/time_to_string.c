#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

size_t mini_snprintf(char *buffer, size_t buffer_size, const char *format, ...);

// Função para converter o tempo em string no formato "ww, dd-mm-yyyy, hh:mm:ss"
size_t time_to_string(struct tm *tm, char *buffer, size_t buffer_size) {
    // Arrays para os dias da semana e meses
    const char *weekdays[] = {
        "domingo", "segunda-feira", "terça-feira", "quarta-feira",
        "quinta-feira", "sexta-feira", "sábado"
    };

    // Verificar se o dia da semana e o mês são válidos
    if (tm->tm_wday < 0 || tm->tm_wday > 6 || tm->tm_mon < 0 || tm->tm_mon > 11) {
        return 0; // Dados inválidos
    }

    // Formatar a string com o formato "ww, dd-mm-yyyy, hh:mm:ss"
    int year = tm->tm_year + 1900; // tm_year é o número de anos desde 1900
    size_t result = snprintf(buffer, buffer_size, "%s, %02d-%02d-%04d, %02d:%02d:%02d",
                             weekdays[tm->tm_wday], tm->tm_mday, tm->tm_mon + 1, year,
                             tm->tm_hour, tm->tm_min, tm->tm_sec);

    // Verificar se o buffer é suficiente
    if (result >= buffer_size) {
        return 0; // Buffer insuficiente
    }

    // Retornar o tamanho da string gerada (sem o caractere nulo)
    return result;
}

// int main(void) 
// {
//     struct tm timeinfo = { .tm_sec = 23, .tm_min = 45, .tm_hour = 12, 
//                            .tm_mday = 16, .tm_mon = 8, .tm_year = 124, 
//                            .tm_wday = 1 };  // segunda-feira, 16 de setembro de 2024
//     char buffer[100];
//     size_t size = time_to_string(&timeinfo, buffer, sizeof(buffer));

//     if (size > 0) {
//         printf("Resultado: %s\n", buffer);
//     } else {
//         printf("Buffer insuficiente.\n");
//     }

//     return 0;
// }
