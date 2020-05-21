#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const long long INF = 8e18;
struct edge{
    int s,f;
    long long w;
    edge(int s,int f,long long w){
        this->s=s;
        this->f=f;
        this->w=w;
    }
};

void dfs(int v,vector<bool>& visited, vector<vector<int>>& graph){
    visited[v] = true;
    for (int u: graph[v])
        if (!visited[u])
            dfs(u, visited, graph);
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    std::freopen("path.in","r", stdin);
    std::freopen("path.out","w", stdout);

    int n,m,s;
    cin>>n>>m>>s;

    vector<edge> e;
    vector<vector<int>> graph(n);

    long long st,fn,wt;
    for (size_t i = 0; i<m; i++){
        cin >>st>>fn>>wt;
        e.emplace_back(edge(st-1,fn-1,wt));
        graph[st - 1].push_back(fn - 1);
    }

    vector<long long> d(n,INF + 1e17);
    vector<long long> p(n,-1);
    d[s-1]=0;
    int f;
    for (int i=0; i<n; ++i) {
        f = -1;
        for (int j=0; j<m; ++j)
            if (d[e[j].s] < INF)
                if (d[e[j].f] > d[e[j].s] + e[j].w) {
                    d[e[j].f] = max (-INF, d[e[j].s] + e[j].w);
                    p[e[j].f] = e[j].s;
                    f = e[j].f;
                }
    }
    vector<long long> newd(n);
    for (int i = 0; i < n; i++) newd[i] = d[i];
    for (int i=0; i<n; ++i) {
        for (int j=0; j<m; ++j)
            if (newd[e[j].s] < INF)
                if (newd[e[j].f] > newd[e[j].s] + e[j].w) {
                    newd[e[j].f] = newd[e[j].s] + e[j].w;
                }
    }
    vector<bool>visited(n, false);
    /*if (f!=-1){
        for (long long i = 0; i < n; i++)
            f = p[f];
        dfs(f, visited, graph);
    }*/
    for (int i = 0; i < n; i++) {
        if (newd[i] != d[i]) dfs(i, visited, graph);
    }
    for (long long i = 0; i < n; i++) {
        if (visited[i])
            cout << "-\n";
        else if (d[i] >= INF)
            cout << "*\n";
        else
            cout << d[i] << '\n';
    }

    return 0;
}