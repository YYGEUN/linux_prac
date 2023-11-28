#include <stdio.h>
#include <math.h>

int size, i = 0;

int partition(int a[], int begin, int end)  // 부분집합 안에서 피봇의 위치를 찾아 확정하는 연산
{
	int pivot, temp, L, R, t;
	L = begin;
	R = end;
	pivot = (int)floor((begin + end) / 2);  // 중간에 위치한 자료를 피봇 원소로 선택
	printf("\n [ %d단계 : pivot=%d] \n", ++i, a[pivot]);
	while (L<R) {
		while ((a[L]<a[pivot]) && (L<R)) L++;
		while ((a[R] >= a[pivot]) && (L<R)) R--;
 		temp = a[L];
		a[L] = a[R];
		a[R] = temp;
		if (L == pivot) {
			// L과 R 원소를 교환하여, 결과적으로 피봇 원소의 위치가 변경된 경우
			printf("done\n");
			for (t = 0; t<size; t++) printf(" %d", a[t]);  //현재의 정렬 상태 출력
			printf("\n");
			return R; // R은 자리 교환하여 확정된 피봇의 위치!
		}
		printf("calc\n");
		for (t = 0; t < size; t++) printf(" %d", a[t]);  // 현재의 정렬 상태 출력	
		printf("\n");
	} //while(L<R)
	  // (L=R)이 된 경우
	temp = a[pivot];
	a[pivot] = a[R];
	a[R] = temp;
	printf("L=R\n");
	for (t = 0; t<size; t++) printf(" %d", a[t]);  // 현재의 정렬 상태 출력	
	printf("\n");
	return R;
}

void quickSort(int a[], int begin, int end)
{
	if (begin<end) {
		int p;
		p = partition(a, begin, end);
		quickSort(a, begin, p - 1); // 피봇의 왼쪽 부분집합에 대해 퀵 정렬 재귀호출
		quickSort(a, p + 1, end); // 피봇의 오른쪽 부분집합에 대해 퀵 정렬 재귀호출
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

	quickSort(iArray, 0, size - 1);

	printf("\n\n정렬 후 배열 값 :");
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", iArray[i]);
	}
	printf("\n");
	return 0;
}