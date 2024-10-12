#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

size_t mini_snprintf(char *buffer, size_t buffer_size, const char *format, ...);
void format_with_leading_zero(int value, char *str);

size_t time_to_string(struct tm *tm, char *buffer, size_t buffer_size) {
    // Array de stings para os dias da semana
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
    char day_str[3], month_str[3], hour_str[3], min_str[3], sec_str[3];
    
    // Formata cada parte usando a função format_with_leading_zero
    format_with_leading_zero(tm->tm_mday, day_str);
    format_with_leading_zero(tm->tm_mon + 1, month_str);
    format_with_leading_zero(tm->tm_hour, hour_str);
    format_with_leading_zero(tm->tm_min, min_str);
    format_with_leading_zero(tm->tm_sec, sec_str);

    // Chamada para mini_snprintf com as strings já formatadas
    size_t result = mini_snprintf(buffer, buffer_size, "%s, %s-%s-%d, %s:%s:%s",
                                    weekdays[tm->tm_wday], day_str, month_str, year,
                                    hour_str, min_str, sec_str);


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
