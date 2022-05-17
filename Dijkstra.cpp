#include <iostream>
#include<vector> // stl vector
#include<queue> // stl queue
using namespace std;

// pair의 인자인 <first, second>를 쉽게 X, Y로 치환해서 사용하기 위한 define
#define X first
#define Y second

// 순서대로 정점의 개수 v, 간선의 개수 e 시작정점 st
int v, e, st;

// {비용, 정점 번호}
vector<pair<int, int>> adj[20005];

const int INF = 0x3f3f3f3f;
int d[20005]; // 최단 거리 테이블
int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> v >> e >> st;
    fill(d, d + v + 1, INF);
    while (e--) { // 간선의 개수만큼 어느 노드에서 어느 노드를 이을지와 그 사이의 가중치를 정함

        // 노드u에서 노드v로 가는 가중치 w
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({ w,v });
    }

    // 매번 가장 적은 가중치(가장 가까운 정점)을 뽑아내야 하기 때문에 
    // 원소의 추가가 가능하고 최솟값의 확인/삭제가 효율적인 자료구조인 우선순위 큐 채용
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
    d[st] = 0; // 정점을 0으로 초기화
    // 우선순위 큐에 (0, 시작점) 추가
    pq.push({ d[st],st });
    while (!pq.empty()) { // 우선순위 큐가 빌때까지 반복

        auto cur = pq.top(); pq.pop(); // 원소가 가리키는 정점 cur {비용, 정점 번호}    
        // 거리가 d에 있는 값과 다를 경우 넘어감
        if (d[cur.Y] != cur.X) continue;
        for (auto nxt : adj[cur.Y]) { // cur과 이웃한 정점들에 대해서 반복
            if (d[nxt.Y] <= d[cur.Y] + nxt.X) continue; // 최단 거리 테이블 값(d)보다 cur을 거쳐가는 것이 더 작은 값을 가질 경우


            d[nxt.Y] = d[cur.Y] + nxt.X; // 최단 거리 테이블의 값을 갱신
            pq.push({ d[nxt.Y],nxt.Y }); // 우선순위 큐에 (거리, 이웃한 정점의 번호)를 추가
        }
    }

    for (int i = 1; i <= v; i++) {
        if (d[i] == INF) cout << "경로가 존재하지 않음\n"; // 경로가 존재하지 않을 경우
        else cout << i << "번 정점으로의 최단 경로의 경로값 : " << d[i] << "\n";
    }
}