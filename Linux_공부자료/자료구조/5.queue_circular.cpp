#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define cQ_SIZE  4

typedef char element;     //char형을 큐 element의 자료형으로 정의
typedef struct {
	element queue[cQ_SIZE];   // 1차원 배열 큐 선언
	int front, rear;
} cQueueType;

cQueueType* createQueue()
{
	cQueueType* cQ;
	cQ = (cQueueType*)malloc(sizeof(cQueueType));
	cQ->front = 0;       //원형 큐의 front 초깃값 설정
	cQ->rear = 0;        //원형 큐의 reart 초깃값 설정
	return cQ;
}
int isEmpty(cQueueType* cQ)   //원형 큐가 공백인지 확인하는 연산
{
	if (cQ->front == cQ->rear) {
		printf("\n Circular Queue is empty! \n");
		return 1;
	}
	else return 0;
}
int isFull(cQueueType* cQ)       //원형 큐가 포화상태인지 확인하는 연산
{
	if (((cQ->rear + 1) % cQ_SIZE) == cQ->front) {
		printf("  Circular Queue is full! \n");
		return 1;
	}
	else return 0;
}

void enQueue(cQueueType* cQ, element item) //원형 큐의 rear에 원소를 삽입하는 연산
{
	if (isFull(cQ))
	{
		getchar();
		exit(1);
	}
	else {
		cQ->rear = (cQ->rear + 1) % cQ_SIZE;
		cQ->queue[cQ->rear] = item;
	}
}
element deQueue(cQueueType* cQ) //원형 큐 front에서 원소 삭제 반환연산
{
	if (isEmpty(cQ)) exit(1);
	else {
		cQ->front = (cQ->front + 1) % cQ_SIZE;
		return cQ->queue[cQ->front];
	}
}

void del(cQueueType* cQ)       //원형 큐의 front에서 원소를 삭제하는 연산
{
	if (isEmpty(cQ)) exit(1);
	else cQ->front = (cQ->front + 1) % cQ_SIZE;

}

element peek(cQueueType* cQ) //원형 큐의 가장 앞에 있는 원소를 검색하여 반환하는 연산
{
	if (isEmpty(cQ)) exit(1);
	else return cQ->queue[(cQ->front + 1) % cQ_SIZE];
}

void printQ(cQueueType* cQ)     //원형 큐의 내용을 출력하는 연산
{
	int i, first, last;
	first = (cQ->front + 1) % cQ_SIZE;
	last = (cQ->rear + 1) % cQ_SIZE;
	printf(" Circular Queue : [");
	i = first;
	while (i != last) {
		printf("%3c", cQ->queue[i]);
		i = (i + 1) % cQ_SIZE;
	}
	printf(" ] \n");
}

void main(void) {
	cQueueType* cQ1 = createQueue();
	element data;
	printf("삽입 A>>");  enQueue(cQ1, 'A');   printQ(cQ1);
	printf("삽입 B>>");  enQueue(cQ1, 'B');   printQ(cQ1);
	printf("삭제  >>");  deQueue(cQ1);        printQ(cQ1);
	printf("삽입 C>>");  enQueue(cQ1, 'C');   printQ(cQ1);
	data = peek(cQ1);  printf(" peek item : %c \n", data);
	printf("삽입 D>>");  enQueue(cQ1, 'D');   printQ(cQ1);
	printf("삽입 E>>");  enQueue(cQ1, 'E');   printQ(cQ1);
}
