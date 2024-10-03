#!/bin/sh

gcc mini_snprintf.c flag_select.c ../exercicio1/int_to_string.c ../exercicio2/float_to_string.c mini_snprintf_test.c -o mini_snprintf_test -g -Wall -pedantic
