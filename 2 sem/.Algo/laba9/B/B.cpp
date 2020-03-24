#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;

enum color{
    white,
    grey,
    black
};

int n;
vector < vector<int> > g;
vector<char> color;
vector<int> parent;
int cycle_start, cycle_end;

bool dfs(int v);

int main() {

    std::freopen("cycle.in","r", stdin);
    std::freopen("cycle.out","w", stdout);

    unsigned n,m;
    std::cin >> n >> m;

    g.resize(n);
    unsigned b,e,j=0;
    while(j<m){
        std::cin>>b>>e;
        g[b-1].push_back(e-1);
        j++;
    }

    parent.resize(n+1);
    color.resize(n);
    cycle_start = -1;
    for (int i=0; i<n; ++i)
        if (dfs (i))
            break;

    if (cycle_start == -1)
        cout <<"NO";
    else {
        cout<<"YES"<<endl;
        vector<int> cycle;
        cycle.push_back (cycle_start);
        for (int v=cycle_end; v!=cycle_start; v=parent[v])
            cycle.push_back (v);
        reverse (cycle.begin(), cycle.end());
        for (size_t i=0; i<cycle.size(); ++i)
            cout<<cycle[i]+1<<" ";
    }
}

bool dfs (int v) {
    color[v] = grey;
    for (int u : g[v]) {
        if (color[u] == white) {
            parent[u] = v;
            if (dfs (u))  return true;
        }
        else if (color[u] == grey) {
            cycle_end = v;
            cycle_start = u;
            return true;
        }
    }
    color[v] = black;
    return false;
}