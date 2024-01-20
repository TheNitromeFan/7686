#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#define MAXN 10

using namespace std;

int c[MAXN][MAXN];
vector<int> adj[MAXN];
unsigned pointer[MAXN];
int f[MAXN][MAXN];
int level[MAXN];

bool bfs(){
    queue<int> q;
    q.push(0);
    level[0] = 0;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v : adj[u]){
            if(level[v] == -1 && c[u][v] > f[u][v]){
                q.push(v);
                level[v] = level[u] + 1;
            }
        }
    }
    return level[7] != -1;
}

int dfs(int u, int pushed){
    if(pushed == 0){
        return 0;
    }else if(u == 7){
        return pushed;
    }
    while(pointer[u] < adj[u].size()){
        int v = adj[u][pointer[u]];
        ++pointer[u];
        if(level[v] == level[u] + 1 && c[u][v] > f[u][v]){
            int flow = dfs(v, min(pushed, c[u][v] - f[u][v]));
            if(flow){
                f[u][v] += flow;
                f[v][u] -= flow;
                return flow;
            }
        }
    }
    return 0;
}

int dinic(){
    int answer = 0;
    while(true){
        fill(level, level + MAXN, -1);
        if(!bfs()){
            break;
        }
        fill(pointer, pointer + MAXN, 0);
        while(true){
            int flow = dfs(0, 1000000000);
            if(flow == 0){
                break;
            }
            answer += flow;
        }
    }
    return answer;
}

int main(){
    // s and t are labeled 0 and 7 respectively
    // the remaining 6 vertices are labeled 1, ..., 6 in row-major order
    c[0][1] = 1; adj[0].push_back(1); adj[1].push_back(0);
    c[0][3] = 2; adj[0].push_back(3); adj[3].push_back(0);
    c[0][5] = 10; adj[0].push_back(5); adj[5].push_back(0);
    c[1][2] = 2; adj[1].push_back(2); adj[2].push_back(1);
    c[1][3] = 4; adj[1].push_back(3); adj[3].push_back(1);
    c[2][7] = 11; adj[2].push_back(7); adj[7].push_back(2);
    c[3][2] = 7; adj[3].push_back(2); adj[2].push_back(3);
    c[3][4] = 1; adj[3].push_back(4); adj[4].push_back(3);
    c[3][6] = 2; adj[3].push_back(6); adj[6].push_back(3);
    c[4][1] = 2; adj[4].push_back(1); adj[1].push_back(4);
    c[4][2] = 2; adj[4].push_back(2); adj[2].push_back(4);
    c[4][7] = 2; adj[4].push_back(7); adj[7].push_back(4);
    c[5][3] = 2; adj[5].push_back(3); adj[3].push_back(5);
    c[5][4] = 4; adj[5].push_back(4); adj[4].push_back(5);
    c[5][6] = 5; adj[5].push_back(6); adj[6].push_back(5);
    c[6][4] = 5; adj[6].push_back(4); adj[4].push_back(6);
    c[6][7] = 1; adj[6].push_back(7); adj[7].push_back(6);
    cout << "Maximum flow is " << dinic() << ".\n";
    for(int u = 0; u <= 7; ++u){
        for(int v = 0; v <= 7; ++v){
            if(f[u][v] > 0){
                cout << "Flow " << f[u][v] << " from " << u << " to " << v << ".\n";
            }
        }
    }
    return 0;
}