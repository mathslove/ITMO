
#include <iostream>
#include <vector>
#include "list"
#include "algorithm"

using namespace std;

vector<bool> used;
vector<vector<unsigned > > graph;
vector<vector<unsigned > > reverse_graph;

void dfs(unsigned v, vector<unsigned >& mas, vector<bool>& visited){
    visited[v] = true;
    for (unsigned u : graph[v]){
        if (!visited[u])
            dfs(u, mas, visited);
    }
    mas.push_back(v);
}

void reverse_dfs(unsigned v, vector<unsigned >& res, unsigned& count){
    res[v] = count;
    for (unsigned u : reverse_graph[v]){
        if (res[u] == 0)
            reverse_dfs(u, res, count);
    }
}

int main() {

    std::freopen("cond.in","r", stdin);
    std::freopen("cond.out","w", stdout);

    unsigned n,m;
    std::cin >> n >> m;

    graph.resize(n);
    reverse_graph.resize(n);

    unsigned b,e;
    for(size_t i = 0; i < m; i++){
        cin>>b>>e;
        graph[b-1].push_back(e-1);
        reverse_graph[e-1].push_back(b-1);
    }

    used.assign(n, false);
    vector<unsigned > sort;
    vector<unsigned > comp(n,0);
    unsigned k = 0;

    for (size_t i = 0; i<n; i++){
        if (!used[i])
            dfs(i, sort, used);
    }
    reverse(sort.begin(), sort.end());

    for (unsigned x : sort){
        if (comp[x] == 0){
            reverse_dfs(x, comp, ++k);
        }
    }

    cout << k <<endl;
    for (unsigned x : comp)
        cout<<x<<" ";

    return 0;
}