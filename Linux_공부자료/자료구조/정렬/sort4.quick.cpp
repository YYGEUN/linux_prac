#include <stdio.h>
#include <math.h>

int size, i = 0;

int partition(int a[], int begin, int end)  // �κ����� �ȿ��� �Ǻ��� ��ġ�� ã�� Ȯ���ϴ� ����
{
	int pivot, temp, L, R, t;
	L = begin;
	R = end;
	pivot = (int)floor((begin + end) / 2);  // �߰��� ��ġ�� �ڷḦ �Ǻ� ���ҷ� ����
	printf("\n [ %d�ܰ� : pivot=%d] \n", ++i, a[pivot]);
	while (L<R) {
		while ((a[L]<a[pivot]) && (L<R)) L++;
		while ((a[R] >= a[pivot]) && (L<R)) R--;
 		temp = a[L];
		a[L] = a[R];
		a[R] = temp;
		if (L == pivot) {
			// L�� R ���Ҹ� ��ȯ�Ͽ�, ��������� �Ǻ� ������ ��ġ�� ����� ���
			printf("done\n");
			for (t = 0; t<size; t++) printf(" %d", a[t]);  //������ ���� ���� ���
			printf("\n");
			return R; // R�� �ڸ� ��ȯ�Ͽ� Ȯ���� �Ǻ��� ��ġ!
		}
		printf("calc\n");
		for (t = 0; t < size; t++) printf(" %d", a[t]);  // ������ ���� ���� ���	
		printf("\n");
	} //while(L<R)
	  // (L=R)�� �� ���
	temp = a[pivot];
	a[pivot] = a[R];
	a[R] = temp;
	printf("L=R\n");
	for (t = 0; t<size; t++) printf(" %d", a[t]);  // ������ ���� ���� ���	
	printf("\n");
	return R;
}

void quickSort(int a[], int begin, int end)
{
	if (begin<end) {
		int p;
		p = partition(a, begin, end);
		quickSort(a, begin, p - 1); // �Ǻ��� ���� �κ����տ� ���� �� ���� ���ȣ��
		quickSort(a, p + 1, end); // �Ǻ��� ������ �κ����տ� ���� �� ���� ���ȣ��
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

	quickSort(iArray, 0, size - 1);

	printf("\n\n���� �� �迭 �� :");
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", iArray[i]);
	}
	printf("\n");
	return 0;
}