#include <iostream>
#include <string.h>
using namespace std;

// 이진트리 구조 사용
// 힙생성(Heapify)의 알고리즘 시간복잡도 : O(lgN)
// 힙구조를 만드는 전체 알고리즘 시간복잡도 : 1/2N x lgN => O(N*lgN)
// 전체구조에서 1/2개 만큼만 보면 힙구조를 만들 수 있음
// 예를들어 전체 9개인 이진 트리가 있을 때 상위 노드 4개에 대해서만 자식노드와 대수비교를 해서
// 자식보다 작을 경우 자리를 바꿈 
// 그 다음 루트와 맨 마지막 노드의 자리를 바꿈
// 마지막 노드에 대해서만 heapify 수행(마지막 노드를 제외하고 대수비교하여 자리 체인지)
// 이것을 반복하면 바로 힙구조를 만드는 알고리즘(heapify)
// (상향식 힙 구조)
// 완전 이진 트리는 배열에 그대로 삽입해도 문제없음

int number = 9;
int heap[9] = { 7,6,5,8,3,5,9,1,6 };
int main() {
	// 전체 트리 구조(heap[9])을 최대 힙 구조로 바꾸는 알고리즘
	for (int i = 1; i < number; i++) {
		int c = i; // 힙구조를 수행하기 위해 노드를 가르키는 포인터 역할
		do {
			int root = (c - 1) / 2; // c의 부모를 가르키는 수식
			if (heap[root] < heap[c]) { // 자식노드의 값이 부모노드보다 클 경우
				int temp = heap[root];
				heap[root] = heap[c];
				heap[c] = temp;
			}
			c = root;// c를 자식의 노드로 이동해서 반복적으로 힙구조를 만듬
		} while (c != 0);
	}
	// 크기를 줄여가며 반복적으로 힙을 구성
	for (int i = number - 1; i >= 0; i--) {
		// 가장 큰 루트 노드를 배열의 맨 뒤의 노드와 바꿈
		int temp = heap[0];
		heap[0] = heap[i];
		heap[i] = temp;
		int root = 0;
		int c = 1;
		do {
			c = 2 * root + 1; // c는 root의 자식
			// 자식 중에 더 큰 값을 찾기
			if (heap[c] < heap[c + 1] && c < i - 1) {
				c++;
			}
			if (heap[root] < heap[c] && c < i) {
				int temp = heap[root];
				heap[root] = heap[c];
				heap[c] = temp;
			}
			root = c;
		} while (c < i);
	}
}