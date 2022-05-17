#include <iostream>
#include<vector> // stl vector
#include<queue> // stl queue
using namespace std;

// pair�� ������ <first, second>�� ���� X, Y�� ġȯ�ؼ� ����ϱ� ���� define
#define X first
#define Y second

// ������� ������ ���� v, ������ ���� e �������� st
int v, e, st;

// {���, ���� ��ȣ}
vector<pair<int, int>> adj[20005];

const int INF = 0x3f3f3f3f;
int d[20005]; // �ִ� �Ÿ� ���̺�
int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> v >> e >> st;
    fill(d, d + v + 1, INF);
    while (e--) { // ������ ������ŭ ��� ��忡�� ��� ��带 �������� �� ������ ����ġ�� ����

        // ���u���� ���v�� ���� ����ġ w
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w,v });
    }

    // �Ź� ���� ���� ����ġ(���� ����� ����)�� �̾Ƴ��� �ϱ� ������ 
    // ������ �߰��� �����ϰ� �ּڰ��� Ȯ��/������ ȿ������ �ڷᱸ���� �켱���� ť ä��
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
    d[st] = 0; // ������ 0���� �ʱ�ȭ
    // �켱���� ť�� (0, ������) �߰�
    pq.push({ d[st],st });
    while (!pq.empty()) { // �켱���� ť�� �������� �ݺ�

        auto cur = pq.top(); pq.pop(); // ���Ұ� ����Ű�� ���� cur {���, ���� ��ȣ}    
        // �Ÿ��� d�� �ִ� ���� �ٸ� ��� �Ѿ
        if (d[cur.Y] != cur.X) continue;
        for (auto nxt : adj[cur.Y]) { // cur�� �̿��� �����鿡 ���ؼ� �ݺ�
            if (d[nxt.Y] <= d[cur.Y] + nxt.X) continue; // �ִ� �Ÿ� ���̺� ��(d)���� cur�� ���İ��� ���� �� ���� ���� ���� ���


            d[nxt.Y] = d[cur.Y] + nxt.X; // �ִ� �Ÿ� ���̺��� ���� ����
            pq.push({ d[nxt.Y],nxt.Y }); // �켱���� ť�� (�Ÿ�, �̿��� ������ ��ȣ)�� �߰�
        }
    }

    for (int i = 1; i <= v; i++) {
        if (d[i] == INF) cout << "��ΰ� �������� ����\n"; // ��ΰ� �������� ���� ���
        else cout << i << "�� ���������� �ִ� ����� ��ΰ� : " << d[i] << "\n";
    }
}