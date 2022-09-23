#include "graph.h"

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

void ifLn(char* expression, int* i, int* no_error) {
    int size = strlen(expression);
    if (*i + 1 < size && expression[*i + 1] == 'n') {
        *i += 1;
    } else {
         *no_error = 0;
    }
}

char* getNumber(char* expression, char * num, int* i) {
    int j = *i, k = 0;
        for (j = *i; j < (int)strlen(expression); j++) {
            if (isDigit(expression[j]) || expression[j] == '.') {
                num[k] = expression[j];
                k++;
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
                ifLn(expression, i, no_error);
            }
    
}

double calcY(char * post_expr, double x) {
    int size = strlen(post_expr);
    double y = 0;
    char empty = ' ';
    struct stack* top = NULL;
    for (int i = 0; i < size; i++) {
        char sym = post_expr[i];
        if (isDigit(sym)) {
        char* num = malloc(size*sizeof(char));
           top = push(empty, atof(getNumber(post_expr, num, &i)), top);
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


double getBinResult(char operand, double a, double b) {
    double res = 0;
    switch(operand) {
       case '+': res = a + b; break;
       case '-': res = a - b;  break;
       case '*': res = a * b; break;
       case '/': res = a / b; break;
       case '^': res = pow(a, b); break;
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


