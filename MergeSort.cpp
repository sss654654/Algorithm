#include <iostream>
using namespace std;

// Stable sort
// 우선 순위가 같은 원소들끼리는 정렬 후에도 원래의 순서를 따라가도록 하는 정렬
// Merge sort는 Stable sort
// 추가적으로 필요한 공간(Overhead) : O(N)
// 시간 복잡도 : O(NlgN)

int n = 10;
int arr[1000001] = { 15, 25, 22, 357, 16, 23, -53, 12, 46, 3 };
int tmp[1000001]; // merge 함수에서 리스트 2개를 합친 결과를 임시로 저장하고 있을 변수

// mid = (st+en)/2라고 할 때 arr[st:mid], arr[mid:en]은 이미 정렬이 되어있는 상태일 때 arr[st:mid]와 arr[mid:en]을 합친다.
void merge(int st, int en) {
	int mid = (st + en) / 2;
	int Lidx = st; // 왼쪽 배열 arr[Lidx:Ridx]
	int Ridx = mid; // 오른쪽 배열 arr[Ridx:en]
	for (int i = st; i < en; i++) {
		if (Lidx == mid) tmp[i] = arr[Ridx++]; // 왼쪽 배열이 tmp배열에 다 담김
		else if (Ridx = en) tmp[i] = arr[Lidx++]; // 오른쪽 배열이 tmp배열에 다 담김
		else if (arr[Lidx] <= arr[Ridx]) tmp[i] = arr[Lidx++];
		else tmp[i] = arr[Ridx++];
	}
	// 왼쪽배열, 오른쪽배열 정렬 완료

	for (int i = st; i < en; i++) arr[i] = tmp[i];
}

// arr[st:en]을 정렬하고 싶다.
void merge_sort(int st, int en) {
	if (en == st+1) return; // 길이 1인 경우
	int mid = (st + en) / 2;
	merge_sort(st, mid); // arr[st:mid]을 정렬한다.
	merge_sort(mid, en); // arr[mid:en]을 정렬한다.
	merge(st, en); // arr[st:mid]와 arr[mid:en]을 합친다.
}

int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0);
	merge_sort(0, n);
	for (int i = 0; i < n; i++) cout << arr[i] << ' ';  // -53 3 12 15 16 22 23 25 46 357
}