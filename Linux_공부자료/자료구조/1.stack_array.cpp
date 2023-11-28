#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100

typedef int element;      // int를 스택 element의 자료형으로 정의
element stack[STACK_SIZE];
int top = -1;                // 스택의 top의 초기값을-1로 설정

void push(element item)    // 스택의 삽입 연산
{
	if (top >= STACK_SIZE - 1) {    // 스택이 이미 Full인 경우
		printf("\n\n Stack is FULL ! \n");
		return;
	}
	else stack[++top] = item;
}

element pop()   // 스택의 삭제 후 반환 연산
{
	if (top == -1) {   // 현재 스택이 공백인 경우
		printf("\n\n Stack is Empty!!\n");
		return 0;
	}
	else return stack[top--];
}
void del()      // 스택의 삭제 연산
{
	if (top == -1) {     // 현재 스택이 공백인 경우
		printf("\n\n Stack is Empty !\n");
		exit(1);
	}
	else top--;
}
element peek()         // 스택의 top 원소 검색 연산
{
	if (top == -1) {     // 현재 스택이 공백인 경우
		printf("\n\n Stack is Empty !\n");
		exit(1);
	}
	else return stack[top];
}
void printStack()        // 스택 내용 출력 연산
{
	int i;
	printf("\n STACK [ ");
	for (i = 0; i <= top; i++)
		printf("%d ", stack[i]);
	printf("] ");
}
void main(void)
{
	int item;
	printStack(); 	push(1);
	printStack();	push(2);
	printStack();	push(3);
	printStack();
	item = peek();
	printStack();
	printf("peek top => %d", item);

	del();
	printStack();

	item = pop();
	printStack();
	printf("\t pop top => %d", item);

	item = pop();
	printStack();
	printf("\t pop top => %d", item);

	pop();
}
