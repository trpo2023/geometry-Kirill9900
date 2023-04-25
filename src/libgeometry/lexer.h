#pragma once
#include "parser.h"
#include <stdbool.h>
#include <stdio.h>

void print_error(int column, int status);
void get_point(Point* point, int* column, FILE* file);
double get_number(int* column, FILE* file);
void del_space(int* column, FILE* file);
bool get_expect_token(char expect, int* column, int status, FILE* file);
bool get_unexpect_token(char unexpect, int* column, int status, FILE* file);
void end_of_line(int* column, FILE* file);