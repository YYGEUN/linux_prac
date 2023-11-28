#include <stdio.h>
#include <math.h>

int size, i = 0;
void intervalSort(int a[], int begin, int end, int interval)
{
	int i, j, item;
	for (i = begin + interval; i <= end; i = i + interval) {
		item = a[i];
		for (j = i - interval; j >= begin && item<a[j]; j = j - interval)
			a[j + interval] = a[j];
		a[j + interval] = item;
	}
}

void shellSort(int a[], int size)
{
	int i, t, interval;
	printf("\n정렬할 원소 : ");
	for (t = 0; t<size; t++)  printf("%d ", a[t]);
	printf("\n\n<<<<<<<<<< 셸 정렬 수행 >>>>>>>>>>\n");
	interval = size / 2;
	while (interval >= 1) {
		for (i = 0; i<interval; i++)
			intervalSort(a, i, size - 1, interval);
		printf("\n interval=%d >> ", interval);
		for (t = 0; t<size; t++)  printf("%d ", a[t]);
		printf("\n");
		interval = interval / 2;
	}
}

int main()
{
	int iArray[10] = { 69, 10, 30, 2, 16, 8, 31, 22, 100, 50 };

	printf("배열 값 :");
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", iArray[i]);
	}
	printf("\n");

	// 정렬
	printf("정렬 작업 시작\n");
	size = 10;
	shellSort(iArray, size);

	printf("\n\n정렬 후 배열 값 :");
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", iArray[i]);
	}
	printf("\n");
	return 0;
}