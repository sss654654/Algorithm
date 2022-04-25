#include <iostream>
#include <string.h>
using namespace std;

// �̺�Ž��
// ���ĵǾ� �ִ� �迭���� Ư�� �����͸� ã�� ���� �����͸� ���������� Ȯ���ϴ� ���
// Ž�� ������ �������� �ٿ����� ã�� Ž�� ���
// ����Ž�� O(N) �̺�Ž�� O(lgN)


// �迭�� ������������ ���ĵǾ� �ִٰ� �����ϰ� �̺�Ž���� ����
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
	return 0; // st >en�� ��� while Ż��
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