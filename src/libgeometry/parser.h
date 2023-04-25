#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 20

typedef struct point {
    double x;
    double y;
} Point;

typedef struct circle {
    Point point;
    double radius;
} Circle;

enum Errors {
    NAME,
    NOT_DOUBLE,
    BACK_BRACE,
    UNEXPECT_TOKEN,
    EXPECT_COMMA,
    UNEXPECT_COMMA,
};

void take_info_circle(Circle* circle, int* column, FILE* file);
void show_info_circle(Circle* circle);
void parser(void);