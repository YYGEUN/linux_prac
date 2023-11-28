#include <stdio.h>

int size, i = 0;

#define MAX 30
int sorted[MAX];

void merge(int a[], int m, int middle, int n)
{
	int i, j, k, t;
	i = m; 		// ù ��° �κ������� ���� ��ġ ����
	j = middle + 1; 	// �� ��° �κ������� ���� ��ġ ����
	k = m; 		// �迭 sorted�� ���ĵ� ���Ҹ� ������ ��ġ ����
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
	printf("\n ���� ���� >> ");
	for (t = 0; t<size; t++) printf("%4d ", a[t]);
}

void mergeSort(int a[], int m, int n)
{
	int middle;
	if (m<n) {
		middle = (m + n) / 2;
		mergeSort(a, m, middle); 	// �� �κп� ���� ���� �۾� ����
		mergeSort(a, middle + 1, n); 	// �� �κп� ���� ���� �۾� ����
		merge(a, m, middle, n); 	// �κ����տ� ���Ͽ� ���İ� ���� �۾� ����
	}
}

int main()
{
	int iArray[10] = { 69, 10, 30, 2, 16, 8, 31, 22, 100, 50 };

	printf("�迭 �� :");
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", iArray[i]);
	}
	printf("\n");

	// ����
	printf("���� �۾� ����\n");
	size = 10;
	mergeSort(iArray, 0, size - 1);

	printf("\n\n���� �� �迭 �� :");
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", iArray[i]);
	}
	printf("\n");
	return 0;
}