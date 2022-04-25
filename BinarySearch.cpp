#include <iostream>
#include <string.h>
using namespace std;

// 이분탐색
// 정렬되어 있는 배열에서 특정 데이터를 찾기 위해 데이터를 순차적으로 확인하는 대신
// 탐색 범위를 절반으로 줄여가며 찾는 탐색 방법
// 선형탐색 O(N) 이분탐색 O(lgN)


// 배열이 오름차순으로 정렬되어 있다고 가정하고 이분탐색을 시작
int a[8] = { 1,2,3,4,5,6,7,8 };
int n = 8;
int binarysearch(int target) {
	int st = 0;
	int en = n - 1;
	while (st <= en) {
		int mid = (st + en) / 2;
		if (a[mid] < target)
			st = mid + 1;
		else if (a[mid] > target)
			en = mid - 1;
		else
			return 1;
	}
	return 0; // st >en일 경우 while 탈출
}
int binsearch_recursive(int st, int en,int target) {
	int mid;
	if (st > en) return 0;
	else {
		mid = (st + en / 2);
		if (target = a[mid])
			return mid;
		else if (target < a[mid])
			return binsearch_recursive(st, mid - 1, target);
		else
			return binsearch_recursive(mid+1, en, target);
	}
	int st = 0;
	int en = n - 1;
}
int main() {
	int target;
	cin >> target;
	cout << binarysearch(target);
}