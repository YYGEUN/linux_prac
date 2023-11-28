#include <stdio.h>

int size, i = 0;
#define parent(x) (x-1)/2
void heap(int *data, int num) {
	for (int i = 1; i<num; i++) {
		int child = i;
		while (child > 0) {
			int root = parent(child);
			if (data[root] < data[child]) {
				int temp = data[root];
				data[root] = data[child];
				data[child] = temp;
			}
			child = root;
		}

		// 중간 출력 
		printf("중간 배열 %d: ", i);
		for (int j = 0; j < num; j++) {
			printf("%d ", data[j]);
		}
		printf("\n");
	}
}

int main()
{
	int num = 10;
	int data[] = { 69, 10, 30, 2, 16, 8, 31, 22, 100, 50 };
	//현재값 출력 
	printf("현재 배열: ");
	for (int i = 0; i<num; i++) {
		printf("%d ", data[i]);
	}
	printf("\n");

	heap(data, num); // 힙을 만든다. 

	for (int i = num - 1; i >= 0; i--) {
		// 가장큰 숫자(root)를 맨 마지막 원소와 스왑 
		int temp = data[i];
		data[i] = data[0];
		data[0] = temp;

		// 맨마지막원소(가장큰원소)를 제외하고 다시 힙을 만든다. 
		heap(data, i);
	}

	// 결과 출력 
	printf("결과 배열: ");
	for (int i = 0; i<num; i++) {
		printf("%d ", data[i]);
	}
	printf("\n");
	return 0;
}