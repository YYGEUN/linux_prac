#include <stdio.h>

void sequentialSearch1(int a[], int n, int key)
{
	int i = 0;
	printf("\n %d�� �˻� ->> ", key);
	while (i<n && a[i] != key)   i++;
	if (i<n) printf("%d��°�� �˻� ����! \n\n", i + 1);
	else printf("%d��°�� �˻� ����! \n\n", i + 1);
}

void sequentialSearch2(int a[], int n, int key)
{
	int i = 0;
	printf("\n %d�� �˻� ->> ", key);
	while (a[i] < key)  i++;
	if (a[i] == key) printf("%d��°�� �˻� ����!\n\n", i + 1);
	else printf("%d��°�� �˻� ����! \n\n", i + 1);
}

void main()
{
	int array[] = { 69, 10, 30, 2, 16, 8, 31, 22, 100, 50 };
	int n = 10;

	sequentialSearch1(array, n, 16);
	sequentialSearch1(array, n, 100);

	sequentialSearch2(array, n, 16);
	sequentialSearch2(array, n, 50);
}