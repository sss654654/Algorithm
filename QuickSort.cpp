#include <iostream>
#include <string.h>
using namespace std;

// ���� ��� ���� �˰��򺸴� ����
// ���� quick�� �����ؾ� �Ѵٸ� merge�� �� ��
// ��������� �����Ǵ� ����
// �� �ܰ� ���� pivot�� ���ڸ��� ���� 
// ����Ʈ�� ������ �߰����� ������ �ʿ����� ���� ������(In-Place Sort)
// Quick sort�� Stable sort �ƴ�
// �ܰ踶�� O(lgN)
// �ð� ���⵵ : O(NlgN)
// �߰������� �ʿ��� ����(Overhead) : O(1)

// worst case
// ����Ʈ�� ���������̰ų� ���������� ���
// �ܰ踶�� O(N)
// �ð� ���⵵ : O(N^2)
// -> pivot�� �����ϰ� ���ؼ� ó��, pivot�ĺ��� 3�� ���ؼ� 3�� �߿��� �߾Ӱ��� pivot���� �ּ� ó��
// O(NlgN)�� �����ϱ� ���ؼ� ���� ���� �̻� ���� HeapSort�� ���� �� �̸� Introspective sort��� �θ�
int arr[8] = {6, -8, 1, 12, 8, 3, 7, -7};

void quicksort(int st, int en) {
	if (en <= st + 1) return;
	int pivot = arr[st];
	int l = st + 1;
	int r = en - 1;
	while (1) {
		while (l <= r && arr[l] <= pivot) l++; // l�� pivot���� ū ���� ���� �� ���� ���������� �̵�
		while (l <= r && arr[r] > pivot) r--; // r�� pivot���� �۰ų� ���� ���� ���� �� ���� �������� �̵�
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