#include <iostream>
#include <string.h>
using namespace std;

int n = 5;
int INF = 10000000;
int W[5][5] = {
	{0, 1, INF, 1,5},
	{9, 0 ,3 ,2, INF},
	{INF, INF, 0, 4,INF},
	{INF, INF ,2, 0, 3},
	{3, INF, INF, INF, 0}
};

void Floyd() {
	int P[5][5];
	int D[5][5] = {0, };
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			P[i][j] = 0;
		}
	}

	memcpy(D, W, sizeof(W));

	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (D[i][k] + D[k][j] < D[i][j]) {
					P[i][j] = k;
					D[i][j] = D[i][k] + D[k][j];
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (W[i][j] == INF) {
				printf("INF ");
			}
			else {
				printf("%3d ", W[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%3d ", D[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%3d ", P[i][j]);
		}
		printf("\n");
	}
}


int main(void) {
	ios::sync_with_stdio(0);
	cin.tie(0);
	Floyd();
}