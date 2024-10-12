#!/bin/sh

gcc time_to_string.c format_with_leading_zero.c ../exercicio3/mini_snprintf.c ../exercicio3/flag_select.c ../exercicio1/int_to_string.c ../exercicio2/float_to_string.c time_to_string_test.c -o time_to_string_test -g -Wall -pedantic
