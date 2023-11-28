#include <stdio.h>

void SelectionSort(int a[], int size) 	// ���� ���� ����
{
	int i, j, t, min, temp;
	printf("\n������ ���� : ");
	for (t = 0; t<size; t++) printf("%d ", a[t]); 	// ���� ���� ���� ���
	printf("\n\n<<<<<<<<<< ���� ���� ���� >>>>>>>>>>\n");
	for (i = 0; i<size - 1; i++) {
		min = i;
		for (j = i + 1; j<size; j++) {
			if (a[j]<a[min]) min = j;
		}
		temp = a[i];
		a[i] = a[min];
		a[min] = temp;
		printf("\n%d �ܰ� : ", i + 1);
		for (t = 0; t<size; t++) printf("%3d ", a[t]);
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
	SelectionSort(iArray, 10);

	printf("\n\n���� �� �迭 �� :");
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", iArray[i]);
	}
	printf("\n");
	return 0;
}

//#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
//SWAP(list[i], list[least], temp);

