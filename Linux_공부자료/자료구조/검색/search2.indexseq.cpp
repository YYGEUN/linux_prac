#include <stdio.h>

#define INDEX_SIZE 3

typedef struct {
	int index;
	int key;
} itable;
itable indexTable[INDEX_SIZE];

void sequentialSearch2(int a[], int begin, int end, int key)
{
	int i = begin;

	printf("\n %d�� �˻�! ->> ", key);
	while (i<end && a[i]<key) i++;

	if (a[i] == key) printf("%d��°�� �˻� ����!\n\n", (i - begin) + 1);
	else printf("%d��°�� �˻� ����! \n\n", (i - begin) + 1);
}

void makeIndexTable(int a[], int size)
{
	int i, n;
	n = size / INDEX_SIZE;
	if (size%INDEX_SIZE > 0)  n = n + 1;
	for (i = 0; i<INDEX_SIZE; i++) {
		indexTable[i].index = i*n;
		indexTable[i].key = a[i*n];
	}
}

void indexSearch(int a[], int n, int key)
{
	int i, begin, end;
	if (key < a[0] || key > a[n - 1])
		printf("\nã�� Ű�� �����ϴ�. �˻� ����! \n");
	for (i = 0; i<INDEX_SIZE; i++)
		if ((indexTable[i].key <= key) && (indexTable[i + 1].key > key)) {
			begin = indexTable[i].index;
			end = indexTable[i + 1].index;
			break;
		}

	if (i == INDEX_SIZE) {
		begin = indexTable[i - 1].index;
		end = n;
	}

	sequentialSearch2(a, begin, end, key);
}

void main()
{
	int array[] = { 2, 8, 10, 16, 22, 30, 31, 50, 69, 100 };
	int n = 10;

	printf("\n\t<< ���� ���� �˻� >>\n");
	makeIndexTable(array, n);
	indexSearch(array, n, 16);
	indexSearch(array, n, 22);
}