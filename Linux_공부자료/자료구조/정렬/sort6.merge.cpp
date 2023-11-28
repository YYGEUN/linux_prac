#include <stdio.h>

int size, i = 0;

#define MAX 30
int sorted[MAX];

void merge(int a[], int m, int middle, int n)
{
	int i, j, k, t;
	i = m; 		// 첫 번째 부분집합의 시작 위치 설정
	j = middle + 1; 	// 두 번째 부분집합의 시작 위치 설정
	k = m; 		// 배열 sorted에 정렬된 원소를 저장할 위치 설정
	printf("\n m %d middle %d n %d \n ", m, middle, n);

	while (i <= middle && j <= n) {
		if (a[i] <= a[j]) {
			sorted[k] = a[i];
			i++;
		}
		else {
			sorted[k] = a[j];
			j++;
		}
		k++;
	}
	if (i>middle) for (t = j; t <= n; t++, k++) sorted[k] = a[t];
	else for (t = i; t <= middle; t++, k++) sorted[k] = a[t];
	for (t = m; t <= n; t++) a[t] = sorted[t];
	printf("\n 병합 정렬 >> ");
	for (t = 0; t<size; t++) printf("%4d ", a[t]);
}

void mergeSort(int a[], int m, int n)
{
	int middle;
	if (m<n) {
		middle = (m + n) / 2;
		mergeSort(a, m, middle); 	// 앞 부분에 대한 분할 작업 수행
		mergeSort(a, middle + 1, n); 	// 뒷 부분에 대한 분할 작업 수행
		merge(a, m, middle, n); 	// 부분집합에 대하여 정렬과 병합 작업 수행
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
	mergeSort(iArray, 0, size - 1);

	printf("\n\n정렬 후 배열 값 :");
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", iArray[i]);
	}
	printf("\n");
	return 0;
}