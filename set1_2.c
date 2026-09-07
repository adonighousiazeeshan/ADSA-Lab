#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 500

// Stack for Operators (char)
struct CharStack {
    int top;
    char items[MAX];
};

void pushChar(struct CharStack *s, char c) {
    s->items[++(s->top)] = c;
}

char popChar(struct CharStack *s) {
    return s->items[(s->top)--];
}

char peekChar(struct CharStack *s) {
    return (s->top != -1) ? s->items[s->top] : '\0';
}

// Stack for Values (int)
struct IntStack {
    int top;
    int items[MAX];
};

void pushInt(struct IntStack *s, int val) {
    s->items[++(s->top)] = val;
}

int popInt(struct IntStack *s) {
    return s->items[(s->top)--];
}

int precedence(char op) {
    if (op == '/' || op == '*') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// Evaluates the Infix Expression passed as a string
int evaluateInfix(char *expr) {
    struct CharStack ops;
    struct IntStack vals;
    ops.top = -1;
    vals.top = -1;

    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == ' ' || expr[i] == '\t') continue;

        // If the token is a number (handles multi-digit integers like 23 or 28)
        if (isdigit(expr[i])) {
            int val = 0;
            while (i < strlen(expr) && isdigit(expr[i])) {
                val = (val * 10) + (expr[i] - '0');
                i++;
            }
            i--; // Step back to compensate for loop increment
            pushInt(&vals, val);
        }
        else if (expr[i] == '(') {
            pushChar(&ops, expr[i]);
        }
        else if (expr[i] == ')') {
            while (ops.top != -1 && peekChar(&ops) != '(') {
                int val2 = popInt(&vals);
                int val1 = popInt(&vals);
                char op = popChar(&ops);

                if (op == '+') pushInt(&vals, val1 + val2);
                else if (op == '-') pushInt(&vals, val1 - val2);
                else if (op == '*') pushInt(&vals, val1 * val2);
                else if (op == '/') pushInt(&vals, val1 / val2);
            }
            if (ops.top != -1) popChar(&ops); // Remove '('
        }
        else { // Operator
            while (ops.top != -1 && precedence(peekChar(&ops)) >= precedence(expr[i])) {
                int val2 = popInt(&vals);
                int val1 = popInt(&vals);
                char op = popChar(&ops);

                if (op == '+') pushInt(&vals, val1 + val2);
                else if (op == '-') pushInt(&vals, val1 - val2);
                else if (op == '*') pushInt(&vals, val1 * val2);
                else if (op == '/') pushInt(&vals, val1 / val2);
            }
            pushChar(&ops, expr[i]);
        }
    }

    // Apply remaining operators
    while (ops.top != -1) {
        int val2 = popInt(&vals);
        int val1 = popInt(&vals);
        char op = popChar(&ops);

        if (op == '+') pushInt(&vals, val1 + val2);
        else if (op == '-') pushInt(&vals, val1 - val2);
        else if (op == '*') pushInt(&vals, val1 * val2);
        else if (op == '/') pushInt(&vals, val1 / val2);
    }

    return popInt(&vals);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s \"<expression>\"\n", argv[0]);
        return 1;
    }

    // Concatenate command-line arguments into a single string
    char expression[MAX] = "";
    for (int i = 1; i < argc; i++) {
        strcat(expression, argv[i]);
        strcat(expression, " ");
    }

    int result = evaluateInfix(expression);
    printf("%d\n", result);

    return 0;
}