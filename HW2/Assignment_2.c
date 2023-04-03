#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#pragma warning(disable:4996)
int all,num;
char d[MAX];

typedef struct _node {
	char* data;
	struct _node* link;
}Node;

typedef struct _stack {
	int count;
	Node* top;
}Stack;

Stack* create() {
	Stack* stack = malloc(sizeof(Stack));
	stack->count = 0;
	stack->top = 0;
	return stack;
}

int Empty(Stack* stack) {
	return stack->count==0;
}

int Full(Stack* stack) {
	return stack->count == MAX;
}

/*void print(Stack* stack) {
	Node* node = stack->top;
	while (node != NULL) {
		printf("%c", node->data);
		node = node->link;
	}
}*/

void destroy(Stack* stack) {
	Node* node = stack->top;
	while (node != NULL) {
		node->data = NULL;
		node = node->link;
	}
	stack->count = 0;
}

void push(Stack* stack, char* data) {
	if (Full(stack)) return;

	Node* newNode = malloc(sizeof(Node));
	newNode->data = data;
	newNode->link = NULL;

	if (!Empty(stack)) {
		newNode->link = stack->top;
	}
	stack->top = newNode;
	stack->count++;
}

Node* pop(Stack* stack) {
	Node* topNode = stack->top;
	stack->top = stack->top->link;
	stack->count--;

	return topNode;
}

Node* top(Stack* stack) {
	return stack->top->data;
}

int priority(char a) {
	if (a == '-' || a == '+')
		return 1;
	else if (a == '/' || a == '*' )
		return 2;
	else
		return 0;
}

void function(char d[], int n, FILE* outFile) {
	Stack* stack = create();
	

	for (int i = 0; i < n; i++) {
		if (d[i] >= 'A' && d[i] <= 'Z') {
			fprintf(outFile, "%c", d[i]);
		}
		else {
			if (d[i] == '('||Empty(stack)) {
				push(stack, d[i]);
			}
			else if (d[i] == ')') {
				do{
					fprintf(outFile, "%c", top(stack));
					pop(stack);
				} while (top(stack)!='(');
				pop(stack);
			}
			else {
				while (!Empty(stack)&&priority(top(stack)) >= priority(d[i])) {
					fprintf(outFile, "%c", top(stack));
					pop(stack);
				}
				push(stack, d[i]);
			}
		}
	}
	while (!Empty(stack)) {
		fprintf(outFile, "%c", top(stack));
		pop(stack);
	}
	fprintf(outFile,"\n");
	
}

int main() {
	FILE* outFile = fopen("output.txt ", "w");
	freopen("C:\\Users\\Dell\\Downloads\\hw2_input.txt", "r", stdin);
	scanf("%d\n", &all);
	printf("The total number: %d \n", all);

	for (int i = 0; i < all; i++) {
		scanf("%d\n", &num);
		for (int n = 0; n < num; n++) {
			scanf("%c", &d[n]);
		}
		function(&d, num, outFile);	
	}
	fclose(outFile);
	return 0;
}