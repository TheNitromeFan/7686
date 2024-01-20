#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#define MAX 22
#define INF 1000000000

using namespace std;

int n, m;
vector<int> adj[MAX];
int matched[MAX];
int dist[MAX];
unsigned ptr[MAX];
vector<int> adj1[MAX];
bool visited[MAX];

void bfs(){
	queue<int> q;
	for(int u = 1; u <= n; ++u){
		if(matched[u] == -1){
			dist[u] = 0;
			q.push(u);
		}else{
			dist[u] = INF;
		}
	}
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(int v : adj[u]){
			if(matched[v] != -1 && dist[matched[v]] == INF){
				dist[matched[v]] = dist[u] + 1;
				q.push(matched[v]);
			}
		}
	}
}

bool dfs(int u){
	while(ptr[u] < adj[u].size()){
		int v = adj[u][ptr[u]];
		if(matched[v] == -1 || (dist[matched[v]] == dist[u] + 1 && dfs(matched[v]))){
			matched[u] = v;
			matched[v] = u;
			return true;
		}
		++ptr[u];
	}
	return false;
}

void traverse(int u){
	visited[u] = true;
	for(int v : adj1[u]){
		if(!visited[v]){
			traverse(v);
		}
	}
}

int main(){
    int n = 10, m = 10;
    // vertices u_1, ..., u_10 are indexed 1 ... 10
    // vertices v_1, ..., v_10 are indexed 11 ... 20
    adj[1].push_back(11); adj[1].push_back(13); adj[1].push_back(14);
    adj[2].push_back(11); adj[2].push_back(12); adj[2].push_back(18);
    adj[3].push_back(11); adj[3].push_back(13);
    adj[4].push_back(13); adj[4].push_back(14);
    adj[5].push_back(13); adj[5].push_back(14);
    adj[6].push_back(15); adj[6].push_back(17);
    adj[7].push_back(12); adj[7].push_back(15); adj[7].push_back(16); adj[7].push_back(20);
    adj[8].push_back(15); adj[8].push_back(17); adj[8].push_back(20);
    adj[9].push_back(19);
    adj[10].push_back(14); adj[10].push_back(19);
	memset(matched, -1, sizeof(matched));
	while(true){
		memset(ptr, 0, sizeof(ptr));
		bfs();
		int flow = 0;
		for(int u = 1; u <= n; ++u){
			if(matched[u] == -1 && dfs(u)){
				++flow;
			}
		}
		if(flow == 0){
			break;
		}
	}
	for(int u = 1; u <= n; ++u){
        if(matched[u] != -1){
            cout << "u" << u << " is matched to v" << matched[u] - 10 << ".\n";
        }
	}
	for(int u = 1; u <= n; ++u){
		for(int v : adj[u]){
			if(matched[u] == v){
				adj1[v].push_back(u);
			}else{
				adj1[u].push_back(v);
			}
		}
	}
	for(int u = 1; u <= n; ++u){
		if(matched[u] == -1 && !visited[u]){
			traverse(u);
		}
	}
	cout << "Minimum vertex cover: ";
	vector<int> a;
	for(int u = 1; u <= n; ++u){
		if(!visited[u]){
			a.push_back(u);
		}
	}
	for(int u : a){
		cout << "u" << u << " ";
	}
	vector<int> b;
	for(int v = n + 1; v <= n + m; ++v){
		if(visited[v]){
			b.push_back(v - n);
		}
	}
	for(int v : b){
		cout << "v" << v << " ";
	}
	return 0;
}