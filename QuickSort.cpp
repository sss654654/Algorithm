#include <iostream>
#include <string.h>
using namespace std;

// 거의 모든 정렬 알고리즘보다 빠름
// 직접 quick을 구현해야 한다면 merge를 쓸 것
// 재귀적으로 구현되는 정렬
// 매 단계 마다 pivot을 제자리로 보냄 
// 퀵소트의 장점은 추가적인 공간이 필요하지 않은 정렬임(In-Place Sort)
// Quick sort는 Stable sort 아님
// 단계마다 O(lgN)
// 시간 복잡도 : O(NlgN)
// 추가적으로 필요한 공간(Overhead) : O(1)

// worst case
// 리스트가 오름차순이거나 내림차순일 경우
// 단계마다 O(N)
// 시간 복잡도 : O(N^2)
// -> pivot을 랜덤하게 택해서 처리, pivot후보를 3개 정해서 3개 중에서 중앙값을 pivot으로 둬서 처리
// O(NlgN)을 보장하기 위해서 일정 깊이 이상 들어가면 HeapSort로 정렬 함 이를 Introspective sort라고 부름
int arr[8] = {6, -8, 1, 12, 8, 3, 7, -7};

void quicksort(int st, int en) {
	if (en <= st + 1) return;
	int pivot = arr[st];
	int l = st + 1;
	int r = en - 1;
	while (1) {
		while (l <= r && arr[l] <= pivot) l++; // l은 pivot보다 큰 값이 나올 때 까지 오른쪽으로 이동
		while (l <= r && arr[r] > pivot) r--; // r은 pivot보다 작거나 같은 값이 나올 때 까지 왼쪽으로 이동
		if (l > r) break;
		swap(arr[l], arr[r]);
	}
	swap(arr[st], arr[r]);
	quicksort(st, r);
	quicksort(r + l, en);
}
int main() {
	quicksort(0, 8);
}