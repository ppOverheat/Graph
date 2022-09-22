#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct stack { // #include "stack.h"
    char operand;
    double value;
    struct stack* next;
} stack;

#define WIDTH 80
#define HEIGHT 25
#define MID 13

#define pi 3.14
#define MAX_DEFINITION_X pi * 4

#define X_STEP 0.16
#define Y_STEP 0.1

#define MIN_DEFINITION_X 0

#define MAX_DEFINITION_Y 1
#define MIN_DEFINITION_Y -1

#define SPACE '.'
#define GRAPH '*'


#define SIZE_Y 25
#define SIZE_X 80

void checkOperand(char* expression, int *i, char* op, int* no_error);
char* pullStack(char* post_expr, struct stack* top, int *k);
void ifLn(char* expression, int* i, char* op, int* no_error);
void ifCosOrCtg(char* expression, int* i, char* op, int* no_error);
void ifSinOrSqrt(char* expression, int* i, char* op, int* no_error);
void calcFunc(char* post_expr, double y_arr[SIZE_Y], double x_arr[SIZE_X], int i_arr[SIZE_X], int j_arr[SIZE_X]);
double calcY(char * post_expr, double x);
void drawFunc(int i_arr[SIZE_X], int j_arr[SIZE_X]);
void fillY(double y_arr[SIZE_Y]);
void fillX(double x_arr[SIZE_X]);
void process();
char* getString(int *length);
char* toPostfix(char * expression, char* post_expr, int* no_error);
double getBinResult(char operand, double a, double b);
double getResult(char operand, double a);
char* getNumber(char* expression, char * num, int* i, int* k);

struct stack* init(char operand, double value);
struct stack* push(char operand, double value, struct stack* top);
struct stack* pop(struct stack* top);
void destroy(struct stack* top);
int stackCount(struct stack* top);
struct stack* getTopValue(struct stack* top, double* last);

int main()
{
    process();
    return 0;
}

char* getString(int *length) {
    *length = 0;
    int capacity = 1;
    char *str = (char*) malloc(sizeof(char));
    char c = getchar();
    while (c != '\n') {
        if (c != ' ') {
            str[(*length)++] = c;
            if (*length >= capacity) {
                capacity *= 2;
                str = (char*) realloc(str, capacity * sizeof(char)); 
            }
        }
        c = getchar();          
    }
    str[*length] = '\0';
    return str;
}

void process() {
    int length = 0;
    char *expression = getString(&length);
    char* post_expr = (char*) malloc(length*sizeof(char));
    int no_error = 1;
    post_expr = toPostfix(expression, post_expr, &no_error);
    if (no_error == 1) {
        double y_arr[SIZE_Y], x_arr[SIZE_X];
        int i_arr[SIZE_X], j_arr[SIZE_X];
        fillY(y_arr);
        fillX(x_arr);
        calcFunc(post_expr, y_arr, x_arr, i_arr, j_arr);
        drawFunc(i_arr, j_arr);
    } else {
        printf("n/a");
    }
    free(expression);
    free(post_expr);
}

int isDigit(char sym) {
    return ('0' <= sym && sym <= '9') ? 1 : 0;
}

int getPriority(char op) {
    int priority = -1;
   switch(op) {
       case '(': priority = 0;  break;
       case '+':
       case '-': priority = 1; break;
       case '*':
       case '/': priority = 2; break;
       case '^': priority = 3; break;
       case 's': 
       case 'c': 
       case 't': 
       case 'g': 
       case 'q': 
       case 'l': 
       case '~': priority = 4; break;
       default: break;
   }
   return priority;
}

void ifSinOrSqrt(char* expression, int* i, char* op, int* no_error) {
    int size = strlen(expression);
    if (*i + 2 < size && expression[*i + 1] == 'i' && expression[*i + 2] == 'n') {
        *i += 2;
    } else if (*i + 3 < size && expression[*i + 1] == 'q' && expression[*i + 2] == 'r' && expression[*i + 3] == 't') {
        *op = 'q';
        *i += 3;
    } else {
        *no_error = 0;
    }
}

void ifCosOrCtg(char* expression, int* i, char* op, int* no_error) {
    int size = strlen(expression);
    if (*i + 1 < size) {
        if (expression[*i + 1] == 'o' && expression[*i + 2] == 's') {
            *i += 2;
        } else if (expression[*i + 1] == 't' && expression[*i + 2] == 'g') {
            *op = 'g';
            *i += 2;
        } else {
            *no_error = 0;
        }
} else {
    *no_error = 0;
}
}

void ifLn(char* expression, int* i, char* op, int* no_error) {
    int size = strlen(expression);
    if (*i + 1 < size && expression[*i + 1] == 'n') {
        *i += 1;
    } else {
         *no_error = 0;
    }
}

char* getNumber(char* expression, char * num, int* i, int* k) {
    int j = *i;
        for (j = *i; j < strlen(expression); j++) {
            if (isDigit(expression[j]) || expression[j] == '.') {
                num[*k] = expression[j];
                *k++;
            } else {
                break;
            }
        }
    j--;
    *i += j - *i;
    return num;
}

char* toPostfix(char * expression, char* post_expr, int* no_error) {
    struct stack* top = NULL;
    int k = 0, size = strlen(expression);
    double value = 0;
    for (int i = 0; i < size; i++) {
        char sym = expression[i];
        if (sym == 'x') {
            post_expr[k] = sym;
            k++;
        } else if (isDigit(sym)) {
           int j = i;
           for (j = i; j < size; j++) {
               if (isDigit(expression[j]) || expression[j] == '.') {
                   post_expr[k] = expression[j];
                    k++;
               } else {
                   break;
               }
           }
           j--; i += j - i;
           post_expr[k] = ' '; k++;
        } else if (sym == '(') {
            top = push(sym, value, top);
        } else if (sym == ')') {
            while (stackCount(top) > 0 && top->operand != '(') {
                post_expr[k] = top->operand;
                top = pop(top); k++;
            }
            top = pop(top);
        } else {
           checkOperand(expression, &i, &sym, no_error);
            while (stackCount(top) > 0 && (getPriority(top->operand)) >= getPriority(sym)) {
                post_expr[k] = top->operand;
                top = pop(top); k++;
            }
            top = push(sym, value, top);
        }
    }
    while (top != NULL) {
        struct stack *p = top;
        post_expr[k] = top->operand; k++;
        top = top->next;
        free(p);
    }
    post_expr[k] = '\0';
    return post_expr;
}

void checkOperand(char* expression, int *i, char* op, int* no_error) {
    if (getPriority(*op) == -1 && *op != ' ') *no_error = 0;
            if (*op == '-' && ((*i == 0) || (*i >= 1 && expression[*i - 1] == '('))) {
                *op = '~';
            } else if (*op == 's') {
                ifSinOrSqrt(expression, i, op, no_error);
            } else if (*op == 'c') {
                ifCosOrCtg(expression, i, op, no_error);
            } else if (*op == 'l') {
                ifLn(expression, i, op, no_error);
            }
    
}

double calcY(char * post_expr, double x) {
    int size = strlen(post_expr), k = 0;
    double y = 0;
    char empty = ' ';
    struct stack* top = NULL;
    for (int i = 0; i < size; i++) {
        char sym = post_expr[i];
        if (isDigit(sym)) {
        char* num = malloc(size*sizeof(char));
           k = 0;
           top = push(empty, atof(getNumber(post_expr, num, &i, &k)), top);
           free(num);
        } else if (sym == 'x') {
            top = push(empty, x, top);
        } else if (getPriority(sym) != -1) {
            if (getPriority(sym) == 4) {
                double last = 0;
                top = getTopValue(top, &last);
                top = push(empty, getResult(sym, last), top); 
            } else {
            double second = 0, first = 0;
            top = getTopValue(top, &second);
            top = getTopValue(top, &first);
            top = push(empty, getBinResult(sym, first, second), top);
            }
        }
    }
   if (top != NULL) y = top->value;
    return y;
}

struct stack* getTopValue(struct stack* top, double* last) {
    if (stackCount(top) > 0) {
        *last = top->value;
        top = pop(top);
    }
    return top;
}

double getBinResult(char operand, double a, double b) {
    double res = 0;
    switch(operand) {
       case '+': res = a + b; break;
       case '-': res = a - b;  break;
       case '*': res = a * b; break;
       case '/': res = a / b; break;
       case '^':res = pow(a, b); break;
       default: break;
   }
    return res;
}

double getResult(char operand, double a) {
    double res = 0;
    switch(operand) {
       case 's': res = sin(a); break;
       case 'c': res = cos(a); break;
       case 't': res = tan(a); break;
       case 'g': res = cos(a)/sin(a); break;
       case 'q': res = sqrt(a); break;
       case 'l': res = log(a); break;
       case '~': res = -1 * a; break;
       default: break;
   }
    return res;
}

void fillY(double y_arr[SIZE_Y]) {
    double value = 1.2;
    for (int i = 0; i < SIZE_Y; i++) {
        y_arr[i] = value;
        value -= Y_STEP;
    }
}

void fillX(double x_arr[SIZE_X]) {
    double value = 0;
    for (int i = 0; i < SIZE_X; i++) {
        x_arr[i] = value;
        value += X_STEP;
    }
}

void calcFunc(char* post_expr, double y_arr[SIZE_Y], double x_arr[SIZE_X], int i_arr[SIZE_X], int j_arr[SIZE_X]) {
    double dif = 10; 
    int i_ = -1;
    for (int j = 0; j < WIDTH; j++) {
        i_ = -1;
        double y = calcY(post_expr, x_arr[j]);
        if (y <= MAX_DEFINITION_Y && y >= MIN_DEFINITION_Y) {
        dif = 10;
        for (int i = 0; i < HEIGHT; i++) {
            double d = fabs(y_arr[i] - y);
            if (dif > d && d < 1) {
                dif = d;
                i_ = i;
            }
        }
        }
        i_arr[j] = i_;
        j_arr[j] = j;
    }
}

void drawFunc(int i_arr[SIZE_X], int j_arr[SIZE_X]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i_arr[j] == i && j_arr[j] == j) {
                printf("%c", GRAPH);
            } else {
                printf("%c", SPACE);
            }
        }
        if (i != HEIGHT - 1) printf("\n");
    }
}

int stackCount(struct stack* top) {
    int count = 0;
    if (top != NULL) {
        top = top->next;
        count++;
    }
    return count;
}

struct stack* init(char operand, double value) {
    struct stack *tmp = (struct stack*) malloc(sizeof(struct stack));
    tmp->operand = operand;
    tmp->value = value;
    tmp->next = NULL;
    return tmp;
}

struct stack* push(char operand, double value, struct stack* top) {
    if (top == NULL) {
        top = init(operand, value);
    } else {
    struct stack *tmp = malloc(sizeof(struct stack));
    tmp->operand = operand;
    tmp->value = value;
    tmp->next = top;
    top = tmp;
    }
    return top;
}

struct stack* pop(struct stack* top) {
    if (top != NULL) {
        struct stack *tmp = top;
        top = top->next;
        free(tmp);
    }
    return top;
}

void destroy(struct stack* top) {
    while (top != NULL) {
        struct stack *p = top;
        top = top->next;
        free(p);
    }
}