#include <stdio.h>
size_t float_to_string(float value, char buffer[], size_t buffer_size) {
    // Formatação simples para float
    int result_size = snprintf(buffer, buffer_size, "%.6f", value);
    return (result_size < 0 || (size_t)result_size >= buffer_size) ? 0 : (size_t)result_size;
}
