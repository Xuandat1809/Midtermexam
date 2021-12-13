#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_STACK 100

int stack[MAX_STACK];
int top = 0;

int isEmpty(){
    if (top == 0) {
        return 1;
    }else {
        return 0;
    }
}

int isFull(){
    if (top == MAX_STACK) {
        return 1;
    }else {
        return 0;
    }
}

void push(int v){
    if (isFull() == 0){
        stack[top] = v;
        top++;
    }else {
        printf("Stack is full!");
    }
}

int pop(){
    if (isEmpty() ==1){
        printf("Stack is empty!");
        exit(EXIT_FAILURE);
    }else {
        top--;
        return stack[top];
    }
}

int peek(){
    if (isEmpty() == 0){
        return stack[top - 1];
    }
    exit(EXIT_FAILURE);
}

int getSize(){
    return top;
}

void makeEmpty(){
    top = 0;
}

int isDigit(char c){
    if (c >= '0' && c <= '9'){
        return 1;
    }
    return 0;
}

int getPriority(int c){
    if (c == '+' || c == '-'){
        return 1;
    }
    if (c == '*' || c == '/') {
        return 2;
    }
    return -1;
}

void rpn(char *input){
    int i, index = -1;
    for (i = 0; i < strlen(input); i++){
        if (isDigit(input[i]) == 1) {
            index++;
            input[index] = input[i];
        }else {
            while (isEmpty() == 0 && getPriority(input[i]) <= getPriority(peek())){
                index++;
                input[index] = pop();
            }
            push(input[i]);
        }
    }
    while (isEmpty() == 0){
        index++;
        input[index] = pop();
    }
    input[++index] = '\0';
}

int calc(char *rpn){
    int i;
    for (i = 0; i < strlen(rpn); i++){
        // nếu là số hạng
        if (isDigit(rpn[i]) == 1){
            push(rpn[i] - '0'); // chuyển ký tự sang số
        }else {
            int v1 = pop();
            int v2 = pop();
            switch (rpn[i])
            {
            case '+':
                push(v2 + v1);
                break;
            case '-':
                push(v2 - v1);
                break;
            case '*':
                push(v1 * v2);
                break;
            case '/':
                if (v2 == 0){
                    exit(EXIT_FAILURE);
                }
                push(v2 / v1); // giả sử luôn chia ra số nguyên?
                break;
            }
        }
    }
    return peek();
}

int main(){
    int i;
    char fomular[100];
    printf("Nhap bieu thuc: ");
    scanf("%s", &fomular);
    rpn(fomular);
    for (i = 0; i < strlen(fomular); i++){
        printf("%c ", fomular[i]);
    }
    makeEmpty(); // xóa toàn bộ stack
    int result = calc(fomular);
    printf("\nResult = %d\n", result);
}