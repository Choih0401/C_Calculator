#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int stack[MAX];
int top;

int calc(char *a);
int push(int a);
void init();
int pop();
void print();
int stack_top();
int stack_empty();
int oper(int a);
void postfix(char *a, char *b);
int legal(char *a);

int main() {

	int a;
	char arr[256] = { 0, };
	scanf("%s", arr);
	char arr2[256];
	postfix(arr2, arr);
	if (!legal(arr2)) {
		printf("Error!\n");
		exit(1);
	}
	a = calc(arr2);
	printf("Answer : %d\n", a);

	system("pause");
}

void init() {
	top = -1;
}

int push(int a) {

	if (top >= MAX - 1) {
		printf("\n    Stack overflow.");
		return -1;
	}

	stack[++top] = a;
	return a;
}

int pop() {
	if (top < 0) {
		printf("\n   Stack underflow.");
		return -1;
	}
	return stack[top--];
}

void print() {
	int i;
	printf("\n Stack contents : TOP ----> Bottom\n");
	for (i = top; i >= 0; i--) {
		printf("%-6d", stack[i]);
	}
}

int stack_top() {
	return (top < 0) ? -1 : stack[top];
}

int stack_empty() {
	return (top < 0);
}

int oper(int a) {
	return (a == '+' || a == '-' || a == '*' || a == '/');
}

int legal(char *a) {
	int i = 0;
	while (*a) {
		while (*a == ' ') {
			a++;
		}

		if (oper(*a)) {
			i--;
		}
		else {
			i++;
			while (*a != ' ') {
				a++;
			}
		}
		if (i < 1) break;
		a++;
	}
	return (i == 1);
}

int perce(int a) {
	if (a == '(') return 0;
	if (a == '+' || a == '-') return 1;
	if (a == '*' || a == '/') return 2;
	else return 3;
}

void postfix(char *a, char *b) {
	char c;
	init();
	while (*b) {
		if (*b == '(') {
			push(*b);
			b++;
		}
		else if (*b == ')') {
			while (stack_top() != '(') {
				*a++ = pop();
				*a++ = ' ';
			}
			pop();
			b++;
		}
		else if (oper(*b)) {
			while (!stack_empty() &&
				perce(stack_top()) >= perce(*b)) {
				*a++ = pop();
				*a++ = ' ';
			}
			push(*b);
			b++;
		}
		else if (*b >= '0' && *b <= '9') {
			do {
				*a++ = *b++;
			} while (*b >= '0' && *b <= '9');
			*a++ = ' ';
		}
		else {
			b++;
		}
	}

	while (!stack_empty()) {
		*a++ = pop();
		*a++ = ' ';
	}
	a--;
	*a = 0;
}

int calc(char *a) {
	int i;
	init();
	while (*a) {
		if (*a >= '0' && *a <= '9') {
			i = 0;
			do {
				i = i * 10 + *a - '0';
				a++;
			} while (*a >= '0' && *a <= '9');
			push(i);
		}
		else if (*a == '+') {
			push(pop() + pop());
			a++;
		}
		else if (*a == '*') {
			push(pop() * pop());
			a++;
		}
		else if (*a == '-') {
			i = pop();
			push(pop() - i);
			a++;
		}
		else if (*a == '/') {
			i = pop();
			push(pop() / i);
			a++;
		}
		else {
			a++;
		}
	}
	return pop();
}