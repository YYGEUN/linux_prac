#include <stdio.h>
#include <stdlib.h>
typedef int element;        //int를 스택 element의 자료형으로 정의

typedef struct  stackNode {  //스택의 노드 구조 정의
	element data;
	struct stackNode* link;
}stackNode;

stackNode* top;     //스택의 top 노드를 지정하기 위한 포인터 top 선언

void push(element item) //스택의 삽입 연산
{
	stackNode* temp = (stackNode*)malloc(sizeof(stackNode));
	temp->data = item;
	temp->link = top;
	top = temp;
}

element pop()      //스택의 삭제 후 반환 연산
{
	element item;
	stackNode* temp = top;

	if (top == NULL) {   //현재 스택이 공백 리스트인 경우
		printf("\n\n Stack is empty !\n");
		return 0;
	}
	else {               //현재 스택이 공백 리스트가 아닌 경우
		item = temp->data;
		top = temp->link;
		free(temp);
		return item;
	}
}

void del()              //스택의 삭제 연산
{
	stackNode* temp;
	if (top == NULL) {    //현재 스택이 공백 리스트인 경우
		printf("\n\n Stack is empty !\n");
	}
	else {              //현재 스택이 공백 리스트가 아닌 경우
		temp = top;
		top = top->link;
		free(temp);
	}
}

// 빠진 peek
element peek()              //연결리스트 스택의 top 원소 검색 연산
{
	element item;
	if (top == NULL) {
		printf("\n\n Stack is empty !\n");
		return 0;
	}
	else {
		item = top->data;
		return item;
	}
}

void printStack()        //스택의 내용 출력 연산
{
	stackNode* p = top;
	printf("\n STACK [ ");
	while (p) {
		printf("%d ", p->data);
		p = p->link;
	}
	printf("] ");
}

void main(void)
{
	element item;
	top = NULL;
	printStack();
	push(1);
	printStack();
	push(2);
	printStack();
	push(3);
	printStack();

	item = peek();
	printStack();
	printf("link peek top => %d", item);

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
