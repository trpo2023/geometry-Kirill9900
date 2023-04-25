#include <ctype.h>
#include <stdlib.h>

#include "lexer.h"
#include "parser.h"

void print_error(int column, int status)  
{
    for (int i = 0; i < column; i++) {
        putchar(' ');
    }
    printf("^\n");
    switch (status) {
    case ER_NAME:
        printf("Error at column %d: expected "
               "'circle'\n",
               column);
        break;
    case ER_NOT_DOUBLE:
        printf("Error at column %d: expected "
               "'<double>'\n",
               column);
        break;
    case ER_BACK_BRACE:
        printf("Error at column %d: expected ')'\n",
               column);
        break;
    case ER_UNEXPECT_TOKEN:
        printf("Error at column %d: expected "
               "token\n",
               column);
        break;
    case ER_EXPECT_COMMA:
        printf("Error at column %d: expected ','\n",
                column);
        break;
    case ER_UNEXPECT_COMMA:
        printf("Error at column %d: expected ','\n",
               column);
    }
}

void del_space(int* column, FILE* file)  
{
    char ch;
    while ((ch = getc(file)) == ' ') {
        *column += 1;  
        continue;
    }
    if (ch != ' ')
        ungetc(ch, file);
}

double get_number(int* column, FILE* file)
{
    char temp[20];
    char ch;
    int point_count = 0;
    int i = 0;   
    int minus_count = 0;

    del_space(column, file);

    while ((ch = getc(file)) != ' ') {
        temp[i] = ch;      

        if (temp[i] == '.') {
            point_count++;
            if (point_count > 1) {
                print_error(*column + i + 1, ER_NOT_DOUBLE);
                exit(EXIT_FAILURE);  
            }
        }

        if (temp[i] == '-') {
            minus_count++;
            if (minus_count > 1) {
                print_error(*column + i + 1, ER_NOT_DOUBLE);
                exit(EXIT_FAILURE);
            }
        }

        if (temp[i] == ')') {
            ungetc(temp[i], file);
            i++;
            break;
        }

        if (temp[i] == ',') {  
            ungetc(temp[i], file);
            break;
        }

        if (temp[i] == '(') {    
            i++;
            print_error(*column + i, ER_BACK_BRACE);
            exit(EXIT_FAILURE);
        }

        if (!isdigit(temp[i]) && temp[i] != '.' && temp[i] != '-') {   
            i++;
            print_error(*column + i, ER_NOT_DOUBLE);
            exit(EXIT_FAILURE);
        }

        i++;
    }
    del_space(column, file);    
    *column += i + 1;    
    char* eptr;
    return strtod(temp, &eptr);  
}
 
bool get_expect_token(char expect, int* column, int status, FILE* file) 
{
    char ch;
    if ((ch = getc(file)) == expect) {
        return true;
    } else {
            print_error(*column, status);
            exit(EXIT_FAILURE);
    }
}

bool get_unexpect_token(char unexpect, int* column, int status, FILE* file)
{
    char ch;
    if ((ch = getc(file)) == unexpect) {
        print_error(*column, status);
        exit(EXIT_FAILURE);
    }
    ungetc(ch, file);
    return true;
}

void get_point(Point* point, int* column, FILE* file)    
{
    point->x = get_number(column, file);             
    get_unexpect_token(',', column, ER_UNEXPECT_COMMA, file);  

    point->y = get_number(column, file);            
}

void end_of_line(int* column, FILE* file)
{
    char ch;
    while ((ch = getc(file)) != '\n' && ch != EOF) { 
        if (ch != ' ') {
            print_error(*column, ER_UNEXPECT_TOKEN);
            exit(EXIT_FAILURE);
        }
        *column += 1;
    }
}