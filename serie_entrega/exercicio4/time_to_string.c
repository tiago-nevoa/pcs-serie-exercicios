#include <stdio.h>
#include <string.h>
#include <time.h>

size_t time_to_string(struct tm *tm, char *buffer, size_t buffer_size) 
{

    const char *weekdays[] = 
    {
        "domingo", "segunda-feira", "terça-feira", "quarta-feira",
        "quinta-feira", "sexta-feira", "sábado"
    };

const char *months[] =
    {
        "janeiro", "fevereiro", "março", "abril", "maio", "junho", 
        "julho", "agosto", "setembro", "outubro", "novembro", "dezembro"
    };

}