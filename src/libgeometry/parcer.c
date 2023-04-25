#include <stdio.h>

#include "lexer.h"
#include "parser.h"

void take_info_circle(Circle* circle, int* column, FILE* file)
{
    get_point(&circle->point, column, file);
    expect(',', column, EXPECT_COMMA, file);

    circle->radius = get_number(column, file);

    expect(')', column, BACK_BRACE, file);

    line_ending(column, file);
}

void show_info_circle(Circle* circle)
{
    printf("circle(%.2f %.2f, %.2f)\n",
           circle->point.x,
           circle->point.y,
           circle->radius);
}

void parser(void)
{
    char geom[NAME_SIZE] = {0};
    char ch;
    int column;

    puts("Enter a geometric shape (or q for exit):");
    while ((ch = getc(stdin)) != EOF && ch != 'q') {
        column = 0;
        do {
            if (ch == '(' || ch == ' ') {
                if (strcmp(geom, "circle") == 0) {
                    Circle circle;
                    take_info_circle(&circle, &column, stdin);
                    printf("\nYou have entered: \n");
                    show_info_circle(&circle);
                    break;
                } else {
                    print_error(0, NAME);
                    exit(EXIT_FAILURE);
                }
            }

            if (ch == ')') {
                print_error(column, BACK_BRACE);
                exit(EXIT_FAILURE);
            }

            geom[column++] = ch;

        } while ((ch = getc(stdin)) != '\n');
    }
}