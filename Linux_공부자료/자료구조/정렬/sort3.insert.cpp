#include <stdio.h>

void insertionSort(int a[], int size)
{
	int i, j, t, temp;
	printf("\n정렬할 원소 : ");
	for (t = 0; t<size; t++)  printf("%d ", a[t]);
	printf("\n\n<<<<<<<<<< 삽입 정렬 수행 >>>>>>>>>>\n");
	for (i = 1; i<size; i++) {
		temp = a[i];
		j = i;
		while ((j>0) && (a[j - 1]>temp)) {
			a[j] = a[j - 1];
			j = j - 1;

		}
		a[j] = temp;
		printf("\n %d 단계 : ", i);
		for (t = 0; t<size; t++) printf("%3d ", a[t]);
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

	insertionSort(iArray, 10);

	printf("\n\n정렬 후 배열 값 :");
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", iArray[i]);
	}
	printf("\n");
	return 0;
}