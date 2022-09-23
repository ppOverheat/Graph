#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stack.h"

#define WIDTH 80
#define HEIGHT 25
#define MID 13
#define MAX_DEFINITION_X M_PI * 4
#define X_STEP 0.16
#define Y_STEP 0.1
#define MIN_DEFINITION_X 0
#define MAX_DEFINITION_Y 1
#define MIN_DEFINITION_Y -1
#define SPACE '.'
#define GRAPH '*'
#define SIZE_Y 25
#define SIZE_X 80

int getPriority(char op);
int isDigit(char sym);
void checkOperand(char* expression, int *i, char* op, int* no_error);
void ifLn(char* expression, int* i, int* no_error);
void ifCosOrCtg(char* expression, int* i, char* op, int* no_error);
void ifSinOrSqrt(char* expression, int* i, char* op, int* no_error);
void calcFunc(char* post_expr, double y_arr[SIZE_Y], double x_arr[SIZE_X], int i_arr[SIZE_X], int j_arr[SIZE_X]);
double calcY(char * post_expr, double x);
void drawFunc(int i_arr[SIZE_X], int j_arr[SIZE_X]);
void fillY(double y_arr[SIZE_Y]);
void fillX(double x_arr[SIZE_X]);
char* getString(int *length);
char* toPostfix(char * expression, char* post_expr, int* no_error);
double getBinResult(char operand, double a, double b);
double getResult(char operand, double a);
char* getNumber(char* expression, char * num, int* i);

#endif  // GRAPH_H_