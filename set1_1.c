#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

struct Stack {
    int top;
    char items[MAX];
};

void push(struct Stack *s, char c) {
    if (s->top < MAX - 1) {
        s->items[++(s->top)] = c;
    }
}

char pop(struct Stack *s) {
    if (s->top != -1) {
        return s->items[(s->top)--];
    }
    return '\0';
}

char peek(struct Stack *s) {
    if (s->top != -1) {
        return s->items[s->top];
    }
    return '\0';
}

int precedence(char op) {
    if (op == '/' || op == '*') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void infixToPostfix(char infix[], char postfix[]) {
    struct Stack s;
    s.top = -1;
    int k = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (ch == ' ' || ch == '\t') continue;

        if (isalnum(ch)) {
            postfix[k++] = ch;
        }
        else if (ch == '(') {
            push(&s, ch);
        }
        else if (ch == ')') {
            while (s.top != -1 && peek(&s) != '(') {
                postfix[k++] = pop(&s);
            }
            pop(&s);
        }
        else {
            while (s.top != -1 && precedence(peek(&s)) >= precedence(ch)) {
                postfix[k++] = pop(&s);
            }
            push(&s, ch);
        }
    }

    while (s.top != -1) {
        postfix[k++] = pop(&s);
    }
    postfix[k] = '\0';
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter Infix Expression: ");
    fgets(infix, sizeof(infix), stdin);
    infix[strcspn(infix, "\n")] = '\0';

    infixToPostfix(infix, postfix);

    printf("Postfix Expression: %s\n", postfix);

    return 0;
}