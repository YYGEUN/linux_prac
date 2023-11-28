#include <stdio.h>

void SelectionSort(int a[], int size) 	// 선택 정렬 연산
{
	int i, j, t, min, temp;
	printf("\n정렬할 원소 : ");
	for (t = 0; t<size; t++) printf("%d ", a[t]); 	// 정렬 전의 원소 출력
	printf("\n\n<<<<<<<<<< 선택 정렬 수행 >>>>>>>>>>\n");
	for (i = 0; i<size - 1; i++) {
		min = i;
		for (j = i + 1; j<size; j++) {
			if (a[j]<a[min]) min = j;
		}
		temp = a[i];
		a[i] = a[min];
		a[min] = temp;
		printf("\n%d 단계 : ", i + 1);
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
	SelectionSort(iArray, 10);

	printf("\n\n정렬 후 배열 값 :");
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", iArray[i]);
	}
	printf("\n");
	return 0;
}

//#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
//SWAP(list[i], list[least], temp);

