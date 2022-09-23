
#include "stack.h"
#include "graph.h"

void process();

int main()
{
    process();
    return 0;
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
